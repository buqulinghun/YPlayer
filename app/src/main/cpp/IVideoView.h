//
// Created by Administrator on 2020/4/27.
//

#ifndef YPLAYER_IVIDEOVIEW_H
#define YPLAYER_IVIDEOVIEW_H


#include <jni.h>
#include <android/native_window.h>
#include "IObserver.h"

class IVideoView : public IObserver {
public:
    virtual void init_player_view(ANativeWindow* nwin, uint32_t width, uint32_t height)=0;
};


#endif //YPLAYER_IVIDEOVIEW_H
