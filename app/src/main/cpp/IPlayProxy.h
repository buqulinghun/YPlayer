//
// Created by Administrator on 2020/4/26.
//

#ifndef YPLAYER_IPLAYPROXY_H
#define YPLAYER_IPLAYPROXY_H


#include "IPlay.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IAudioPlay.h"
#include "IVideoView.h"
#include "IPlayerBuilder.h"
#include "Log.h"
#include <mutex>
#include <android/native_window.h>


class IPlayProxy: public IPlay{
public:
    void open(const char* url);
    void play();
    void init_player_view(ANativeWindow* nwin, uint32_t width, uint32_t height);
//    void start();


    static IPlayProxy* getInstance() {

        LOGI("IPlayProxy* getInstance()");
        static IPlayProxy playProxy;
        return &playProxy;
    }


private:
    IPlayProxy();
    IPlay *m_play = NULL;

};


#endif //YPLAYER_IPLAYPROXY_H
