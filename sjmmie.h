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

// Converts a sockaddr from C to Java
jbyteArray c_java_sockaddr(JNIEnv *env, struct sockaddr *input);

// Frees a sockaddr that was sent to Java
void java_c_sockaddr(JNIEnv *env, jbyteArray sa_data_java);

#define C_JAVA_SOCKADDR(INPUT) jbyteArray INPUT_sa_data_java = c_java_sockaddr(env, (struct sockaddr *) INPUT);
#define SOCKADDR_UNROLL(INPUT) ((INPUT == NULL) ? 0 : INPUT->sa_family), INPUT_sa_data_java
#define RELEASE_JAVA_SOCKADDR(INPUT) java_c_sockaddr(env, INPUT_sa_data_java);

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

#endif // SJMMIE_HEADER
