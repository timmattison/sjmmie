#include "sjmmie.h"

//public class ReferenceMsghdr {
//    public byte[] msg_name;
//    public byte[][] msg_iov;
//    public byte[] msg_control;
//    public int msg_flags;
//}

#define REFERENCE_MSGHDR_MSG_NAMELEN_FIELD_NAME "msg_namelen"
#define REFERENCE_MSGHDR_MSG_IOVLEN_FIELD_NAME "msg_iovlen"
#define REFERENCE_MSGHDR_MSG_CONTROLLEN_FIELD_NAME "msg_controllen"

jobject msghdr_to_reference_msghdr(JNIEnv *env, struct msghdr *msghdr, int address_length) {
    jclass reference_msghdr_class = (*env)->FindClass(env, REFERENCE_SOCKADDR_CLASS_NAME);
    jmethodID reference_msghdr_constructor = (*env)->GetMethodID(env, reference_msghdr_class, "<init>", no_arguments);
    jobject reference_msghdr_object = (*env)->NewObject(env, reference_msghdr_class, reference_msghdr_constructor);

    jfieldID flags_field_id = (*env)->GetFieldID(env, reference_msghdr_class, REFERENCE_MSGHDR_MSG_FLAGS_FIELD_NAME, "I");
    (*env)->SetIntField(env, reference_msghdr_object, flags_field_id, msghdr->msg_flags);

    jfieldID msg_name_field_id = (*env)->GetFieldID(env, reference_msghdr_class, REFERENCE_MSGHDR_MSG_NAME_FIELD_NAME, "[B");
    jbyteArray msg_name_byte_array = (*env)->NewByteArray(env, address_length);
    (*env)->SetByteArrayRegion(env, msg_name_byte_array, 0, address_length, (jbyte *) msghdr->msg_name);
    (*env)->SetObjectField(env, reference_msghdr_object, msg_name_field_id, msg_name_byte_array);

    jfieldID msg_control_field_id = (*env)->GetFieldID(env, reference_msghdr_class, REFERENCE_MSGHDR_MSG_CONTROL_FIELD_NAME, "[B");
    jbyteArray msg_control_byte_array = (*env)->NewByteArray(env, address_length);
    (*env)->SetByteArrayRegion(env, msg_control_byte_array, 0, address_length, (jbyte *) msghdr->msg_control);
    (*env)->SetObjectField(env, reference_msghdr_object, msg_control_field_id, msg_control_byte_array);

    return reference_msghdr_object;
}

struct sockaddr *reference_msghdr_to_msghdr(JNIEnv *env, jobject reference_sockaddr_object, int *address_length) {
    jclass reference_sockaddr_class = (*env)->FindClass(env, REFERENCE_SOCKADDR_CLASS_NAME);

    jfieldID sa_len_field_id = (*env)->GetFieldID(env, reference_sockaddr_class, REFERENCE_SOCKADDR_SA_LEN_FIELD_NAME, "I");

    jfieldID sa_family_field_id = (*env)->GetFieldID(env, reference_sockaddr_class, REFERENCE_SOCKADDR_SA_FAMILY_FIELD_NAME, "I");

    jfieldID sa_data_field_id = (*env)->GetFieldID(env, reference_sockaddr_class, REFERENCE_SOCKADDR_SA_DATA_FIELD_NAME, "[B");
    jbyteArray sa_data_field_byte_array = (*env)->GetObjectField(env, reference_sockaddr_object, sa_data_field_id);
    char *sa_data = (*env)->GetByteArrayElements(env, sa_data_field_byte_array, 0);
    *address_length = (int) (*env)->GetArrayLength(env, sa_data_field_byte_array);

    int sa_len_size = member_size(struct sockaddr, sa_len);
    int sa_family_size = member_size(struct sockaddr, sa_family);

    int full_structure_length = *address_length + sa_len_size + sa_family_size;
    struct sockaddr *out = calloc(1, full_structure_length);

    out->sa_len = (*env)->GetIntField(env, reference_sockaddr_object, sa_len_field_id);
    out->sa_family = (*env)->GetIntField(env, reference_sockaddr_object, sa_family_field_id);
    char *sa_data_dest = out->sa_data;
    memcpy(sa_data_dest, sa_data, *address_length);

    // Address length needs to be the length of the whole address structure including sa_len and sa_family.
    // We must add back the length of these fields to get the length of the entire structure.
    *address_length += sizeof(out->sa_len);
    *address_length += sizeof(out->sa_family);

    return out;
}
