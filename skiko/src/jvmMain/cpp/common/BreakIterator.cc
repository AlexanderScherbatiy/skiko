#include <jni.h>
#include "interop.hh"
#include "unicode/ubrk.h"

static void deleteBreakIterator(UBreakIterator* instance) {
  ubrk_close(instance);
}

extern "C" JNIEXPORT jlong JNICALL Java_org_jetbrains_skia_BreakIteratorKt_BreakIterator_1nGetFinalizer(JNIEnv* env, jclass jclass) {
    return static_cast<jlong>(reinterpret_cast<uintptr_t>(&deleteBreakIterator));
}

extern "C" JNIEXPORT jlong JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nMake
  (JNIEnv* env, jclass jclass, jint type, jstring localeStr, jintArray errorCode) {
    UErrorCode errorCodes[1] = { U_ZERO_ERROR };
    UBreakIterator* instance;
    if (localeStr == nullptr)
      instance = ubrk_open(static_cast<UBreakIteratorType>(type), uloc_getDefault(), nullptr, 0, errorCodes);
    else {
      SkString locale = skString(env, localeStr);
      instance = ubrk_open(static_cast<UBreakIteratorType>(type), locale.c_str(), nullptr, 0, errorCodes);
    }

    env->SetIntArrayRegion(errorCode, 0, 1, reinterpret_cast<jint*>(errorCodes));

    if (U_FAILURE(errorCodes[0])) {
      return 0;
    } else
      return reinterpret_cast<jlong>(instance);
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nClone
  (JNIEnv* env, jclass jclass, jlong ptr, jintArray errorCode) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    UErrorCode status = U_ZERO_ERROR;
    UBreakIterator* clone = ubrk_clone(instance, &status);
    if (U_FAILURE(status)) {
      env->ThrowNew(java::lang::RuntimeException::cls, u_errorName(status));
      return 0;
    } else
      return reinterpret_cast<jlong>(clone);
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nCurrent
  (JNIEnv* env, jclass jclass, jlong ptr) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    return ubrk_current(instance);
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nNext
  (JNIEnv* env, jclass jclass, jlong ptr) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    return ubrk_next(instance);
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nPrevious
  (JNIEnv* env, jclass jclass, jlong ptr) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    return ubrk_previous(instance);
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nFirst
  (JNIEnv* env, jclass jclass, jlong ptr) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    return ubrk_first(instance);
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nLast
  (JNIEnv* env, jclass jclass, jlong ptr) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    return ubrk_last(instance);
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nPreceding
  (JNIEnv* env, jclass jclass, jlong ptr, jint offset) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    return ubrk_preceding(instance, offset);
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nFollowing
  (JNIEnv* env, jclass jclass, jlong ptr, jint offset) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    return ubrk_following(instance, offset);
}

extern "C" JNIEXPORT jboolean JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nIsBoundary
  (JNIEnv* env, jclass jclass, jlong ptr, jint offset) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    return ubrk_isBoundary(instance, offset);
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nGetRuleStatus
  (JNIEnv* env, jclass jclass, jlong ptr) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    return ubrk_getRuleStatus(instance);
}

extern "C" JNIEXPORT jintArray JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nGetRuleStatuses
  (JNIEnv* env, jclass jclass, jlong ptr) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));
    UErrorCode status = U_ZERO_ERROR;
    int32_t len = ubrk_getRuleStatusVec(instance, nullptr, 0, &status);
    if (U_FAILURE(status))
      env->ThrowNew(java::lang::RuntimeException::cls, u_errorName(status));
    std::vector<jint> vec(len);
    ubrk_getRuleStatusVec(instance, reinterpret_cast<int32_t*>(vec.data()), len, &status);
    if (U_FAILURE(status))
      env->ThrowNew(java::lang::RuntimeException::cls, u_errorName(status));
    return javaIntArray(env, vec);
}

extern "C" JNIEXPORT jlong JNICALL Java_org_jetbrains_skia_BreakIteratorKt__1nSetText
  (JNIEnv* env, jclass jclass, jlong ptr, jcharArray textArr, jint len, jintArray errorCode) {
    UBreakIterator* instance = reinterpret_cast<UBreakIterator*>(static_cast<uintptr_t>(ptr));

    std::vector<jchar>* text = new std::vector<jchar>(len);
    env->GetCharArrayRegion(textArr, 0, len, text->data());

    UErrorCode errorCodes[1] = { U_ZERO_ERROR };
    ubrk_setText(instance, reinterpret_cast<UChar *>(text->data()), len, errorCodes);

    env->SetIntArrayRegion(errorCode, 0, 1, reinterpret_cast<jint*>(errorCodes));

    return reinterpret_cast<jlong>(text);
}