//
// Created by Administrator on 2020/4/27.
//

#ifndef YPLAYER_IAUDIOPLAY_H
#define YPLAYER_IAUDIOPLAY_H

#include <list>
#include <libavutil/frame.h>
#include <mutex>
#include "IObserver.h"
#include "XParam.h"
#include "XData.h"

class IAudioPlay : public IObserver{
public:
    virtual bool startPlay(XParam *aParam)=0;
    virtual void update(XData *data);
    XData* getData();
    const int MAX_SIZE = 50;

protected:
    std::list<XData*> m_datas;
    bool m_exit = false;
    std::mutex m_mutex;
};


#endif //YPLAYER_IAUDIOPLAY_H
