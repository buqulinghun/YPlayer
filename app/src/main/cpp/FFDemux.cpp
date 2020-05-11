//
// Created by Administrator on 2020/4/30.
//
extern "C"{
#include <libavformat/avformat.h>
}
#include "FFDemux.h"
#include "Log.h"

FFDemux::FFDemux() {
    //初始化封装
    av_register_all();
    avformat_network_init();
    avcodec_register_all();
}


void FFDemux::open(const char* url) {
    LOGI("yubin FFDemux::open url:%s", url);
    int ret = avformat_open_input(&m_format_context, url, 0, 0);
    if (ret != 0) {
        char err_msg[1024];
        av_strerror(ret, err_msg, 1024);
        LOGE("avformat_open_input is failed! ret:%d errmsg:%s", ret, err_msg);
        return;
    }

    ret = avformat_find_stream_info(m_format_context, 0);
    if (ret != 0) {
        LOGE("avformat_find_stream_info is failed, ret=%d",ret);
        return;
    }

    m_total_duration = m_format_context->duration / (AV_TIME_BASE/1000);
    LOGI("m_total_duration =%d nb_streams=%d", m_total_duration, m_format_context->nb_streams);
}



void FFDemux::mainProcess() {
    LOGI("yubin FFDemux::mainProcess");

    while(!isExit) {
        AVPacket *packet = av_packet_alloc();
        int ret = av_read_frame(m_format_context, packet);
        if (ret != 0) {
            LOGE("av_read_frame is failed. ret=%d", ret);
            return;
        }

        XData *xdata = new XData();
        if(packet->stream_index == AUDIO_STREAM) {
            xdata->set_is_audio(true);
            LOGI("av_read_frame AUDIO_STREAM");
        }else if(packet->stream_index == VIDEO_STREAM) {
            xdata->set_is_audio(false);
            LOGI("av_read_frame VIDEO_STREAM");
        }else{
            continue;
        }

        xdata->set_size(packet->size);
        xdata->set_data((unsigned char*)packet);
        xdata->set_data_type(AVFRAME_TYPE);
        notify(xdata);
    }
}


XParam* FFDemux::getVParam(XParam *vparam) {
  /*  if(m_vParam != NULL) {
        return m_vParam;
    }*/

    int videoStream = av_find_best_stream(m_format_context, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    AVStream *avs = m_format_context->streams[videoStream];
    LOGI("videoStream:%d height=%d width=%d, codecpar=%d format=%d",
         videoStream, avs->codecpar->width, avs->codecpar->height, avs->codecpar->codec_id, avs->codecpar->format);

   /* m_vParam = new XParam();
    m_vParam->set_is_audio(false);
    m_vParam->set_acodeParam(avs->codecpar);
    return m_vParam;*/


    vparam->set_is_audio(false);
    vparam->set_acodeParam(avs->codecpar);
     return vparam;
}

XParam* FFDemux::getAParam(XParam *aParam) {
    /*if(m_aParam != NULL) {
        return m_aParam;
    }*/

    int audioStream = av_find_best_stream(m_format_context, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    AVStream *aus = m_format_context->streams[audioStream];
    LOGI("videoStream:%d channels=%d sample_rate=%d ",
         audioStream, aus->codecpar->channels, aus->codecpar->sample_rate);

    /*m_aParam = new XParam();
    m_aParam->set_is_audio(true);
    m_aParam->set_acodeParam(aus->codecpar);
    return m_aParam;*/

    aParam->set_is_audio(true);
    aParam->set_acodeParam(aus->codecpar);
    return aParam;
}
