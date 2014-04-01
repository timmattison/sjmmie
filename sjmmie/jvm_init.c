#include "sjmmie.h"

const char *static_initializer_name = "getInstance";
const char *static_initializer_signature = "()Lcom/timmattison/sjmmie/Sjmmie;";

JavaVM* jvm;
jclass sjmmie_class;
jobject sjmmie_instance;

jmethodID sjmmie_static_initializer;

int count_and_set_jvm_options(char *jvm_options_string, JavaVMOption *options) {
    const char *separator = " ";
    char *token;
    int option_count = 0;

    char *copy_of_string = (char *) malloc(strlen(jvm_options_string));
    strcpy(copy_of_string, jvm_options_string);

    // Get the first token
    token = strtok(copy_of_string, separator);

    while(token != NULL) {
        if(options != NULL) {
            // XXX - LEAK
            options[option_count].optionString = (char *) malloc(strlen(token + 1));
            strcpy(options[option_count].optionString, token);
        }

        option_count++;
        token = strtok(NULL, separator);
    }

    free(copy_of_string);

    return option_count;
}

JNIEnv* attach_environment() {
    JNIEnv* env;

    int getEnvStat = (*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_6);

    if (getEnvStat == JNI_EDETACHED) {
        if ((*jvm)->AttachCurrentThread(jvm, (void **) &env, NULL) != 0) {
            printf("Failed to attach\n");
            exit(1);
        }
    }

    return env;
}

JNIEnv* get_env() {
    // Have we already been initialized?
    if(initialized == INITIALIZED) {
        // Yes, just make sure the environment is attached
        return attach_environment();
    }

    // Are we in the process of initializing?
    if(initialized == INITIALIZING) {
        // Yes, don't try to initialize again
        return NULL;
    }

    // Indicate that we are in the process of initializing
    initialized = INITIALIZING;

    // Get the JVM options (usually at least -D to specify where the classes live)
    char *jvm_options_string = getenv(SJMMIE_JVM_OPTS_VARIABLE);

    // Get the name of the class that we'll be using to load our callbacks
    char *class              = getenv(SJMMIE_CLASS_VARIABLE);

    // Did they specify a class?
    if(class == NULL) {
        // No, we can't continue without a class name
        printf("No Sjmmie class specified in the %s environment variable.  Cannot continue.\n", SJMMIE_CLASS_VARIABLE);
        exit(1);
    }

    JavaVMInitArgs args;

    int jvm_option_count = count_and_set_jvm_options(jvm_options_string, NULL);

    // XXX - LEAK
    JavaVMOption *options = (JavaVMOption*) calloc(jvm_option_count, sizeof(JavaVMOption));

    args.version = JNI_VERSION_1_6;
    args.nOptions = count_and_set_jvm_options(jvm_options_string, options);
    args.options = options;
    args.ignoreUnrecognized = JNI_FALSE;

    // Create a new JVM
    JNIEnv* env;
    jint res = JNI_CreateJavaVM(&jvm, (void **)&env, &args);

    if(res < 0) {
        printf("JNI_CreateJavaVM failed with error code %d\n", res);
        exit(1);
    }

    if(jvm == NULL) {
        printf("Couldn't create JVM\n");
        exit(1);
    }

    if(env == NULL) {
        printf("Couldn't get a JVM environment\n");
        exit(1);
    }

    // Look up the class that they specified
    sjmmie_class = (*env)->FindClass(env, class);

    // Did we find the class?
    if(sjmmie_class == NULL) {
        // No, we can't continue without a class
        printf("Didn't find the Sjmmie class, exiting\n");
        exit(1);
    }

    // Get a global reference to the class
    sjmmie_class = (jclass) (*env)->NewGlobalRef(env, sjmmie_class);

    // Get the static initializer for this class
    sjmmie_static_initializer = (*env)->GetStaticMethodID(env, sjmmie_class, static_initializer_name, static_initializer_signature);

    // Call the static initializer to get an instance of the object
    sjmmie_instance = (*env)->CallStaticObjectMethod(env, sjmmie_class, sjmmie_static_initializer);

    // Get a global reference to the instance we just created
    sjmmie_instance = (*env)->NewGlobalRef(env, sjmmie_instance);

    // Get a reference to the methods we're intercepting

    // open
    java_open_method = (*env)->GetMethodID(env, sjmmie_class, open_interceptor_name, open_interceptor_arguments);

    // close
    java_close_method = (*env)->GetMethodID(env, sjmmie_class, close_interceptor_name, close_interceptor_arguments);

    // connect
    java_connect_method = (*env)->GetMethodID(env, sjmmie_class, connect_interceptor_name, connect_interceptor_arguments);

    // sendto
    java_sendto_method = (*env)->GetMethodID(env, sjmmie_class, sendto_interceptor_name, sendto_interceptor_arguments);

    // socket
    java_socket_method = (*env)->GetMethodID(env, sjmmie_class, socket_interceptor_name, socket_interceptor_arguments);

    // send
    java_send_method = (*env)->GetMethodID(env, sjmmie_class, send_interceptor_name, send_interceptor_arguments);

    // recv
    java_recv_method = (*env)->GetMethodID(env, sjmmie_class, recv_interceptor_name, recv_interceptor_arguments);

    // Indicate that we are initialized
    initialized = INITIALIZED;

    return attach_environment();
}