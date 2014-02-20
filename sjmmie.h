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
void get_env();
extern JNIEnv* env;

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

#endif // SJMMIE_HEADER
