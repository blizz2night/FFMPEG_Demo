#include <jni.h>
#include <string>
#include <unistd.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_github_blizz2night_ffmpeg_1demo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavcodec/jni.h>

JNIEXPORT jstring JNICALL
Java_com_github_blizz2night_ffmpeg_1demo_MainActivity_ffmpegInfo(JNIEnv *env, jobject  /* this */) {
    char info[40000] = {0};
    AVCodec *c_temp = av_codec_next(nullptr);
    while (c_temp != nullptr) {
        if (c_temp->decode != nullptr) {
            sprintf(info, "%sdecode:", info);
            switch (c_temp->type) {
                case AVMEDIA_TYPE_VIDEO:
                    sprintf(info, "%s(video):", info);
                    break;
                case AVMEDIA_TYPE_AUDIO:
                    sprintf(info, "%s(audio):", info);
                    break;
                default:
                    sprintf(info, "%s(other):", info);
                    break;
            }
            sprintf(info, "%s[%10s]\n", info, c_temp->name);
        }
        c_temp = c_temp->next;
    }
    return env->NewStringUTF(info);
}
}