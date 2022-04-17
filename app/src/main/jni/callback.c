#include <jni.h>
#include <stdlib.h>
#include <android/log.h>
#define LOG_TAG "System.out"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
/**
 * ��һ��jstringת����һ��c���Ե�char* ����.
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
JNIEXPORT void JNICALL Java_com_itheima_callbackjava_JNI_callbackvoidmethod
  (JNIEnv * env, jobject clazz){
	//jclass      (*FindClass)(JNIEnv*, const char*);
	//�� ��ȡ�ֽ������
	jclass claz = (*env)->FindClass(env,"com/itheima/callbackjava/JNI");
	//�ڻ�ȡMethod����
	//jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
	jmethodID methodID =(*env)->GetMethodID(env,claz,"helloFromJava","()V");
	//��ͨ���ֽ�����󴴽�һ��Object
	//��ͨ��������÷���
	//void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
	(*env)->CallVoidMethod(env,clazz,methodID);

}

JNIEXPORT void JNICALL Java_com_itheima_callbackjava_JNI_callbackintmethod
  (JNIEnv * env, jobject clazz){
	//�� ��ȡ�ֽ������
	jclass claz =(*env)->FindClass(env,"com/itheima/callbackjava/JNI");
	//�ڻ�ȡMethod����
	jmethodID methodID = (*env)->GetMethodID(env,claz,"add","(II)I");
	//jint        (*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
	int result =(*env)->CallIntMethod(env,clazz,methodID,3,4);
	LOGD("result = %d",result);
}

JNIEXPORT void JNICALL Java_com_itheima_callbackjava_JNI_callbackStringmethod
  (JNIEnv * env, jobject clazz){
	//�� ��ȡ�ֽ������
		jclass claz =(*env)->FindClass(env,"com/itheima/callbackjava/JNI");
	//�� ��ȡMethod����
		jmethodID methodid =(*env)->GetMethodID(env,claz,"printString","(Ljava/lang/String;)V");
	//
		jstring result =(*env)->NewStringUTF(env,"hello from c");
		(*env)->CallVoidMethod(env,clazz,methodid,result);
}
JNIEXPORT void JNICALL Java_com_itheima_callbackjava_JNI_callbackShowToast
  (JNIEnv * env, jobject clazz){
	jclass claz =(*env)->FindClass(env,"com/itheima/callbackjava/JNI");
	jmethodID methodid =(*env)->GetMethodID(env,claz,"showToast","(Ljava/lang/String;)V");
	//jobject     (*AllocObject)(JNIEnv*, jclass);
	//ͨ���ֽ�����󴴽� java���� ��������Ǵ�����mainactivity�Ķ���
	//jobject obj =(*env)->AllocObject(env,claz);
	jstring result =(*env)->NewStringUTF(env,"hello from c");
	//void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
	(*env)->CallVoidMethod(env,clazz,methodid,result);
}

