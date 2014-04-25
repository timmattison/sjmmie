#include "sjmmie.h"

// For converting Java arrays to char/byte arrays
void java_byte_array_to_existing_char_array(JNIEnv *env, jbyteArray java_byte_array, char **output) {
    char *data = java_byte_array_to_char_array(env, java_byte_array);

    if(*output != NULL) {
        free(*output);
        *output = NULL;
    }

    if(data == NULL) {
        return;
    }

    int length = (int) (*env)->GetArrayLength(env, java_byte_array);

    *output = calloc(1, length);
    memcpy(*output, data, length);
}

char *java_byte_array_to_char_array(JNIEnv *env, jbyteArray java_byte_array) {
    if(java_byte_array == NULL) {
        return NULL;
    }

    return (char *) (*env)->GetByteArrayElements(env, java_byte_array, 0);
}

// For converting char/byte arrays to Java arrays
jbyteArray char_array_to_java_byte_array(JNIEnv *env, char* c_buffer, int c_buffer_length) {
    if(c_buffer == NULL) {
        return NULL;
    }

    jbyteArray java_byte_array = (*env)->NewByteArray(env, c_buffer_length);
    (*env)->SetByteArrayRegion(env, java_byte_array, 0, c_buffer_length, (jbyte*) c_buffer);

    return java_byte_array;
}
