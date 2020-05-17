//
// Created by Administrator on 2020/4/28.
//

#ifndef YPLAYER_FFDECODE_H
#define YPLAYER_FFDECODE_H


#include <list>
#include <mutex>
#include "IDecode.h"

struct AVPacket;

struct AVCodecContext;
struct AVFrame;
class FFDecode: public IDecode {
public:
    virtual void open(XParam *param);

protected:
    bool sendPacket(XData *data);
    XData* receive_frame();

private:
    AVCodecContext *m_avCodecContext = NULL;
};


#endif //YPLAYER_FFDECODE_H
