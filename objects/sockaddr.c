#include "sjmmie.h"

jobject sockaddr_to_reference_sockaddr(JNIEnv *env, struct sockaddr *address, int address_length) {
    // Address length is the length of the whole address structure including sa_len and sa_family.
    // We must subtract out the length of these fields to get the length of the sa_data field.
    address_length -= sizeof(address->sa_len);
    address_length -= sizeof(address->sa_family);

    jclass reference_sockaddr_class = (*env)->FindClass(env, REFERENCE_SOCKADDR_CLASS_NAME);
    jmethodID reference_sockaddr_constructor = get_no_args_constructor(env, reference_sockaddr_class);
    jobject reference_sockaddr_object = (*env)->NewObject(env, reference_sockaddr_class, reference_sockaddr_constructor);

    set_int_field(env, reference_sockaddr_class, reference_sockaddr_object, REFERENCE_SOCKADDR_SA_LEN_FIELD_NAME, address->sa_len);
    set_int_field(env, reference_sockaddr_class, reference_sockaddr_object, REFERENCE_SOCKADDR_SA_FAMILY_FIELD_NAME, address->sa_family);

    set_byte_array_field(env, reference_sockaddr_class, reference_sockaddr_object, REFERENCE_SOCKADDR_SA_DATA_FIELD_NAME, address->sa_data, address_length);

    return reference_sockaddr_object;
}

struct sockaddr *reference_sockaddr_to_sockaddr(JNIEnv *env, jobject reference_sockaddr_object, int *address_length) {
    jclass reference_sockaddr_class = (*env)->FindClass(env, REFERENCE_SOCKADDR_CLASS_NAME);

    char *sa_data = get_byte_array_field(env, reference_sockaddr_class, reference_sockaddr_object, REFERENCE_SOCKADDR_SA_DATA_FIELD_NAME, address_length);

    int sa_len_size = member_size(struct sockaddr, sa_len);
    int sa_family_size = member_size(struct sockaddr, sa_family);

    int full_structure_length = *address_length + sa_len_size + sa_family_size;
    struct sockaddr *out = calloc(1, full_structure_length);

    out->sa_len = get_int_field(env, reference_sockaddr_class, reference_sockaddr_object, REFERENCE_SOCKADDR_SA_LEN_FIELD_NAME);
    out->sa_family = get_int_field(env, reference_sockaddr_class, reference_sockaddr_object, REFERENCE_SOCKADDR_SA_FAMILY_FIELD_NAME);
    char *sa_data_dest = out->sa_data;
    memcpy(sa_data_dest, sa_data, *address_length);

    // Address length needs to be the length of the whole address structure including sa_len and sa_family.
    // We must add back the length of these fields to get the length of the entire structure.
    *address_length += sizeof(out->sa_len);
    *address_length += sizeof(out->sa_family);

    return out;
}

void free_sockaddr(struct sockaddr *to_free) {
    if(to_free != NULL) {
        free(to_free);
    }
}