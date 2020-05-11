//
// Created by Administrator on 2020/4/28.
//

#include <list>
#include "IObserver.h"
#include "Log.h"

using namespace std;

void IObserver::addObserver(IObserver *observer) {
    if (!observer) {
        LOGE("observer is null");
        return;
    }

    LOGI("IObserver::addObserver m_observers:%p", &m_observers);
    m_observers.push_back(observer);
}

void IObserver::notify(XData *data) {
    for (int i = 0; i < m_observers.size(); i++) {
        m_observers.at(i)->update(data);
    }
}