//
// Created by Administrator on 2020/4/27.
//

#include "FFPlayerBuilder.h"
#include "FFVideoView.h"
#include "Log.h"
#include "FFDecode.h"
#include "FFDemux.h"
#include "FFResample.h"
#include "SLAudioPlayer.h"
#include "GLVideoView.h"

FFPlayerBuilder::FFPlayerBuilder() {
    LOGI("FFPlayerBuilder::FFPlayerBuilder()");
    IPlay *play = createPlay();
    IDemux *demux = createDemux();

    IDecode *aDecode = createDecode();
    IDecode *vDecode = createDecode();

    demux->addObserver(aDecode);
    demux->addObserver(vDecode);

    play->set_dmux(demux);
    play->set_adecode(aDecode);
    play->set_vdecode(vDecode);

    IVideoView *videoView = createVideo();
    play->set_videoView(videoView);
    vDecode->addObserver(videoView);

    IResample *resample = createIResample();
    play->set_resample(resample);
    aDecode->addObserver(resample);

    IAudioPlay *audioPlay = createAudioPlay();
    play->set_audioPlay(audioPlay);
    resample->addObserver(audioPlay);
}


IPlay* FFPlayerBuilder:: createPlay() {
    LOGI("FFPlayerBuilder:: createPlay()");
    return IPlay::get();
}


IDemux* FFPlayerBuilder:: createDemux() {
    return new FFDemux();
}

IDecode* FFPlayerBuilder:: createDecode() {
    return new FFDecode();
}

IResample* FFPlayerBuilder:: createIResample() {
    return new FFResample();
}

IAudioPlay* FFPlayerBuilder::createAudioPlay() {
    return new SLAudioPlayer();
}

IVideoView* FFPlayerBuilder::createVideo() {
    return new GLVideoView();
//    return new FFVideoView();
}