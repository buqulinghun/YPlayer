//
// Created by Administrator on 2020/5/1.
//

#ifndef YPLAYER_XTHREAD_H
#define YPLAYER_XTHREAD_H


class XThread {
public:
    virtual bool start();
    void XSleep(int mis);

protected:
    //入口函数
    virtual void mainProcess()=0;

private:
    void threadMain();


};


#endif //YPLAYER_XTHREAD_H
