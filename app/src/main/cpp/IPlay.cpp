//
// Created by Administrator on 2020/4/26.
//

#include "IPlay.h"
void IPlay::open(const char* url) {
    if (!m_demux) {
        LOGE("m_demux is NULL");
        return;
    }

    m_demux->open(url);

    if(m_vdecode == NULL || m_adecode == NULL) {
        LOGE("m_vdecode or m_adecode is NULL");
        return;
    }

//    XParam *auParam = m_demux->getAParam();
    XParam aParam, vParam;
    m_vdecode->open(m_demux->getVParam(&vParam));
    m_adecode->open(m_demux->getAParam(&aParam));
    m_resmaple->open(&aParam);
}

void IPlay::play() {
    LOGI("IPlay::play()");
    m_demux->start();
    m_vdecode->start();
    m_adecode->start();

    XParam aParam;
    m_audioPlay->startPlay(m_demux->getAParam(&aParam));
}

void IPlay::init_player_view(ANativeWindow* nwin, uint32_t width, uint32_t height) {
    m_videoView->init_player_view(nwin, width, height);
}

