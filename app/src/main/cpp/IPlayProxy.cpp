//
// Created by Administrator on 2020/4/26.
//

#include <jni.h>
#include "IPlayProxy.h"
#include "Log.h"
#include "FFPlayerBuilder.h"
#include "FFDecode.h"

/**
 * 初始化
 * @param url 视频文件路径
 */


void IPlayProxy:: open(const char* url) {
   if (!m_play) {
        LOGE("player is null");
        return;
    }

   m_play->open(url);

}


void IPlayProxy::play() {
    if (!m_play) {
        LOGE("player is null");
        return;
    }

    m_play->play();
}

IPlayProxy::IPlayProxy() {
    LOGI("IPlayProxy::IPlayProxy()");
    IPlayerBuilder *m_playerBuild = new FFPlayerBuilder();
    m_play = m_playerBuild->createPlay();
}

/**
 * 双重检查单例，后续添加内存屏障
 * @return
 */
/*IPlayProxy* IPlayProxy::getInstance() {
    if (s_playerProxy == NULL) {
        m_mux.lock();
        if (s_playerProxy == NULL) {
            s_playerProxy = new IPlayProxy();
        }
        m_mux.unlock();
    }

    return s_playerProxy;
}*/

void IPlayProxy::init_player_view(ANativeWindow* nwin, uint32_t width, uint height) {
    m_play->init_player_view(nwin, width, height);
}