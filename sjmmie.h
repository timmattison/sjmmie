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

// For character arrays
#define C_JAVA_CHAR_ARRAY(INPUT, LENGTH) jbyteArray INPUT ## _buffer = char_array_to_java_byte_array(env, (char *) INPUT, LENGTH);
#define CHAR_ARRAY_UNROLL(INPUT) INPUT ## _buffer
#define JAVA_C_CHAR_ARRAY_COPY_BACK(INPUT, SIZE) char* INPUT ## _temp_buffer = java_byte_array_to_char_array(env, INPUT ## _buffer); memcpy((void *) INPUT, INPUT ## _temp_buffer, SIZE); safe_release_byte_array_elements(env, INPUT ## _buffer, (signed char *) INPUT ## _temp_buffer);

#define RELEASE_JAVA_CHAR_ARRAY(INPUT) safe_delete_local_ref(env, INPUT ## _buffer);

#define JAVA_C_CHAR_ARRAY(INPUT) char* INPUT ## _buffer = java_byte_array_to_char_array(env, INPUT);
#define RELEASE_C_CHAR_ARRAY(INPUT) safe_release_byte_array_elements_copy_back(env, INPUT, (signed char *) INPUT ## _buffer);

// For strings
#define JAVA_C_STRING(INPUT) const char *INPUT ## _buffer = (*env)->GetStringUTFChars(env, INPUT, NULL);
#define STRING_UNROLL(INPUT) INPUT ## _buffer
#define RELEASE_C_STRING(INPUT) (*env)->ReleaseStringUTFChars(env, INPUT, INPUT ## _buffer);

#define C_JAVA_STRING(INPUT) jstring INPUT ## _buffer = (*env)->NewStringUTF(env, INPUT);
#define RELEASE_JAVA_STRING(INPUT) safe_delete_local_ref(env, INPUT ## _buffer)

// For sockaddr
#define C_JAVA_SOCKADDR(INPUT) jbyteArray INPUT ## _buffer = c_java_sockaddr(env, (struct sockaddr *) INPUT);
#define JAVA_SOCKADDR_UNROLL(INPUT) ((INPUT == NULL) ? 0 : INPUT->sa_family), INPUT ## _buffer
#define RELEASE_JAVA_SOCKADDR(INPUT) java_c_sockaddr(env, INPUT ## _buffer);

#define JAVA_C_SOCKADDR(INPUT, INPUT_SA_FAMILY) \
struct sockaddr INPUT ## _temp;\
INPUT ## _temp.sa_family = INPUT_SA_FAMILY; \
char* INPUT ## _buffer = NULL; \
if(INPUT != NULL) { \
INPUT ## _buffer = java_byte_array_to_char_array(env, INPUT); \
memcpy(&INPUT ## _temp.sa_data[0], INPUT ## _buffer, sizeof(INPUT ## _temp.sa_data)); \
}
#define C_SOCKADDR_UNROLL(INPUT) ((INPUT == NULL) ? NULL : &INPUT ## _temp)
#define RELEASE_C_SOCKADDR(INPUT) safe_release_byte_array_elements(env, INPUT, (signed char *) INPUT ## _buffer);

// For msghdr
#define C_JAVA_MSGHDR(INPUT) jbyteArray INPUT ## _msg_name = char_array_to_java_byte_array(env, (char *) INPUT.msg_name, INPUT.msg_namelen); \
jclass byteArrayClass = (*env)->FindClass(env, "[B"); \
jobjectArray INPUT ## _msg_iov = (*env)->NewObjectArray(env, (jsize) INPUT.msg_iovlen, byteArrayClass, NULL); \
jbyteArray[] INPUT ## _iovec = calloc(INPUT.msg_iovlen, sizeof(socklen_t)); \
for(int INPUT ## _temp_loop = 0; INPUT ## _temp_loop < INPUT.msg_iovlen; INPUT ## _temp_loop++) { \
  INPUT ## _iovec[INPUT ## _temp_loop] = char_array_to_java_byte_array(env, (char *) INPUT.msg_iov[INPUT ## _temp_loop], INPUT.msg_iov.iov_len); \
} \
jbyteArray INPUT ## _msg_control = char_array_to_java_byte_array(env, (char *) INPUT.msg_control, INPUT.msg_controllen);
#define JAVA_MSGHDR_UNROLL(INPUT) INPUT ## _msg_name, INPUT.msg_namelen, INPUT ## _msg_iov, INPUT.msg_iovlen, INPUT ## _msg_control, INPUT.msg_controllen, INPUT.msg_flags

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
