#include "sjmmie.h"

// For converting Java arrays to char/byte arrays
void java_byte_array_to_existing_char_array(JNIEnv *env, jbyteArray java_byte_array, char **output, int length) {
    printf("a\n");
    char *data = java_byte_array_to_char_array(env, java_byte_array);

    // Did they specify a fixed size?
    if (length == -1) {
        // No, is the buffer allocated already?
        printf("b\n");
        if (*output != NULL) {
            // Yes, free it and mark it as NULL
            printf("c\n");
            free(*output);
            printf("d\n");
            *output = NULL;
        }
    }

    // Is there any data to copy?
    if (data == NULL) {
        printf("e\n");
        // No, just return
        return;
    }

    // Get the length of the Java data
    printf("f\n");
    int java_length = (int) (*env)->GetArrayLength(env, java_byte_array);

    // Did they specify a fixed size?
    if (length == -1) {
        // No, allocate enough space to fit the data from Java
        printf("g\n");
        *output = calloc(1, java_length);

        // Set the length to the length of the data from Java
        printf("h\n");
        length = java_length;
    }
    else {
        // Yes, choose the smaller of the fixed size and the Java array length
        printf("i\n");
        length = (length < java_length) ? length : java_length;
    }

    // Copy the data
    printf("j\n");
    memcpy(*output, data, length);

    printf("k\n");
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
jbyteArray char_array_to_java_byte_array(JNIEnv *env, char *c_buffer, int c_buffer_length) {
    if (c_buffer == NULL) {
        return NULL;
    }

    jbyteArray java_byte_array = (*env)->NewByteArray(env, c_buffer_length);
    (*env)->SetByteArrayRegion(env, java_byte_array, 0, c_buffer_length, (jbyte *) c_buffer);

    return java_byte_array;
}

void print_java_array(JNIEnv *env, char *message, jbyteArray array) {
    int java_length = (int) (*env)->GetArrayLength(env, array);
    jbyte *bytes = (*env)->GetByteArrayElements(env, array, 0);

    print_c_array(message, bytes, java_length);
}

void print_c_array(char *message, void *array, int size) {
    if(message != NULL) {
        printf("%s\n", message);
    }

    for(int loop = 0; loop < size; loop++) {
        printf("[%d] - %d %c\n", loop, ((char *) array)[loop], ((char *) array)[loop]);
    }
}
