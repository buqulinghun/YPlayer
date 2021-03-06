# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#添加头文件路径（相对于本文件路径）
set(APPPATH E:/workspace/Android/Yplayer/app)
set(CPP_PATH ${APPPATH}/src/main/cpp)

#MESSAGE(AUTHOR_WARNING   "CPP_PATH = ${CPP_PATH}.")

#include_directories(${APPPATH}/include)
include_directories(E:/workspace/Android/Yplayer/app/include)


#设置ffmpeg库所在路径的变量
set(FF ${APPPATH}/libs/armeabi-v7a)

#设置ffmpeg库所在路径的变量
#set(FF ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI})
add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${FF}/libavcodec.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${FF}/libavformat.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${FF}/libavutil.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${FF}/libswscale.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${FF}/libswresample.so)


add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
            ${CPP_PATH}/native-lib.cpp
            ${CPP_PATH}/IPlay.cpp
            ${CPP_PATH}/IPlay.h
            ${CPP_PATH}/IPlayProxy.cpp
            ${CPP_PATH}/IPlayProxy.h
            ${CPP_PATH}/Log.h
            ${CPP_PATH}/IPlayerBuilder.cpp
            ${CPP_PATH}/IPlayerBuilder.h
            ${CPP_PATH}/FFPlayerBuilder.h
            ${CPP_PATH}/FFPlayerBuilder.cpp
            ${CPP_PATH}/IDemux.cpp
            ${CPP_PATH}/IDemux.h
            ${CPP_PATH}/FFDemux.cpp
            ${CPP_PATH}/FFDemux.h
            ${CPP_PATH}/IDecode.cpp
            ${CPP_PATH}/IDecode.h
            ${CPP_PATH}/FFDecode.cpp
            ${CPP_PATH}/FFDecode.h
            ${CPP_PATH}/IObserver.cpp
            ${CPP_PATH}/IObserver.h
            ${CPP_PATH}/IAudioPlay.cpp
            ${CPP_PATH}/IAudioPlay.h
            ${CPP_PATH}/IVideoView.cpp
            ${CPP_PATH}/IVideoView.h
            ${CPP_PATH}/FFVideoView.cpp
            ${CPP_PATH}/FFVideoView.h
            ${CPP_PATH}/XThread.cpp
            ${CPP_PATH}/XThread.h
            ${CPP_PATH}/IResample.h
            ${CPP_PATH}/IResample.cpp
            ${CPP_PATH}/FFResample.h
            ${CPP_PATH}/FFResample.cpp
            ${CPP_PATH}/SLAudioPlayer.h
            ${CPP_PATH}/SLAudioPlayer.cpp
            ${CPP_PATH}/XData.cpp
            ${CPP_PATH}/XData.h
            ${CPP_PATH}/XTexture.cpp
            ${CPP_PATH}/XTexture.h
            ${CPP_PATH}/GLVideoView.cpp
            ${CPP_PATH}/GLVideoView.h
            ${CPP_PATH}/GLVideoView.cpp
            ${CPP_PATH}/GLVideoView.h
            ${CPP_PATH}/XShader.cpp
            ${CPP_PATH}/Xshader.h
            ${CPP_PATH}/XEGL.cpp
            ${CPP_PATH}/XEGL.h
         )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                        native-lib
                        GLESv2 EGL
                        android OpenSLES avcodec avformat avutil swscale swresample
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )