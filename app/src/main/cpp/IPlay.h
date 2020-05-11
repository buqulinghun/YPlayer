//
// Created by Administrator on 2020/4/26.
//

#ifndef YPLAYER_IPLAY_H
#define YPLAYER_IPLAY_H


#include <android/native_window.h>
#include "IVideoView.h"
#include "IAudioPlay.h"
#include "IResample.h"
#include "IDemux.h"
#include "IDecode.h"
#include "Log.h"

class IPlay {
public:
    virtual void open(const char* url);
    virtual void play();
    virtual void init_player_view(ANativeWindow* nwin, uint32_t width, uint32_t height);
    static IPlay* get(int index=0) {
        LOGI("IPlay::get index:%d", index);
        if (index < 0 || index >=256) {
            return NULL;
        }

        static IPlay s_players[256];
        return &s_players[index];
    }

    void set_dmux(IDemux *idemux) {
        m_demux = idemux;
    }

    IDemux* get_dmux() {
        return m_demux;
    }

    void set_adecode(IDecode *decode) {
        m_adecode = decode;
    }

    IDecode* get_adecode() {
        return m_adecode;
    }

    void set_vdecode(IDecode *decode) {
        m_vdecode = decode;
    }

    IDecode* get_vdecode() {
        return m_vdecode;
    }

    void set_audioPlay(IAudioPlay *audioPlay) {
        m_audioPlay = audioPlay;
    }

    IAudioPlay* get_audioPlay() {
        return m_audioPlay;
    }

    void set_videoView(IVideoView *videoView) {
        m_videoView = videoView;
    }

    IVideoView* get_videoView() {
        return m_videoView;
    }

    void set_resample(IResample *resample) {
        m_resmaple = resample;
    }


protected:
    IDemux *m_demux = NULL;
    IDecode *m_adecode = NULL;
    IDecode *m_vdecode = NULL;
    IResample *m_resmaple = NULL;
    IAudioPlay *m_audioPlay = NULL;
    IVideoView *m_videoView = NULL;

};


#endif //YPLAYER_IPLAY_H
