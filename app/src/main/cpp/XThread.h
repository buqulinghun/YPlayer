//
// Created by Administrator on 2020/5/1.
//

#ifndef YPLAYER_XTHREAD_H
#define YPLAYER_XTHREAD_H


class XThread {
public:
    virtual bool start();
    //入口函数
    virtual void mainProcess()=0;
    void XSleep(int mis);
private:
    void threadMain();


};


#endif //YPLAYER_XTHREAD_H
