//
// Created by Administrator on 2020/4/28.
//


#include "FFDecode.h"
#include "Log.h"

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavutil/samplefmt.h>
}

void FFDecode::open(XParam *param) {
    if(param == NULL) {
        LOGE("FFDecode::open failed");
        return;
    }

    LOGI("FFDecode::open param:%p", param);
    AVCodecParameters *ap = param->get_codec_paramters();
    if(ap == NULL) {
        LOGE("ap is NULL");
        return ;
    }
    LOGI("ap:%p", ap);

    AVCodec *avCodec = avcodec_find_decoder(ap->codec_id);
    if(avCodec == NULL) {
        LOGE("avcodec_find_decoder failed");
        return;
    }
    LOGI("avcodec_find_decoder success");

    m_avCodecContext = avcodec_alloc_context3(avCodec);
    if(m_avCodecContext == NULL) {
        LOGE("avcodec_alloc_context3 failed");
        return;
    }
    LOGI("avcodec_alloc_context3 success");

    int ret = avcodec_parameters_to_context(m_avCodecContext, ap);
    if(ret != 0) {
        LOGE("avcodec_parameters_to_context failed");
        return;
    }
    LOGI("avcodec_parameters_to_context success");

    ret = avcodec_open2(m_avCodecContext, 0, 0);
    if(ret != 0) {
        LOGE("avcodec_open2 is failed, ret=%d", ret);
        return;
    }

    LOGI("avcodec_open2 success");
    if(m_avCodecContext->codec_type == AVMEDIA_TYPE_AUDIO) {
        m_is_audio = true;
    }else if(m_avCodecContext->codec_type == AVMEDIA_TYPE_VIDEO) {
        m_is_audio = false;
    }
}

void FFDecode::update(XData *data) {
    if(m_is_audio != data->get_is_audio() || data->get_data() == NULL) {
        return;
    }

    while(!m_is_exit) {
        m_mutex.lock();
        if(datas.size() < MAX_SIZE) {
            LOGI("FFDecode::update m_is_audio:%d", m_is_audio);
            datas.push_back(data);
            m_mutex.unlock();
            break;
        }

        m_mutex.unlock();
        XSleep(2);
    }
}

void FFDecode::mainProcess() {
   while(!m_is_exit) {
        m_mutex.lock();
       if(datas.size() == 0) {
//           LOGI("mainProcess datas is empty");
           m_mutex.unlock();
           XSleep(10);
           continue;
       }

        XData* xdata = (XData*)datas.front();
        datas.pop_front();
        m_mutex.unlock();

        AVPacket *packet = (AVPacket*)xdata->get_data();
        int ret = avcodec_send_packet(m_avCodecContext, packet);
        if(ret != 0) {
            LOGE("avcodec_send_packet is failed. ret=%d", ret);
            free(xdata);
            continue;
        }

        while(!m_is_exit) {
            m_av_frame = av_frame_alloc();
            ret = avcodec_receive_frame(m_avCodecContext, m_av_frame);
            if(ret != 0) {
                char err_buf[1024] = {0};
                av_strerror(ret, err_buf, sizeof(err_buf) - 1);
                LOGE("avcodec_receive_frame is failed. ret=%d,msg:%s, %s", ret, err_buf, m_is_audio?"audio":"video");
                break;
            }

            LOGI("avcodec_receive_frame is success. ret=%d, %s", ret,  m_is_audio?"audio":"video");
            if(!m_av_frame->data) {
                break;
            }

            LOGI("avcodec_receive_frame success");
            XData *data = new XData();
            data->set_data((uint8_t*)m_av_frame);
            int size;
            if(m_avCodecContext->codec_type == AVMEDIA_TYPE_VIDEO) {
                size = (m_av_frame->linesize[0] + m_av_frame->linesize[1] + m_av_frame->linesize[2]) * m_av_frame->height;
                data->set_size(size);
                data->set_width(m_av_frame->width);
                data->set_height(m_av_frame->height);

                LOGI("yubin frame->format:%d frame->linesize:%d %d %d %d %d %d width:%d height:%d",
                     m_av_frame->format, m_av_frame->linesize[0], m_av_frame->linesize[1], m_av_frame->linesize[2],
                     m_av_frame->linesize[3], m_av_frame->linesize[4], m_av_frame->linesize[5], m_av_frame->width, m_av_frame->height);
            } else if (m_avCodecContext->codec_type == AVMEDIA_TYPE_AUDIO) {
                size = av_get_bytes_per_sample((AVSampleFormat)m_av_frame->format) * m_av_frame->nb_samples * m_av_frame->channels;
                data->set_size(size);
                LOGI("yubin frame->format:%d nb_sample:%d channels:%d size:%d", m_av_frame->format, m_av_frame->nb_samples, m_av_frame->channels, size);
            } else {
                continue;
            }

            data->set_size(size);
            data->set_frame_data(m_av_frame->data);
            data->set_pts(m_av_frame->pts);
            data->set_data_type(AVFRAME_TYPE);
            notify(data);
        }

        free(xdata);
   }
}