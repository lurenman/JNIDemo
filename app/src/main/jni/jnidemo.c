#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <Android/log.h>

#ifndef BRUSHVIEWDEMO_LOG_UTIL_H
#define BRUSHVIEWDEMO_LOG_UTIL_H
#define LOG "demo_jni"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__)
#endif //BRUSHVIEWDEMO_LOG_UTIL_H

char *_JString2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid,
                                                            strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte *ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);
    return rtn;
}

JNIEXPORT jstring JNICALL Java_com_example_jnidemo_JNITest_getStrFromJNI
        (JNIEnv *env, jclass clazz) {

    return (*env)->NewStringUTF(env, "I am Str from jni libs!");
}

JNIEXPORT jint JNICALL Java_com_example_jnidemo_JNITest_add
        (JNIEnv *env, jclass clazz, jint a, jint b) {
    return a + b;
}

JNIEXPORT jstring JNICALL Java_com_example_jnidemo_JNITest_getStrParse
        (JNIEnv *env, jclass clazz, jstring jStr) {
    char *str = _JString2CStr(env, jStr);
    int length = strlen(str);
    int i;
    for (i = 0; i < length; i++) {
        *(str + i) += 1;
    }
    return (*env)->NewStringUTF(env, str);
}
//todo why
JNIEXPORT jintArray JNICALL Java_com_example_jnidemo_JNITest_parseIntArray
        (JNIEnv *env, jclass clazz, jintArray jArray) {
    int length = (*env)->GetArrayLength(env, jArray);
    // LOGE("length = %d",length);
    jint *p = (*env)->GetIntArrayElements(env, jArray, NULL);
    for (int i = 0; i < length; i++) {
        //i = i + 1;
        *(p++) = i + 100;
    }
    return jArray;
}
//示例 静态方法的调用
JNIEXPORT void JNICALL Java_com_example_jnidemo_JNITest_callbackvoidmethod
        (JNIEnv *env, jclass clazz) {
    jclass claz = (*env)->FindClass(env, "com/example/jnidemo/JNITest");
    //jmethodID methodId= (*env)->GetMethodID(env,clazz,"helloFromJava","()V");
    jmethodID methodId = (*env)->GetStaticMethodID(env, claz, "helloFromJava", "()V");
    (*env)->CallStaticVoidMethod(env, clazz, methodId);
}

JNIEXPORT void JNICALL Java_com_example_jnidemo_JNITest_callbackintmethod
        (JNIEnv *env, jclass clazz) {
    jclass claz = (*env)->FindClass(env, "com/example/jnidemo/JNITest");
    jmethodID methodId = (*env)->GetStaticMethodID(env, claz, "addback", "(II)I");
    (*env)->CallStaticIntMethod(env, clazz, methodId, 1, 2);
}

JNIEXPORT void JNICALL Java_com_example_jnidemo_JNITest_callbackstringmethod
        (JNIEnv *env, jclass clazz) {
    jclass claz = (*env)->FindClass(env, "com/example/jnidemo/JNITest");
    jmethodID methodId = (*env)->GetStaticMethodID(env, claz, "stringback",
                                                   "(Ljava/lang/String;)V");
    char *str = "hello call string";
    jstring result = (*env)->NewStringUTF(env, str);
    (*env)->CallStaticVoidMethod(env, claz, methodId, result);
}