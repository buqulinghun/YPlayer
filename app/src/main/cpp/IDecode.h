//
// Created by Administrator on 2020/4/27.
//

#ifndef YPLAYER_IDECODE_H
#define YPLAYER_IDECODE_H


#include "IObserver.h"
#include "XParam.h"

class IDecode: public IObserver{
public:
    virtual void open(XParam *param)=0;

protected:
    bool m_is_audio;
};


#endif //YPLAYER_IDECODE_H
