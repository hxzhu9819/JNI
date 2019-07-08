#include <stdio.h>
#include "Helloworld.h"
#include <string.h>

JNIEXPORT void JNICALL Java_Helloworld_Hello (JNIEnv *env, jobject obj){
	printf("Hello from c\n");
	return;
}

JNIEXPORT void JNICALL Java_Helloworld_send (JNIEnv *env, jobject obj, jstring a){
	printf("Java_Helloworld_send from c.\n");
	char buf[128];
	const char *str = (*env)->GetStringUTFChars(env, a, 0);
	printf("From JAVA: \n\n--------------------------------\n");
	printf("%s", str);
	printf("\n--------------------------------\n");
	(*env)->ReleaseStringUTFChars(env, a, str);
	
	return;
}

JNIEXPORT void JNICALL Java_Helloworld_sum(JNIEnv *env, jobject obj, jdouble a, jdouble b){
	printf("%f",a+b);
}