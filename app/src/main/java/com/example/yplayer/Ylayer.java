package com.example.yplayer;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class Ylayer extends GLSurfaceView implements SurfaceHolder.Callback {
    private String mPath;
    public static final int OUTWIDTH = 1920;
    public static final int OUTHEIGHT = 1080;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public Ylayer(Context context) {
        this(context, null);
    }

    public Ylayer(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        initPlayerView(holder.getSurface(), OUTWIDTH, OUTHEIGHT);
        open(mPath);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width,
                               int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    public void setPath(String path) {
        mPath = path;
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void open(String path);
    public native void initPlayerView(Object surface, int outWidth, int  height);
}
