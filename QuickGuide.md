# JNI Quick Guide

hxzhu

Created Jul 8, 2019

*Personal use only. *

## Steps

1. Write Java code

   ```java
   class Helloworld {
   	public native void Hello();
   	
   	static {
   		System.loadLibrary("Helloworld");
   	}
   	
   	public native void send(String a);
   	
   	public static void main(String[] args) {
   		new Helloworld().Hello(); 
   		new Helloworld().send("100010101010231310231023");
   	}
   }
   ```

   * `System.loadLibrary(*/Libraryname*/)`
   * Use `native` to declare functions that will use C

2. Generate c header file

   `javah Helloworld`

   * May need to modify the `#include <jni.h>` to `#include "jni.h"` in `*.h` 

3. Write C code

   ```c
   #include <stdio.h>
   #include "Helloworld.h"
   #include <string.h>
   
   JNIEXPORT void JNICALL Java_Helloworld_Hello (JNIEnv *env, jobject obj){
   	printf("Hello from c");
   	return;
   }
   
   JNIEXPORT void JNICALL Java_Helloworld_send (JNIEnv *env, jobject obj, jstring a){
   	printf("Hello from c. Following comes from JAVA\n");
   	char buf[128];
   	const char *str = (*env)->GetStringUTFChars(env, a, 0);
   	printf("%s", str);
   	(*env)->ReleaseStringUTFChars(env, a, str);
   	
   	return;
   }
   ```

   * Implement functions that are declared in `*.h`
   * `jstring` can not be directly used as `char*`

4. Generate Library

   * Linux

     * Check JDK directory

       `echo $JAVA_HOME` 

     * Compile and generate `.o` file

       `gcc -I $JAVA_HOME/include/linux/ -fPIC -c Helloworld.c`

     * Compile and generate `.so` file

       `gcc -shared -WI -soname -o libHelloworld.so Helloworld.o`

     * `export LD_LIBRARY_PATH = 'pwd:$LD_LIBRARY_PATH'`

   * MacOS

     * Go to corresponding folder and run

       `gcc -dynamiclib -I /System/Library/Frameworks/JavaVM.framework/Headers Helloworld.c -o libHelloworld.jnilib`

       * Naming format `lib+NAME.jnilib`

5. `javac Helloworld.java`

6. `java Helloworld`



## Tables

### JIN Built-in Functions

