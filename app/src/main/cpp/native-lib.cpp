#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_kso_android_ndkapp_MainActivity_greetingFromJNI(
        JNIEnv* env,
        jobject) {
    std::string hello = "Hello World from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_kso_android_ndkapp_MainActivity_add(JNIEnv *env, jobject thiz, jint a, jint b) {
    return a + b;
}

extern "C"
JNIEXPORT jint JNICALL
Java_kso_android_ndkapp_MainActivity_getStrLen(JNIEnv *env, jobject thiz, jstring s_) {
    const char *s = env->GetStringUTFChars(s_, 0);

    jint len = strlen(s);

    env->ReleaseStringUTFChars(s_, s);
    return len;

}

extern "C"
JNIEXPORT jint JNICALL
Java_kso_android_ndkapp_MainActivity_addArray(JNIEnv *env, jobject thiz, jintArray jarr) {
    jint *arr = env->GetIntArrayElements(jarr, NULL);
    int res=0;
    int size = env->GetArrayLength(jarr);
    for(int i=0;i<size;i++)
        res+=arr[i];

    env->ReleaseIntArrayElements(jarr, arr, 0);
    return res;

}

extern "C"
JNIEXPORT jintArray JNICALL
Java_kso_android_ndkapp_MainActivity_getArray(JNIEnv *env, jobject thiz) {
    int arr[10]={1,2,3,4,5,6,7,8,9,0};
    jintArray ret = env->NewIntArray(10);

    env->SetIntArrayRegion(ret,0,10,arr);

    return ret;
}

jintArray gl_arr;
extern "C"
JNIEXPORT void JNICALL
Java_kso_android_ndkapp_MainActivity_saveArray(JNIEnv *env, jobject thiz, jintArray arr) {
    gl_arr = (jintArray )env->NewGlobalRef((jobject) arr);
}

extern "C"
JNIEXPORT jint JNICALL
Java_kso_android_ndkapp_MainActivity_addSavedArray(JNIEnv *env, jobject thiz) {
    jint *arr = env->GetIntArrayElements(gl_arr, NULL);
    int res=0;
    int size = env->GetArrayLength(gl_arr);
    for(int i=0;i<size;i++)
        res+=arr[i];

    env->ReleaseIntArrayElements(gl_arr, arr, 0);
    env->DeleteGlobalRef(gl_arr);
    return res;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_kso_android_ndkapp_Test_greetingFromJNI(JNIEnv *env, jobject thiz) {
    std::string name = "Kyaw San Oo";
    return env->NewStringUTF(name.c_str());
}


extern "C"
JNIEXPORT jobject JNICALL
Java_kso_android_ndkapp_MainActivity_getEmployeeFromJNI(JNIEnv *env, jobject thiz) {
    std::string name = "Kyaw San Oo";

    jclass employee_class = env->FindClass( "kso/android/ndkapp/Employee");
    jmethodID employee_constructor = env->GetMethodID( employee_class,  "<init>", "()V" );
    jobject employee_object = env->NewObject(employee_class, employee_constructor );

    jmethodID set_name_method = env->GetMethodID( employee_class,  "setName", "(Ljava/lang/String;)V" );
    jstring jstr = env->NewStringUTF( name.c_str() );
    env->CallVoidMethod(employee_object, set_name_method, jstr );
    return employee_object;
}