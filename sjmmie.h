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

// For safely freeing memory
extern void safe_delete_local_ref(JNIEnv *env, jobject object);
extern void safe_release_byte_array_elements(JNIEnv *env, jbyteArray java_byte_array, signed char *c_buffer);
extern void safe_release_byte_array_elements_copy_back(JNIEnv *env, jbyteArray java_byte_array, signed char *c_buffer);

// For getting the current Sjmmie instance
extern jobject sjmmie_instance;

// For intercepting "open"
extern const char *open_interceptor_name;
extern const char *open_interceptor_arguments;
extern jmethodID java_open_method;
extern jmethodID open_interceptor;

// For intercepting "close"
extern const char *close_interceptor_name;
extern const char *close_interceptor_arguments;
extern jmethodID java_close_method;
extern jmethodID close_interceptor;

// For intercepting "connect"
extern const char *connect_interceptor_name;
extern const char *connect_interceptor_arguments;
extern jmethodID java_connect_method;
extern jmethodID connect_interceptor;

// For intercepting "sendto"
extern const char *sendto_interceptor_name;
extern const char *sendto_interceptor_arguments;
extern jmethodID java_sendto_method;
extern jmethodID sendto_interceptor;

// For intercepting "socket"
extern const char *socket_interceptor_name;
extern const char *socket_interceptor_arguments;
extern jmethodID java_socket_method;
extern jmethodID socket_interceptor;

// For intercepting "send"
extern const char *send_interceptor_name;
extern const char *send_interceptor_arguments;
extern jmethodID java_send_method;
extern jmethodID send_interceptor;

// For intercepting "recv"
extern const char *recv_interceptor_name;
extern const char *recv_interceptor_arguments;
extern jmethodID java_recv_method;
extern jmethodID recv_interceptor;

#endif // SJMMIE_HEADER
