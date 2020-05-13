//
// Created by Administrator on 2020/4/28.
//

#ifndef YPLAYER_FFDECODE_H
#define YPLAYER_FFDECODE_H


#include <list>
#include <mutex>
#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;
class FFDecode: public IDecode {
public:
    virtual void open(XParam *param);
    void update(XData *data);
    void mainProcess();

private:
    AVCodecContext *m_avCodecContext = NULL;
    std::list<XData*> datas;
    bool m_is_exit = false;
    AVFrame *m_av_frame = NULL;
    std::mutex m_mutex;
    const int MAX_SIZE = 1000;
};


#endif //YPLAYER_FFDECODE_H
