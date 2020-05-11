//
// Created by Administrator on 2020/4/27.
//

#ifndef YPLAYER_IPLAYERBUILDER_H
#define YPLAYER_IPLAYERBUILDER_H



#include "IPlay.h"

class IPlayerBuilder {
public:
    IPlayerBuilder();
    virtual IPlay* createPlay()=0;
    virtual IDemux* createDemux()=0;
    virtual IDecode* createDecode()=0;
    virtual IResample* createIResample()=0;
    virtual IAudioPlay* createAudioPlay()=0;
    virtual IVideoView* createVideo()=0;

protected:
    IPlay *m_play;

};


#endif //YPLAYER_IPLAYERBUILDER_H
