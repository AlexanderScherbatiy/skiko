#ifndef SK_BUILD_FOR_ANDROID
#include <jawt.h>
#include <jawt_md.h>

#include <stdlib.h>

#if SK_BUILD_FOR_WIN
#include <windows.h>
#include <strsafe.h>
#else
#include <dlfcn.h>
#endif

typedef jboolean (*JAWT_GetAWT_t)(JNIEnv *, JAWT *);

#if 0
bool check(JNIEnv* env, const char* msg) {
    if (env->ExceptionCheck()) {
        jthrowable exception = env->ExceptionOccurred();
        jclass throwableClass = env->FindClass("java/lang/Throwable");
        jmethodID toStringMethod = env->GetMethodID(
                throwableClass, "toString", "()Ljava/lang/String;");
        jstring messageObject = (jstring) env->CallObjectMethod(exception, toStringMethod);
        const char* messageString = env->GetStringUTFChars(messageObject, 0);
        fprintf(stderr, "Java exception: %s\n", messageString);
        env->ReleaseStringUTFChars(messageObject, messageString);
        jmethodID printStackTraceMethod = env->GetMethodID(throwableClass, "printStackTrace", "()V");
        env->CallVoidMethod(exception, printStackTraceMethod);
        env->ExceptionClear();
    }
}
#endif

 extern "C" jboolean Skiko_GetAWT(JNIEnv *env, JAWT *awt) {
    return JAWT_GetAWT(env, awt);
}

#endif