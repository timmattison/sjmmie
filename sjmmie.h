#ifndef SJMMIE_HEADER
#define SJMMIE_HEADER

#include <fcntl.h>              
#include <stdio.h>              
#include <stdlib.h>             
#include <jni.h>
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "objects/sockaddr.h"

extern const char *constructor_name;
extern const char *no_arguments;

extern const char *SJMMIE_JVM_OPTS_VARIABLE;
extern const char *SJMMIE_CLASS_VARIABLE;

extern const int debug;

extern const int NOT_INITIALIZED;
extern const int INITIALIZED;
extern const int INITIALIZING;

extern int initialized;

// For getting the Java environment
JNIEnv* get_env();

// For converting Java arrays to char/byte arrays
extern char* java_byte_array_to_char_array(JNIEnv *env, jbyteArray java_byte_array);

// For converting char/byte arrays to Java arrays
extern jbyteArray char_array_to_java_byte_array(JNIEnv *env, char* c_buffer, int c_buffer_length);

// For converting Java arrays to int arrays
extern int* java_int_array_to_int_array(JNIEnv *env, jintArray java_byte_array);

// For converting int arrays to Java arrays
extern jintArray int_array_to_java_int_array(JNIEnv *env, int* c_buffer, int c_buffer_length);

// For safely freeing memory
extern void safe_delete_local_ref(JNIEnv *env, jobject object);
extern void safe_release_byte_array_elements(JNIEnv *env, jbyteArray java_byte_array, signed char *c_buffer);
extern void safe_release_byte_array_elements_copy_back(JNIEnv *env, jbyteArray java_byte_array, signed char *c_buffer);
extern void safe_release_int_array_elements(JNIEnv *env, jintArray java_int_array, int *c_buffer);
extern void safe_release_int_array_elements_copy_back(JNIEnv *env, jintArray java_byte_array, int *c_buffer);

// Copies a sockaddr from C to Java
jbyteArray copy_c_to_java_sockaddr(JNIEnv *env, struct sockaddr *input, int size);

// For character arrays
#define C_JAVA_CHAR_ARRAY(INPUT, LENGTH) jbyteArray INPUT ## _buffer = char_array_to_java_byte_array(env, (char *) INPUT, LENGTH);
#define CHAR_ARRAY_UNROLL(INPUT) INPUT ## _buffer
#define JAVA_C_CHAR_ARRAY_COPY_BACK(INPUT, SIZE) char* INPUT ## _temp_buffer = java_byte_array_to_char_array(env, INPUT ## _buffer); memcpy((void *) INPUT, INPUT ## _temp_buffer, SIZE); safe_release_byte_array_elements(env, INPUT ## _buffer, (signed char *) INPUT ## _temp_buffer);

#define RELEASE_JAVA_CHAR_ARRAY(INPUT) safe_delete_local_ref(env, INPUT ## _buffer);

#define JAVA_C_CHAR_ARRAY(INPUT) char* INPUT ## _buffer = java_byte_array_to_char_array(env, INPUT);
#define RELEASE_C_CHAR_ARRAY(INPUT) safe_release_byte_array_elements_copy_back(env, INPUT, (signed char *) INPUT ## _buffer);

// For int arrays
#define C_JAVA_INT_ARRAY(INPUT, LENGTH) jintArray INPUT ## _buffer = int_array_to_java_int_array(env, (int *) INPUT, LENGTH);
#define INT_ARRAY_UNROLL(INPUT) INPUT ## _buffer
#define JAVA_C_INT_ARRAY_COPY_BACK(INPUT, SIZE) int* INPUT ## _temp_buffer = java_int_array_to_int_array(env, INPUT ## _buffer); memcpy((void *) INPUT, INPUT ## _temp_buffer, SIZE); safe_release_int_array_elements(env, INPUT ## _buffer, (int *) INPUT ## _temp_buffer);

#define RELEASE_JAVA_INT_ARRAY(INPUT) safe_delete_local_ref(env, INPUT ## _buffer);

#define JAVA_C_INT_ARRAY(INPUT) int* INPUT ## _buffer = java_int_array_to_int_array(env, INPUT);
#define RELEASE_C_INT_ARRAY(INPUT) safe_release_int_array_elements_copy_back(env, INPUT, (int *) INPUT ## _buffer);

// For strings
#define JAVA_C_STRING(INPUT) const char *INPUT ## _buffer = (*env)->GetStringUTFChars(env, INPUT, NULL);
#define STRING_UNROLL(INPUT) INPUT ## _buffer
#define RELEASE_C_STRING(INPUT) (*env)->ReleaseStringUTFChars(env, INPUT, INPUT ## _buffer);

#define C_JAVA_STRING(INPUT) jstring INPUT ## _buffer = (*env)->NewStringUTF(env, INPUT);
#define RELEASE_JAVA_STRING(INPUT) safe_delete_local_ref(env, INPUT ## _buffer)

// For sockaddr
#define REFERENCE_SOCKADDR_CLASS_NAME "Lcom/timmattison/sjmmie/objects/ReferenceSockaddr;"
#define REFERENCE_SOCKADDR_SA_LEN_FIELD_NAME "sa_len"
#define REFERENCE_SOCKADDR_SA_FAMILY_FIELD_NAME "sa_family"
#define REFERENCE_SOCKADDR_SA_DATA_FIELD_NAME "sa_data"


// For getting the current Sjmmie instance
extern jobject sjmmie_instance;

// For intercepting "open"
extern const char *open_interceptor_name;
extern const char *open_interceptor_arguments;
extern jmethodID java_open_method;

// For intercepting "close"
extern const char *close_interceptor_name;
extern const char *close_interceptor_arguments;
extern jmethodID java_close_method;

// For intercepting "connect"
extern const char *connect_interceptor_name;
extern const char *connect_interceptor_arguments;
extern jmethodID java_connect_method;

// For intercepting "sendto"
extern const char *sendto_interceptor_name;
extern const char *sendto_interceptor_arguments;
extern jmethodID java_sendto_method;

// For intercepting "recvfrom"
extern const char *recvfrom_interceptor_name;
extern const char *recvfrom_interceptor_arguments;
extern jmethodID java_recvfrom_method;

// For intercepting "socket"
extern const char *socket_interceptor_name;
extern const char *socket_interceptor_arguments;
extern jmethodID java_socket_method;

// For intercepting "send"
extern const char *send_interceptor_name;
extern const char *send_interceptor_arguments;
extern jmethodID java_send_method;

// For intercepting "recv"
extern const char *recv_interceptor_name;
extern const char *recv_interceptor_arguments;
extern jmethodID java_recv_method;

// For intercepting "recvmsg"
extern const char *recvmsg_interceptor_name;
extern const char *recvmsg_interceptor_arguments;
extern jmethodID java_recvmsg_method;

#endif // SJMMIE_HEADER
