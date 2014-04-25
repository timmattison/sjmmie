// For converting Java arrays to char/byte arrays
extern void java_byte_array_to_existing_char_array(JNIEnv *env, jbyteArray java_byte_array, char **out, int length);
extern char *java_byte_array_to_char_array(JNIEnv *env, jbyteArray java_byte_array);

// For converting char/byte arrays to Java arrays
extern jbyteArray char_array_to_java_byte_array(JNIEnv *env, char* c_buffer, int c_buffer_length);

extern void print_c_array(char *message, void *array, int size);
extern void print_java_array(JNIEnv *env, char *message, jbyteArray array);