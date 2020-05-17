//
// Created by Administrator on 2020/4/27.
//

#ifndef YPLAYER_IDECODE_H
#define YPLAYER_IDECODE_H


#include <mutex>
#include "IObserver.h"
#include "XParam.h"

class IDecode: public IObserver{
public:
    virtual void open(XParam *param)=0;
    void update(XData *data);
    virtual XData* receive_frame()=0;

protected:
    void mainProcess();
    virtual bool sendPacket(XData *data)=0;
    const int MAX_SIZE = 1000;
    bool m_is_exit = false;
    bool m_is_audio;
    std::mutex m_mutex;
    std::list<XData*> datas;
};


#endif //YPLAYER_IDECODE_H