| 函数                                                         | Java          | 本地类型 | 说明                                                         |
| :----------------------------------------------------------- | :------------ | :------- | :----------------------------------------------------------- |
| GetBooleanArrayElements                                      | jbooleanArray | jboolean | ReleaseBooleanArrayElements 释放                             |
| GetByteArrayElements                                         | jbyteArray    | jbyte    | ReleaseByteArrayElements 释放                                |
| GetCharArrayElements                                         | jcharArray    | jchar    | ReleaseShortArrayElements 释放                               |
| GetShortArrayElements                                        | jshortArray   | jshort   | ReleaseBooleanArrayElements 释放                             |
| GetIntArrayElements                                          | jintArray     | jint     | ReleaseIntArrayElements 释放                                 |
| GetLongArrayElements                                         | jlongArray    | jlong    | ReleaseLongArrayElements 释放                                |
| GetFloatArrayElements                                        | jfloatArray   | jfloat   | ReleaseFloatArrayElements 释放                               |
| GetDoubleArrayElements                                       | jdoubleArray  | jdouble  | ReleaseDoubleArrayElement 释放                               |
| GetObjectArrayElement                                        | 自定义对象    | object   |                                                              |
| SetObjectArrayElement                                        | 自定义对象    | object   |                                                              |
| GetArrayLength                                               |               |          | 获取数组大小                                                 |
| NewArray                                                     |               |          | 创建一个指定长度的原始数据类型的数组                         |
| GetPrimitiveArrayCritical                                    |               |          | 得到指向原始数据类型内容的指针，该方法可能使垃圾回收不能执行，该方法可能返回数组的拷贝，因此必须释放此资源。 |
| ReleasePrimitiveArrayCritical                                |               |          | 释放指向原始数据类型内容的指针，该方法可能使垃圾回收不能执行，该方法可能返回数组的拷贝，因此必须释放此资源。 |
| NewStringUTF                                                 |               |          | jstring类型的方法转换                                        |
| GetStringUTFChars                                            |               |          | jstring类型的方法转换                                        |
| DefineClass                                                  |               |          | 从原始类数据的缓冲区中加载类                                 |
| FindClass 该函数用于加载本地定义的类。它将搜索由CLASSPATH 环境变量为具有指定名称的类所指定的目录和 zip文件 |               |          |                                                              |
| GetObjectClass                                               |               |          | 通过对象获取这个类。该函数比较简单，唯一注意的是对象不能为NULL，否则获取的class肯定返回也为NULL |
| GetSuperclass                                                |               |          | 获取父类或者说超类 。 如果 clazz 代表类class而非类 object，则该函数返回由 clazz 所指定的类的超类。 如果 clazz指定类 object 或代表某个接口，则该函数返回NULL |
| IsAssignableFrom                                             |               |          | 确定 clazz1 的对象是否可安全地强制转换为clazz2               |
| Throw                                                        |               |          | 抛出 java.lang.Throwable 对象                                |
| ThrowNew                                                     |               |          | 利用指定类的消息（由 message 指定）构造异常对象并抛出该异常  |
| ExceptionOccurred                                            |               |          | 确定是否某个异常正被抛出。在平台相关代码调用 ExceptionClear() 或 Java 代码处理该异常前，异常将始终保持抛出状态 |
| ExceptionDescribe                                            |               |          | 将异常及堆栈的回溯输出到系统错误报告信道（例如 stderr）。该例程可便利调试操作 |
| ExceptionClear                                               |               |          | 清除当前抛出的任何异常。如果当前无异常，则此例程不产生任何效果 |
| FatalError                                                   |               |          | 抛出致命错误并且不希望虚拟机进行修复。该函数无返回值         |
| NewGlobalRef                                                 |               |          | 创建 obj 参数所引用对象的新全局引用。obj 参数既可以是全局引用，也可以是局部引用。全局引用通过调用DeleteGlobalRef() 来显式撤消。 |
| DeleteGlobalRef                                              |               |          | 删除 globalRef 所指向的全局引用                              |
| DeleteLocalRef                                               |               |          | 删除 localRef所指向的局部引用                                |
| AllocObject                                                  |               |          | 分配新 Java 对象而不调用该对象的任何构造函数。返回该对象的引用。clazz 参数务必不要引用数组类。 |
| getObjectClass                                               |               |          | 返回对象的类                                                 |
| IsSameObject                                                 |               |          | 测试两个引用是否引用同一 Java 对象                           |
| NewString                                                    |               |          | 利用 Unicode 字符数组构造新的 java.lang.String 对象          |
| GetStringLength                                              |               |          | 返回 Java 字符串的长度（Unicode 字符数）                     |
| GetStringChars                                               |               |          | 返回指向字符串的 Unicode 字符数组的指针。该指针在调用 ReleaseStringchars() 前一直有效 |
| ReleaseStringChars                                           |               |          | 通知虚拟机平台相关代码无需再访问 chars。参数chars 是一个指针，可通过 GetStringChars() 从 string 获得 |
| NewStringUTF                                                 |               |          | 利用 UTF-8 字符数组构造新 java.lang.String 对象              |
| GetStringUTFLength                                           |               |          | 以字节为单位返回字符串的 UTF-8 长度                          |
| GetStringUTFChars                                            |               |          | 返回指向字符串的 UTF-8 字符数组的指针。该数组在被ReleaseStringUTFChars() 释放前将一直有效 |
| ReleaseStringUTFChars                                        |               |          | 通知虚拟机平台相关代码无需再访问 utf。utf 参数是一个指针，可利用 GetStringUTFChars() 获得 |
| NewObjectArray                                               |               |          | 构造新的数组，它将保存类 elementClass 中的对象。所有元素初始值均设为 initialElement |
| SetArrayRegion                                               |               |          | 将基本类型数组的某一区域从缓冲区中复制回来的一组函数         |
| GetFieldID                                                   |               |          | 返回类的实例（非静态）域的属性 ID。该域由其名称及签名指定。访问器函数的GetField 及 SetField系列使用域 ID 检索对象域。GetFieldID() 不能用于获取数组的长度域。应使用GetArrayLength()。 |
| GetField                                                     |               |          | 该访问器例程系列返回对象的实例（非静态）域的值。要访问的域由通过调用GetFieldID() 而得到的域 ID 指定。 |
| SetField                                                     |               |          | 该访问器例程系列设置对象的实例（非静态）属性的值。要访问的属性由通过调用SetFieldID() 而得到的属性 ID指定。 |
| GetStaticFieldID GetStaticField SetStaticField               |               |          | 同上，只不过是静态属性。                                     |
| GetMethodID                                                  |               |          | 返回类或接口实例（非静态）方法的方法 ID。方法可在某个 clazz 的超类中定义，也可从 clazz 继承。该方法由其名称和签名决定。 GetMethodID() 可使未初始化的类初始化。要获得构造函数的方法 ID，应将 作为方法名，同时将void (V) 作为返回类型。 |
| CallVoidMethod                                               |               |          | 同上                                                         |
| CallObjectMethod                                             |               |          | 同上                                                         |
| CallBooleanMethod                                            |               |          | 同上                                                         |
| CallByteMethod                                               |               |          | 同上                                                         |
| CallCharMethod                                               |               |          | 同上                                                         |
| CallShortMethod                                              |               |          | 同上                                                         |
| CallIntMethod                                                |               |          | 同上                                                         |
| CallLongMethod                                               |               |          | 同上                                                         |
| CallFloatMethod                                              |               |          | 同上                                                         |
| CallDoubleMethod                                             |               |          | 同上                                                         |
| GetStaticMethodID                                            |               |          | 调用静态方法                                                 |
| CallMethod                                                   |               |          | 同上                                                         |
| RegisterNatives                                              |               |          | 向 clazz 参数指定的类注册本地方法。methods 参数将指定 JNINativeMethod 结构的数组，其中包含本地方法的名称、签名和函数指针。nMethods 参数将指定数组中的本地方法数。 |
| UnregisterNatives                                            |               |          | 取消注册类的本地方法。类将返回到链接或注册了本地方法函数前的状态。该函数不应在常规平台相关代码中使用。相反，它可以为某些程序提供一种重新加载和重新链接本地库的途径。 |

