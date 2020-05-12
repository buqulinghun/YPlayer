//
// Created by Administrator on 2020/5/5.
//

extern "C"{
#include <libavformat/avformat.h>
}
#include "SLAudioPlayer.h"
#include "Log.h"
#include "XParam.h"

SLAudioPlayer::SLAudioPlayer() {
    m_buf = new char[1024 * 1024];
}


bool SLAudioPlayer::createSL() {
    SLresult re;
    re = slCreateEngine(&m_engineSL, 0, 0, 0, 0, 0);
    if(re != SL_RESULT_SUCCESS) {
        return false;
    }

    re = (*m_engineSL)->Realize(m_engineSL, SL_BOOLEAN_FALSE);
    if(re != SL_BOOLEAN_FALSE) {
        return false;
    }

    re = (*m_engineSL)->GetInterface(m_engineSL, SL_IID_ENGINE, &m_eng);
    if(re != SL_BOOLEAN_FALSE) {
        return false;
    }

    return true;
}


static void pcmCall(SLAndroidSimpleBufferQueueItf bf,void *context) {
//    LOGI("SLAudioPlayer");

    SLAudioPlayer *player = (SLAudioPlayer*)context;
    if(!player) {
        LOGE("player is NULL");
        return;
    }

    XData* data = player->getData();
    if(data == NULL || data->get_size() == 0) {
        LOGE("avframe is NULL");
        return;
    }

    char* buf = player->get_buf();
    int size = data->get_size();

    memcpy(buf, data, size);

    if(player->m_pcmQue && (*(player->m_pcmQue))) {
        (*player->m_pcmQue)->Enqueue(player->m_pcmQue, buf, size);
        data->drop();
        LOGI("m_pcmQue)->Enqueue len:%d", size);
    }
}

char* SLAudioPlayer::get_buf() {
    return m_buf;
}

bool SLAudioPlayer::startPlay(XParam *aParam) {
     //1 创建引擎
     if(createSL()) {
         LOGI("SLAudioPlayer createSL success");
     } else {
         LOGE("SLAudioPlayer createSL failed");
         return false;
     }

     //2 创建混音器
    SLresult re = 0;
    re = (*m_eng)->CreateOutputMix(m_eng, &m_mix, 0, 0, 0);
    if(re != SL_RESULT_SUCCESS) {
        LOGE("SLAudioPlayer CreateOutputMix failed. re=%d", re);
        return false;
    }
    LOGI("SLAudioPlayer CreateOutputMix success");

    re = (*m_mix)->Realize(m_mix, SL_BOOLEAN_FALSE);
    if(re != SL_RESULT_SUCCESS) {
        LOGE("SLAudioPlayer m_mix)->Realize failed");
        return false;
    }
    LOGI("SLAudioPlayer m_mix)->Realize success");

    // 3、配置音频信息
    SLDataLocator_OutputMix outputMix = {SL_DATALOCATOR_OUTPUTMIX, m_mix};
    SLDataSink audioSink = {&outputMix, 0};
    SLDataLocator_AndroidSimpleBufferQueue que = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 10};
    LOGI("SLAudioPlayer pcm channel:%d sample:%d", aParam->get_channel(), aParam->get_sample());

    SLDataFormat_PCM pcm = {
        SL_DATAFORMAT_PCM,
        (SLuint32)aParam->get_channel(),
        (SLuint32)aParam->get_sample() * 1000,
        SL_PCMSAMPLEFORMAT_FIXED_16,
        SL_PCMSAMPLEFORMAT_FIXED_16,
        SL_SPEAKER_FRONT_LEFT|SL_SPEAKER_FRONT_RIGHT,
        SL_BYTEORDER_LITTLEENDIAN//字节序，小端
    };
    SLDataSource ds = {&que, &pcm};

    //4、创建播放器
    const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE};
    const SLboolean req[] = {SL_BOOLEAN_TRUE};

    re = (*m_eng)->CreateAudioPlayer(m_eng, &m_player, &ds, &audioSink,
                                             sizeof(ids)/sizeof(SLInterfaceID), ids, req);

    if(re != SL_RESULT_SUCCESS) {
        LOGE("SLAudioPlayer CreateAudioPlayer failed. re=%d", re);
        return false;
    }
    LOGI("SLAudioPlayer CreateAudioPlayer success");

    (*m_player)->Realize(m_player, SL_BOOLEAN_FALSE);
    re = (*m_player)->GetInterface(m_player, SL_IID_PLAY, &m_iplayer);
    if(re != SL_RESULT_SUCCESS) {
        LOGE("SLAudioPlayer GetInterface is failed");
        return false;
    }
    LOGI("SLAudioPlayer GetInterface is success");

    re = (*m_player)->GetInterface(m_player,SL_IID_BUFFERQUEUE,&m_pcmQue);
    if(re !=SL_RESULT_SUCCESS )
    {
        LOGE("GetInterface SL_IID_BUFFERQUEUE failed!");
        return false;
    }


    //设置回调函数
    (*m_pcmQue)->RegisterCallback(m_pcmQue, pcmCall, this);
    (*m_iplayer)->SetPlayState(m_iplayer, SL_PLAYSTATE_PLAYING);
    //启动队列回调
    (*m_pcmQue)->Enqueue(m_pcmQue, "", 1);
    LOGI("SLAudioPlayer Enqueue success");

    return true;
}