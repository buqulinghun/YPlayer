//
// Created by Administrator on 2020/5/1.
//
#include <thread>
#include "XThread.h"
#include "Log.h"

using namespace std;
bool XThread::start() {
//    thread th();
    thread th(&XThread::threadMain, this);
    th.detach();
    return true;
}

void XThread::XSleep(int mis) {
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

void XThread::threadMain() {
    LOGI("进入线程");
    mainProcess();
}


