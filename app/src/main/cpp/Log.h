//
// Created by Administrator on 2020/4/26.
//

#ifndef YPLAYER_LOG_H
#define YPLAYER_LOG_H
#include <android/log.h>


#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,"yplayer",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"yplayer",__VA_ARGS__)



//#define NULL ((void *)0)


#endif //YPLAYER_LOG_H
