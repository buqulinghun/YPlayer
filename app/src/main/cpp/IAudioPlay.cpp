//
// Created by Administrator on 2020/4/27.
//

#include "IAudioPlay.h"
void IAudioPlay::update(XData *data) {
    while(!m_exit) {
        m_mutex.lock();
        if(m_datas.size() > MAX_SIZE) {
            m_mutex.unlock();
            XSleep(3);
            continue;
        }

        m_datas.push_back(data);
        m_mutex.unlock();
    }
}

XData* IAudioPlay::getData() {
    while(!m_exit) {
        m_mutex.lock();
        if(m_datas.empty()) {
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

