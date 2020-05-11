//#include <jni.h>
#include <string>
#include "IPlayProxy.h"
#include "Log.h"

#include <android/native_window.h>
#include <android/native_window_jni.h>

extern "C" {
    #include <libavcodec/jni.h>
    #include <libavcodec/avcodec.h>
}


extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm,void *res)
{
    //设置Java虚拟机，如果不设置无法获取Android 硬解码
    av_jni_set_java_vm(vm,0);
    return JNI_VERSION_1_4;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_yplayer_Ylayer_open(
        JNIEnv* env,
        jobject, jstring path/* this */) {

        const char* url = env->GetStringUTFChars(path, 0);

        LOGI("yubin Java_com_example_yplayer_Ylayer_open url:%s", url);
        IPlayProxy::getInstance()->open(url);
        IPlayProxy::getInstance()->play();
        env->ReleaseStringUTFChars(path, url);
}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_yplayer_Ylayer_initPlayerView(JNIEnv *env, jobject thiz, jobject surface,
                                                                                jint outWidth, jint outHeight) {
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surface);
    IPlayProxy::getInstance()->init_player_view(nwin, outWidth, outHeight);
    LOGI("yubin Java_com_example_yplayer_Ylayer_initPlayerView");
}