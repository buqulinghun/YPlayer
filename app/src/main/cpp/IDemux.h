//
// Created by Administrator on 2020/4/27.
//

#ifndef YPLAYER_IDEMUX_H
#define YPLAYER_IDEMUX_H


#include "IObserver.h"
#include "XParam.h"

class IDemux: public IObserver {
public:
    virtual void open(const char* url)=0;
    virtual void mainProcess()=0;
    virtual XParam* getVParam(XParam *vParam)=0;
    virtual XParam* getAParam(XParam *aParam)=0;

private:
    bool m_is_exit = false;
};


#endif //YPLAYER_IDEMUX_H
