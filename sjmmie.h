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
#include "objects/arrays.h"

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

// For safely freeing memory
extern void safe_delete_local_ref(JNIEnv *env, jobject object);
extern void safe_release_byte_array_elements(JNIEnv *env, jbyteArray java_byte_array, signed char *c_buffer);
extern void safe_release_byte_array_elements_copy_back(JNIEnv *env, jbyteArray java_byte_array, signed char *c_buffer);
extern void safe_release_int_array_elements(JNIEnv *env, jintArray java_int_array, int *c_buffer);
extern void safe_release_int_array_elements_copy_back(JNIEnv *env, jintArray java_byte_array, int *c_buffer);

// Gem from https://stackoverflow.com/questions/3553296/c-sizeof-single-struct-member
#define member_size(type, member) sizeof(((type *)0)->member)

// General object handling
void set_int_field(JNIEnv *env, jclass class, jobject object, char *field_name, int value);
void set_byte_array_field(JNIEnv *env, jclass class, jobject object, char *field_name, char *value, int length);
jmethodID get_no_args_constructor(JNIEnv *env, jclass jclass);
int get_int_field(JNIEnv *env, jclass class, jobject object, char *field_name);
char *get_byte_array_field(JNIEnv *env, jclass class, jobject object, char *field_name, int *output_length);

// For sockaddr
#define REFERENCE_SOCKADDR_CLASS_NAME "Lcom/timmattison/sjmmie/objects/ReferenceSockaddr;"
#define REFERENCE_SOCKADDR_SA_LEN_FIELD_NAME "sa_len"
#define REFERENCE_SOCKADDR_SA_FAMILY_FIELD_NAME "sa_family"
#define REFERENCE_SOCKADDR_SA_DATA_FIELD_NAME "sa_data"

// For msghdr
#define REFERENCE_MSGHDR_CLASS_NAME "Lcom/timmattison/sjmmie/objects/ReferenceMsghdr;"
#define REFERENCE_MSGHDR_MSG_NAMELEN_FIELD_NAME "msg_namelen"
#define REFERENCE_MSGHDR_MSG_NAME_FIELD_NAME "msg_name"
#define REFERENCE_MSGHDR_MSG_IOVLEN_FIELD_NAME "msg_iovlen"
#define REFERENCE_MSGHDR_MSG_IOV_FIELD_NAME "msg_iov"
#define REFERENCE_MSGHDR_MSG_CONTROLLEN_FIELD_NAME "msg_controllen"
#define REFERENCE_MSGHDR_MSG_CONTROL_FIELD_NAME "msg_control"
#define REFERENCE_MSGHDR_MSG_FLAGS_FIELD_NAME "msg_flags"

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
