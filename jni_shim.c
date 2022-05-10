#include <jni.h>
#include <stdio.h>

extern void get_a_value_from_rust();

JNIEXPORT jint JNICALL
Java_com_example_androidapp_JniShim_printSomething(JNIEnv *env, jclass clazz) {
    get_a_value_from_rust();
}
