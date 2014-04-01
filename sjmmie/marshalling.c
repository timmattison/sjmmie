#include "sjmmie.h"

// For converting Java arrays to char/byte arrays
char* java_byte_array_to_char_array(JNIEnv *env, jbyteArray java_byte_array) {
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

// For safely freeing memory
void safe_delete_local_ref(JNIEnv *env, jobject object) {
    if(object == NULL) {
        return;
    }

    (*env)->DeleteLocalRef(env, object);
}

void safe_release_byte_array_elements(JNIEnv *env, jbyteArray java_byte_array, signed char *c_buffer) {
    if((java_byte_array == NULL) || (c_buffer == NULL)) {
        return;
    }

    (*env)->ReleaseByteArrayElements(env, java_byte_array, (signed char *) c_buffer, JNI_ABORT);
}

void safe_release_byte_array_elements_copy_back(JNIEnv *env, jbyteArray java_byte_array, signed char *c_buffer) {
    if((java_byte_array == NULL) || (c_buffer == NULL)) {
        return;
    }

    (*env)->ReleaseByteArrayElements(env, java_byte_array, (signed char *) c_buffer, 0);
}