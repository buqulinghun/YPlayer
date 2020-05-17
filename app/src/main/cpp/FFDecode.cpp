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


/**
 * 发送数据到解码器
 * @param data
 * @return true 成功  false 失败
 */
bool FFDecode:: sendPacket(XData *data) {
    AVPacket *packet = (AVPacket*)data->get_data();
    int ret = avcodec_send_packet(m_avCodecContext, packet);
    if(ret != 0) {
        LOGE("avcodec_send_packet is failed. ret=%d", ret);
       return false;
    }

    return true;
}

XData* FFDecode::receive_frame() {
    AVFrame *av_frame = av_frame_alloc();
   int ret = avcodec_receive_frame(m_avCodecContext, av_frame);
    if(ret != 0) {
        char err_buf[1024] = {0};
        av_strerror(ret, err_buf, sizeof(err_buf) - 1);
        LOGE("avcodec_receive_frame is failed. ret=%d,msg:%s, %s", ret, err_buf, m_is_audio?"audio":"video");
        return NULL;
    }

    LOGI("avcodec_receive_frame is success. ret=%d, %s", ret,  m_is_audio?"audio":"video");
    if(!av_frame->data) {
        return NULL;
    }

    LOGI("avcodec_receive_frame success");
    XData *data = new XData();
    data->set_data((uint8_t*)av_frame);
    int size;
    if(m_avCodecContext->codec_type == AVMEDIA_TYPE_VIDEO) {
        size = (av_frame->linesize[0] + av_frame->linesize[1] + av_frame->linesize[2]) * av_frame->height;
        data->set_size(size);
        data->set_width(av_frame->width);
        data->set_height(av_frame->height);

        LOGI("yubin frame->format:%d frame->linesize:%d %d %d %d %d %d width:%d height:%d",
             av_frame->format, av_frame->linesize[0], av_frame->linesize[1], av_frame->linesize[2],
             av_frame->linesize[3], av_frame->linesize[4], av_frame->linesize[5], av_frame->width, av_frame->height);
    } else if (m_avCodecContext->codec_type == AVMEDIA_TYPE_AUDIO) {
        size = av_get_bytes_per_sample((AVSampleFormat)av_frame->format) * av_frame->nb_samples * av_frame->channels;
        data->set_size(size);
        LOGI("yubin frame->format:%d nb_sample:%d channels:%d size:%d", av_frame->format, av_frame->nb_samples, av_frame->channels, size);
    } else {
        free(data);
        return NULL;
    }

    data->set_size(size);
    data->set_frame_data(av_frame->data);
    data->set_pts(av_frame->pts);
    data->set_data_type(AVFRAME_TYPE);
    return data;
}



