//
// Created by Administrator on 2020/5/1.
//
extern "C"{
#include <libavcodec/avcodec.h>
}

#include <cstdint>
#include <cstring>
#include "XData.h"
void XData::alloc(int size, const char* d) {
    m_dataType = UNCHAR_TYPE;
    m_data = new uint8_t [size];
    memset(m_data, 0, size);

    if(d) {
        memcpy(m_data, d, size);
    }

    m_size = size;

}

void XData::drop(){
    if(m_data != NULL) {
        return;
    }

    if(m_dataType == UNCHAR_TYPE) {
        delete(m_data);
    } else if(m_dataType == AVFRAME_TYPE) {
        av_frame_free((AVFrame**)&m_data);
    } else if(m_dataType == AVPACKET_TYPE) {
        av_packet_free((AVPacket**)&m_data);
    }

    m_data = NULL;
    m_size = 0;
}