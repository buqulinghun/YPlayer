//
// Created by Administrator on 2020/4/27.
//

#include "IResample.h"
#include "XData.h"
#include "../../../include/libavutil/frame.h"


void IResample::update(XData *xdata){
    XData *data = resample(xdata);
    if(!data) {
        notify(data);
    }
}

