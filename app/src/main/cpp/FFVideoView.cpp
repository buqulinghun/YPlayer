extern "C" {
#include <libavutil/frame.h>
#include <libswscale/swscale.h>
}

#include <opencl-c-base.h>
#include "FFVideoView.h"
#include "Log.h"

void FFVideoView::init_player_view(ANativeWindow* nwin, uint32_t width, uint32_t height) {
    ANativeWindow_setBuffersGeometry(nwin, width, height, WINDOW_FORMAT_RGBA_8888);
    m_nwin = nwin;
    m_width = width;
    m_height = height;
    m_rgb = new char[width * height *4 + 1];
    memset(m_rgb, 0 , width * height *4 + 1);
}

void FFVideoView::update(XData *xdata) {
    if(xdata == NULL) {
        LOGE("FFVideoView::update xdata is NULL");
        return;
    }

    AVFrame *frame = (AVFrame*)xdata->get_data();
    if (frame->data == NULL) {
        LOGE("frame->data is NULL");
        return;
    }

    LOGI("update 开始显示 m_width:%d height:%d frame->width:%d frame->height:%d", m_width, m_height, frame->width, frame->height);
    LOGI("frame->data:%s", frame->data);

    m_swsContext = sws_getCachedContext(m_swsContext, frame->width, frame->height,
            (AVPixelFormat)frame->format, m_width, m_height, AV_PIX_FMT_RGBA, SWS_FAST_BILINEAR, 0, 0, 0);

    if(m_swsContext == NULL) {
        LOGE("sws_getCachedContext is failed");
        return;
    }

    uint8_t *data[AV_NUM_DATA_POINTERS] = {0};
    data[0] = (uint8_t*)m_rgb;
    memset(m_rgb, 0, m_width * m_height *4);
    /*
    if(i++ % 3 == 0) {
        memset(m_rgb, 0, m_width * m_height *4);
    }else if(i++ % 3 ==1) {
        memset(m_rgb, 125, m_width * m_height *4);
    }else {
        memset(m_rgb, 255, m_width * m_height *4);
    }*/

    int lines[AV_NUM_DATA_POINTERS] = {0};
    lines[0] = m_width *4;
    int h = sws_scale(m_swsContext,
                      frame->data, frame->linesize, 0, frame->height, data, lines);
    LOGI("sws_scale h=%d", h);

    if (h <=0 ) {
        LOGE("h=%d", h);
        return;
    }

    LOGI("rgb:%s", m_rgb);

    ANativeWindow_Buffer wbuf;
    ANativeWindow_lock(m_nwin, &wbuf, 0);
    uint8_t *dst = (uint8_t*)wbuf.bits;
    memcpy(dst, m_rgb, m_width * m_height * 4);
    ANativeWindow_unlockAndPost(m_nwin);
    LOGI("ANativeWindow_unlockAndPost");
}