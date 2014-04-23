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

jobject sockaddr_to_reference_sockaddr(JNIEnv *env, struct sockaddr *address, int address_length) {
    address_length -= sizeof(address->sa_len);
    address_length -= sizeof(address->sa_family);

    jclass reference_sockaddr_class = (*env)->FindClass(env, REFERENCE_SOCKADDR_CLASS_NAME);
    jmethodID reference_sockaddr_constructor = (*env)->GetMethodID(env, reference_sockaddr_class, "<init>", no_arguments);
    jobject reference_sockaddr_object = (*env)->NewObject(env, reference_sockaddr_class, reference_sockaddr_constructor);

    jfieldID sa_len_field_id = (*env)->GetFieldID(env, reference_sockaddr_class, REFERENCE_SOCKADDR_SA_LEN_FIELD_NAME, "I");
    (*env)->SetIntField(env, reference_sockaddr_object, sa_len_field_id, address->sa_len);

    jfieldID sa_family_field_id = (*env)->GetFieldID(env, reference_sockaddr_class, REFERENCE_SOCKADDR_SA_FAMILY_FIELD_NAME, "I");
    (*env)->SetIntField(env, reference_sockaddr_object, sa_family_field_id, address->sa_family);

    jfieldID sa_data_field_id = (*env)->GetFieldID(env, reference_sockaddr_class, REFERENCE_SOCKADDR_SA_DATA_FIELD_NAME, "[B");
    jbyteArray sa_data_byte_array = (*env)->NewByteArray(env, address_length);
    (*env)->SetByteArrayRegion(env, sa_data_byte_array, 0, address_length, (jbyte *) address->sa_data);
    (*env)->SetObjectField(env, reference_sockaddr_object, sa_data_field_id, sa_data_byte_array);

    return reference_sockaddr_object;
}

struct sockaddr *reference_sockaddr_to_sockaddr(JNIEnv *env, jobject reference_sockaddr_object, int *address_length) {
    struct sockaddr *out = calloc(1, sizeof(struct sockaddr));

    jclass reference_sockaddr_class = (*env)->FindClass(env, REFERENCE_SOCKADDR_CLASS_NAME);

    jfieldID sa_len_field_id = (*env)->GetFieldID(env, reference_sockaddr_class, REFERENCE_SOCKADDR_SA_LEN_FIELD_NAME, "I");
    out->sa_len = (*env)->GetIntField(env, reference_sockaddr_object, sa_len_field_id);

    jfieldID sa_family_field_id = (*env)->GetFieldID(env, reference_sockaddr_class, REFERENCE_SOCKADDR_SA_FAMILY_FIELD_NAME, "I");
    out->sa_family = (*env)->GetIntField(env, reference_sockaddr_object, sa_family_field_id);

    jfieldID sa_data_field_id = (*env)->GetFieldID(env, reference_sockaddr_class, REFERENCE_SOCKADDR_SA_DATA_FIELD_NAME, "[B");
    jbyteArray sa_data_field_byte_array = (*env)->GetObjectField(env, reference_sockaddr_object, sa_data_field_id);
    char *sa_data = (*env)->GetByteArrayElements(env, sa_data_field_byte_array, 0);
    *address_length = (int) (*env)->GetArrayLength(env, sa_data_field_byte_array);
    char *sa_data_dest = out->sa_data;
    memcpy(sa_data_dest, sa_data, *address_length);

    *address_length += sizeof(out->sa_len);
    *address_length += sizeof(out->sa_family);

    return out;
}