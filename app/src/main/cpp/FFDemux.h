//
// Created by Administrator on 2020/4/30.
//

#ifndef YPLAYER_FFDEMUX_H
#define YPLAYER_FFDEMUX_H

struct AVFormatContext;

#include "IDemux.h"

class FFDemux: public IDemux {
public:
    void open(const char *url);
    void mainProcess();
    FFDemux();

    virtual XParam* getVParam(XParam *vparam);
    virtual XParam* getAParam(XParam *aParam);

    const int AUDIO_STREAM = 1;
    const int VIDEO_STREAM = 0;
private:
    AVFormatContext *m_format_context = NULL;
    int m_total_duration = 0;//单位毫秒
    bool isExit = false;
    XParam *m_aParam;
    XParam *m_vParam;

//    AVCodecParameters *parameters = NULL;
};


#endif //YPLAYER_FFDEMUX_H
