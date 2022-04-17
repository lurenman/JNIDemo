#include <jni.h>
#include <stdlib.h>
#include <android/log.h>
#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


/**
 * 把一个jstring转换成一个c语言的char* 类型.
 */
char* _JString2CStr(JNIEnv* env, jstring jstr) {
	 char* rtn = NULL;
	 jclass clsstring = (*env)->FindClass(env, "java/lang/String");
	 jstring strencode = (*env)->NewStringUTF(env,"GB2312");
	 jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
	 jbyteArray barr = (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid, strencode); // String .getByte("GB2312");
	 jsize alen = (*env)->GetArrayLength(env, barr);
	 jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
	 if(alen > 0) {
		rtn = (char*)malloc(alen+1); //"\0"
		memcpy(rtn, ba, alen);
		rtn[alen]=0;
	 }
	 (*env)->ReleaseByteArrayElements(env, barr, ba,0);
	 return rtn;
}
JNIEXPORT jint JNICALL Java_com_itheima_javapassdata_JNI_add
  (JNIEnv * env, jobject clazz, jint x, jint y){
	return x+y;
}

/*
 * Class:     com_itheima_javapassdata_JNI
 * Method:    sayHelloInC
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_itheima_javapassdata_JNI_sayHelloInC
  (JNIEnv * env, jobject clazz, jstring jstr){
	//调用工具方法把 java中的string 类型 转换成 C 语言中的 char*
	char* cstr = _JString2CStr(env,jstr);
	//调用strlen 获取 cstr 字符串的长度
	int length = strlen(cstr);
	int i;
	for(i = 0;i<length;i++){
		*(cstr+i) += 1;
	}
	return (*env)->NewStringUTF(env,cstr);
}

/*
 * Class:     com_itheima_javapassdata_JNI
 * Method:    arrElementsIncrease
 * Signature: ([I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_itheima_javapassdata_JNI_arrElementsIncrease
  (JNIEnv * env, jobject clazz, jintArray jArray){
	//jsize       (*GetArrayLength)(JNIEnv*, jarray);
	jsize length =(*env)->GetArrayLength(env,jArray);
	LOGD("length = %d",length);
	//jboolean iscopy;
	//jint*       (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
	int* arrayPointer =(*env)->GetIntArrayElements(env,jArray,NULL);
	int i;
	for(i = 0;i<length;i++){
		*(arrayPointer+i) += 10;
	}
	return jArray;
}
