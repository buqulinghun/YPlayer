extern "C"{
    #include <libavcodec/avcodec.h>
}


#include "IDecode.h"
#include "Log.h"

void IDecode::update(XData *data) {
    if(m_is_audio != data->get_is_audio() || data->get_data() == NULL) {
        return;
    }

    while(!m_is_exit) {
        m_mutex.lock();
        if(datas.size() < MAX_SIZE) {
            LOGI("FFDecode::update m_is_audio:%d", m_is_audio);
            datas.push_back(data);
            m_mutex.unlock();
            return;
        }

        m_mutex.unlock();
        XSleep(2);
    }
}

void IDecode::mainProcess() {
    while (!m_is_exit) {
        m_mutex.lock();
        if (datas.size() == 0) {
//           LOGI("mainProcess datas is empty");
            m_mutex.unlock();
            XSleep(10);
            continue;
        }

        XData *xdata = (XData *) datas.front();
        datas.pop_front();
        m_mutex.unlock();

        int ret = sendPacket(xdata);
        if (ret != 0) {
            LOGE("avcodec_send_packet is failed. ret=%d", ret);
            free(xdata);
            continue;
        }

        while (!m_is_exit) {
            XData *data = receive_frame();
            if (data != NULL) {
                notify(data);
                free(data);
            } else {
                break;
            }
        }

        free(xdata);
    }
}