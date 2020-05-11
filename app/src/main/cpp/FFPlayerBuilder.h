//
// Created by Administrator on 2020/4/27.
//

#ifndef YPLAYER_FFPLAYERBUILDER_H
#define YPLAYER_FFPLAYERBUILDER_H


#include "IPlayerBuilder.h"

class FFPlayerBuilder : public IPlayerBuilder{
public:
    FFPlayerBuilder();

    virtual IPlay* createPlay();
    virtual IDemux* createDemux();
    virtual IDecode* createDecode();
    virtual IResample* createIResample();
    virtual IAudioPlay* createAudioPlay();
    virtual IVideoView* createVideo();
};


#endif //YPLAYER_FFPLAYERBUILDER_H
