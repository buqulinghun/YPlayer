//
// Created by Administrator on 2020/5/3.
//

#ifndef YPLAYER_XPARAM_H
#define YPLAYER_XPARAM_H


struct AVCodecParameters;

class XParam {
public:
    bool get_is_audio() {
        return m_is_audio;
    }

    void set_is_audio(bool is_audio) {
        m_is_audio = is_audio;
    }

    void set_acodeParam(AVCodecParameters *codeParams) {
        m_acodeParam = codeParams;
    }

    AVCodecParameters * get_codec_paramters() {
        return m_acodeParam;
    }

    int get_channel() {
        return m_channels;
    }

    int get_sample() {
        return m_sample_rate;
    }
private:
    bool m_is_audio = false;
    AVCodecParameters *m_acodeParam = NULL;
    int m_channels = 2;
    int m_sample_rate = 44100;

};


#endif //YPLAYER_XPARAM_H
