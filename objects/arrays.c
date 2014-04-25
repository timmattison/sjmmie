#include "sjmmie.h"

// For converting Java arrays to char/byte arrays
void java_byte_array_to_existing_char_array(JNIEnv *env, jbyteArray java_byte_array, char **output, int length) {
    char *data = java_byte_array_to_char_array(env, java_byte_array);

    // Did they specify a fixed size?
    if (length == -1) {
        // No, is the buffer allocated already?
        if (*output != NULL) {
            // Yes, free it and mark it as NULL
            free(*output);
            *output = NULL;
        }
    }

    // Is there any data to copy?
    if (data == NULL) {
        // No, just return
        return;
    }

    // Get the length of the Java data
    int java_length = (int) (*env)->GetArrayLength(env, java_byte_array);

    // Did they specify a fixed size?
    if (length == -1) {
        // No, allocate enough space to fit the data from Java
        *output = calloc(1, java_length);

        // Set the length to the length of the data from Java
        length = java_length;
    }
    else {
        // Yes, choose the smaller of the fixed size and the Java array length
        length = (length < java_length) ? length : java_length;
    }

    // Copy the data
    memcpy(*output, data, length);

    // Free the data
    free(data);
}

char *java_byte_array_to_char_array(JNIEnv *env, jbyteArray java_byte_array) {
    if (java_byte_array == NULL) {
        return NULL;
    }

    return (char *) (*env)->GetByteArrayElements(env, java_byte_array, 0);
}

// For converting char/byte arrays to Java arrays
jbyteArray inner_char_array_to_java_byte_array(JNIEnv *env, jbyteArray java_byte_array, char *c_buffer, int c_buffer_length);

void char_array_to_existing_java_byte_array(JNIEnv *env, jbyteArray java_byte_array, char *c_buffer, int c_buffer_length) {
    inner_char_array_to_java_byte_array(*env, java_byte_array, c_buffer, c_buffer_length);
}

jbyteArray char_array_to_java_byte_array(JNIEnv *env, char *c_buffer, int c_buffer_length) {
    return inner_char_array_to_java_byte_array(*env, NULL, c_buffer, c_buffer_length);
}

jbyteArray inner_char_array_to_java_byte_array(JNIEnv *env, jbyteArray java_byte_array, char *c_buffer, int c_buffer_length) {
    // Is there any data to copy?
    printf("1\n");
    if (c_buffer == NULL) {
        // No, just return NULL
        // TODO - This doesn't quite work as expected for java_byte_array values that are passed by reference
        printf("2\n");
        return NULL;
    }

    printf("3\n");
    if (java_byte_array == NULL) {
        printf("4 %d\n", c_buffer_length);
        jbyteArray return_value = (*env)->NewByteArray(env, c_buffer_length);
        printf("5\n");
        (*env)->SetByteArrayRegion(env, return_value, 0, c_buffer_length, (jbyte *) c_buffer);
        printf("6\n");
        return return_value;
    }

    printf("7\n");
    (*env)->SetByteArrayRegion(env, java_byte_array, 0, c_buffer_length, (jbyte *) c_buffer);
    printf("8\n");
    return java_byte_array;
}

void print_java_array(JNIEnv *env, char *message, jbyteArray array) {
    int java_length = (int) (*env)->GetArrayLength(env, array);
    jbyte *bytes = (*env)->GetByteArrayElements(env, array, 0);

    print_c_array(message, bytes, java_length);
}

void print_c_array(char *message, void *array, int size) {
    if (message != NULL) {
        printf("%s\n", message);
    }

    for (int loop = 0; loop < size; loop++) {
        printf("[%d] - %d %c\n", loop, ((char *) array)[loop], ((char *) array)[loop]);
    }
}
