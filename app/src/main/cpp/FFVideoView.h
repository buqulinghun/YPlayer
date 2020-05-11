//
// Created by Administrator on 2020/4/29.
//

#ifndef YPLAYER_FFVIDEOVIEW_H
#define YPLAYER_FFVIDEOVIEW_H
#include <libswscale/swscale.h>
#include "IVideoView.h"

class FFVideoView : public IVideoView{
public:
    void init_player_view(ANativeWindow* nwin, uint32_t width, uint32_t height);
    void set_width(int width) {
        m_width = width;
    }

    void set_height(int height) {
        m_height = height;
    }

    void update(XData *data);
    void mainProcess(){}

private:
    ANativeWindow* m_nwin;
    int m_width;
    int m_height;
    char *m_rgb;
    SwsContext *m_swsContext;
};


#endif //YPLAYER_FFVIDEOVIEW_H
