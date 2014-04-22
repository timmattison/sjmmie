#include "sjmmie.h"

// For sockaddr
#define C_JAVA_SOCKADDR(INPUT, LENGTH) jbyteArray INPUT ## _buffer = copy_c_to_java_sockaddr(env, (struct sockaddr *) INPUT, LENGTH);
#define JAVA_SOCKADDR_UNROLL(INPUT) ((INPUT == NULL) ? 0 : INPUT->sa_family), INPUT ## _buffer
#define RELEASE_JAVA_SOCKADDR(INPUT) safe_delete_local_ref(env, INPUT ## _buffer);

#define JAVA_C_SOCKADDR(INPUT, ADDRLEN) \
char* INPUT ## _buffer = NULL; \
if(INPUT != NULL) { \
INPUT ## _buffer = java_byte_array_to_char_array(env, (char *) INPUT); \
}
#define C_SOCKADDR_UNROLL(INPUT) ((INPUT == NULL) ? NULL : *INPUT ## _buffer)
#define RELEASE_C_SOCKADDR(INPUT) safe_release_byte_array_elements(env, INPUT, (signed char *) INPUT ## _buffer);

char const *sa_len_field_name = "sa_len";
char const *sa_family_field_name = "sa_family";
char const *sa_data_field_name = "sa_data";

jobject sockaddr_to_reference_sockaddr(JNIEnv *env, struct sockaddr *address, int address_length) {
    jclass reference_sockaddr_class = (*env)->FindClass(env, reference_sockaddr_class);
    jmethodID reference_sockaddr_constructor = (*env)->GetMethodID(env, reference_sockaddr_class, "<init>", no_arguments);
    jobject reference_sockaddr_object = (*env)->NewObject(env, reference_sockaddr_class, reference_sockaddr_constructor);

    jfieldID sa_len_field = (*env)->GetFieldID(env, reference_sockaddr_class, sa_len_field_name, "I");
    (*env)->SetObjectField(env, reference_sockaddr_object, sa_len_field, address->sa_len);

    jfieldID sa_family_field = (*env)->GetFieldID(env, reference_sockaddr_class, sa_family_field_name, "I");
    (*env)->SetObjectField(env, reference_sockaddr_object, sa_family_field, address->sa_family);

    jfieldID sa_data_field = (*env)->GetFieldID(env, reference_sockaddr_class, sa_data_field_name, "[B");
    jbyteArray sa_data_byte_array = (*env)->NewByteArray(env, address_length);
    (*env)->SetByteArrayRegion(env, sa_data_byte_array, 0, address_length, (jbyte*) address->sa_data);
    (*env)->SetObjectField(env, reference_sockaddr_object, sa_data_field, sa_data_byte_array);

    return reference_sockaddr_object;
}

struct sockaddr *reference_sockaddr_to_sockaddr(JNIEnv *env, jobject reference_sockaddr_object, int *address_length) {
    struct sockaddr *out = calloc(1, sizeof(struct sockaddr));

    jclass reference_sockaddr_class = (*env)->FindClass(env, reference_sockaddr_class);

    jfieldID sa_len_field = (*env)->GetFieldID(env, reference_sockaddr_class, sa_len_field_name, "I");
    out->sa_len = (*env)->GetObjectField(env, reference_sockaddr_object, sa_len_field);

    jfieldID sa_family_field = (*env)->GetFieldID(env, reference_sockaddr_class, sa_family_field_name, "I");
    out->sa_family = (*env)->GetObjectField(env, reference_sockaddr_object, sa_family_field);

    jfieldID sa_data_field = (*env)->GetFieldID(env, reference_sockaddr_class, sa_data_field_name, "[B");
    jbyteArray sa_data_field_byte_array = (*env)->GetObjectField(env, reference_sockaddr_object, sa_data_field);
    char *sa_data = (*env)->GetByteArrayElements(env, sa_data_field_byte_array, 0);
    address_length = (*env)->GetArrayLength(env, sa_data_field_byte_array);
    char *sa_data_dest = out->sa_data;
    sa_data_dest = calloc(1, address_length);
    memcpy(sa_data_dest, sa_data, address_length);

    return out;
}