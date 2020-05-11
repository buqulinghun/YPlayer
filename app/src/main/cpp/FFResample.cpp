//
// Created by Administrator on 2020/5/5.
//

extern "C"{
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
#include <libavutil/channel_layout.h>
#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
}

#include "FFResample.h"
#include "Log.h"

void FFResample::open(XParam* aParam) {
    AVCodecParameters *avParams = aParam->get_codec_paramters();
    m_out_channel = avParams->channels;
    m_out_format = AV_SAMPLE_FMT_S16;

    m_actx = swr_alloc();
    if(m_actx == NULL) {
        LOGE("swr_alloc failed");
        return;
    }

    m_actx = swr_alloc_set_opts(m_actx,
            av_get_default_channel_layout(m_out_channel), m_out_format, avParams->sample_rate,
            av_get_default_channel_layout(avParams->channels), (AVSampleFormat)avParams->format, avParams->sample_rate,
            0, 0);
    if(m_actx == NULL) {
        LOGE("swr_alloc_set_opts is failed");
        return;
    }

    int ret = swr_init(m_actx);
    if(ret != 0) {
        LOGE("swr_init failed");
        return ;
    }

    LOGI("swr_init success");
}

XData* FFResample::resample(XData *xdata){
    if(xdata->get_data() == NULL) {
        LOGE("FFResample::resample xdata is null");
        return NULL;
    }

    AVFrame* frame = (AVFrame*)xdata->get_data();
    int outsize = m_out_channel * frame->nb_samples * av_get_default_channel_layout(m_out_format);
    if(outsize <= 0) {
        LOGE("outsize:%d", outsize);
        return NULL;
    }

    XData *out = new XData();
    out->alloc(outsize);
    uint8_t *outArray[2] = {0};
    outArray[0] = out->get_data();

    int len = swr_convert(m_actx,
            outArray, frame->nb_samples,
            (const uint8_t **)frame->data, frame->nb_samples);

    if(len < 0) {
//        out->drop();
        LOGE("swr_convert failed len:%d", len);
        free(out);
        return NULL;
    }
    LOGI("swr_convert success len:%d", len);
    out->set_size(len);

    return out;
}



