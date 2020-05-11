//
// Created by Administrator on 2020/5/1.
//

#ifndef YPLAYER_XDATA_H
#define YPLAYER_XDATA_H

enum XDataType{
AVPACKET_TYPE = 0,
AVFRAME_TYPE = 1,
UNCHAR_TYPE = 2
};

class XData {
public:
    void set_size(int size) {
        m_size = size;
    }

    void set_data(uint8_t *data) {
        m_data = data;
    }

    uint8_t* get_data() {
        return m_data;
    }

    void set_is_audio(bool audio) {
        m_is_audio = audio;
    }

    int get_size() {
        return m_size;
    }

    bool get_is_audio() {
        return m_is_audio;
    }


    void set_width(int w) {
        m_width = w;
    }

    void set_height(int h) {
        m_height = h;
    }

    void set_format(int format) {
        m_format = format;
    }

    void set_frame_data(unsigned char** frame_data) {
        memcpy(m_frame_data, frame_data, sizeof(m_frame_data));
    }

    void set_pts(int64_t pts) {
        m_pts = pts;
    }

    void alloc(int size, const char * d = 0);
    void drop();

    XDataType get_data_type() {
        return m_dataType;
    }

    void set_data_type(XDataType dataType) {
        m_dataType = dataType;
    }

    ~XData() {
        drop();
    }

private:
    int m_size;
    uint8_t *m_data;
    bool m_is_audio;
    int m_width;
    int m_height;
    int m_format;
    unsigned char *m_frame_data[8] = {0};
    XDataType m_dataType;
    int64_t m_pts;

};


#endif //YPLAYER_XDATA_H
