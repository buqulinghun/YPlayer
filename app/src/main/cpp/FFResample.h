//
// Created by Administrator on 2020/5/5.
//

#ifndef YPLAYER_FFRESAMPLE_H
#define YPLAYER_FFRESAMPLE_H

#include <list>
#include "IResample.h"
#include "XData.h"
struct SwrContext;

class FFResample : public IResample{
public:
    void open(XParam* aParam);
    XData* resample(XData *data);
    void mainProcess(){}
private:
    SwrContext *m_actx = NULL;
    int m_out_channel;
    AVSampleFormat m_out_format;
};


#endif //YPLAYER_FFRESAMPLE_H
