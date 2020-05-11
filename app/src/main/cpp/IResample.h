//
// Created by Administrator on 2020/4/27.
//

#ifndef YPLAYER_IRESAMPLE_H
#define YPLAYER_IRESAMPLE_H


#include "IObserver.h"
#include "XParam.h"

class IResample : public IObserver{
public:
    virtual void open(XParam* aParam)=0;
    virtual XData* resample(XData *data)=0;
protected:
    void update(XData *data);


};


#endif //YPLAYER_IRESAMPLE_H
