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
    printf("1\n");
    jclass reference_sockaddr_class = (*env)->FindClass(env, REFERENCE_SOCKADDR_CLASS_NAME);

    printf("2\n");
    char *sa_data = get_byte_array_field(env, reference_sockaddr_class, reference_sockaddr_object, REFERENCE_SOCKADDR_SA_DATA_FIELD_NAME, address_length);

    printf("3\n");
    int sa_len_size = member_size(struct sockaddr, sa_len);
    printf("4\n");
    int sa_family_size = member_size(struct sockaddr, sa_family);

    printf("5\n");
    int full_structure_length = *address_length + sa_len_size + sa_family_size;
    printf("6\n");
    struct sockaddr *out = calloc(1, full_structure_length);

    printf("7\n");
    out->sa_len = get_int_field(env, reference_sockaddr_class, reference_sockaddr_object, REFERENCE_SOCKADDR_SA_LEN_FIELD_NAME);
    printf("8\n");
    out->sa_family = get_int_field(env, reference_sockaddr_class, reference_sockaddr_object, REFERENCE_SOCKADDR_SA_FAMILY_FIELD_NAME);
    printf("9\n");
    char *sa_data_dest = out->sa_data;
    printf("10\n");
    memcpy(sa_data_dest, sa_data, *address_length);

    // Address length needs to be the length of the whole address structure including sa_len and sa_family.
    // We must add back the length of these fields to get the length of the entire structure.
    printf("11\n");
    *address_length += sizeof(out->sa_len);
    printf("12\n");
    *address_length += sizeof(out->sa_family);

    printf("13\n");
    return out;
}

void free_sockaddr(struct sockaddr *to_free) {
    if(to_free != NULL) {
        free(to_free);
    }
}