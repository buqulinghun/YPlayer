//
// Created by Administrator on 2020/5/5.
//

#ifndef YPLAYER_SLAUDIOPLAYER_H
#define YPLAYER_SLAUDIOPLAYER_H

#include "IAudioPlay.h"
#include "XParam.h"
extern "C" {
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
};

class SLAudioPlayer : public IAudioPlay {
public:
    virtual bool startPlay(XParam *aParam);
    SLAudioPlayer();
    bool createSL();
    void mainProcess(){}
    char* get_buf();
    SLAndroidSimpleBufferQueueItf m_pcmQue = NULL;

private:
    char *m_buf;
    SLEngineItf m_eng;
    SLObjectItf m_engineSL;
    SLObjectItf m_mix;
    SLObjectItf m_player;
    SLPlayItf m_iplayer;
};


#endif //YPLAYER_SLAUDIOPLAYER_H
