//
// Created by Administrator on 2020/4/27.
//

#include "IAudioPlay.h"
#include "Log.h"

void IAudioPlay::update(XData *data) {
    if(data == NULL) {
        return;
    }

    while(!m_exit) {
        m_mutex.lock();
        if(m_datas.size() > MAX_SIZE) {
            LOGI("IAudioPlay::update size:%d", m_datas.size());
            m_mutex.unlock();
            XSleep(1);
            continue;
        }

        m_datas.push_back(data);
        m_mutex.unlock();
        return;
    }
}

XData* IAudioPlay::getData() {
    while(!m_exit) {
        m_mutex.lock();
        if(m_datas.empty()) {
            LOGI("IAudioPlay::getData is empty");
            m_mutex.unlock();
            XSleep(3);
            continue;
        }

        XData *data = (XData*)m_datas.front();
        m_datas.pop_front();
        m_mutex.unlock();
        return data;
    }
}

