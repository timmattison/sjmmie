#include "sjmmie.h"

jobject msghdr_to_reference_msghdr(JNIEnv *env, struct msghdr *msghdr) {
    jclass reference_msghdr_class = (*env)->FindClass(env, REFERENCE_MSGHDR_CLASS_NAME);
    jmethodID reference_msghdr_constructor = (*env)->GetMethodID(env, reference_msghdr_class, "<init>", no_arguments);
    jobject reference_msghdr_object = (*env)->NewObject(env, reference_msghdr_class, reference_msghdr_constructor);

    jfieldID msg_name_field_id = (*env)->GetFieldID(env, reference_msghdr_class, REFERENCE_MSGHDR_MSG_NAME_FIELD_NAME, "[B");
    jbyteArray msg_name_byte_array = (*env)->NewByteArray(env, msghdr->msg_namelen);
    (*env)->SetByteArrayRegion(env, msg_name_byte_array, 0, msghdr->msg_namelen, (jbyte *) msghdr->msg_name);
    (*env)->SetObjectField(env, reference_msghdr_object, msg_name_field_id, msg_name_byte_array);

    jfieldID msg_iov_field_id = (*env)->GetFieldID(env, reference_msghdr_class, REFERENCE_MSGHDR_MSG_IOV_FIELD_NAME, "[java/lang/Object;");

    // Find the byte array class
    jclass byte_array_class = (*env)->FindClass(env, "[B");

    // Create an array to hold all of the byte arrays
    jobjectArray msg_iov_object_array = (*env)->NewObjectArray(env, msghdr->msg_iovlen, byte_array_class, NULL);

    for(int loop = 0; loop < (msghdr->msg_iovlen); loop++) {
        int length = msghdr->msg_iov[loop].iov_len;
        jbyteArray iov_byte_array = (*env)->NewByteArray(env, length);
        (*env)->SetByteArrayRegion(env, iov_byte_array, 0, length, (jbyte *) msghdr->msg_iov[loop].iov_base);
        (*env)->SetObjectArrayElement(env, msg_iov_object_array, loop, iov_byte_array);
    }

    (*env)->SetObjectField(env, reference_msghdr_object, msg_iov_field_id, msg_iov_object_array);

    jfieldID msg_control_field_id = (*env)->GetFieldID(env, reference_msghdr_class, REFERENCE_MSGHDR_MSG_CONTROL_FIELD_NAME, "[B");
    jbyteArray msg_control_byte_array = (*env)->NewByteArray(env, msghdr->msg_controllen);
    (*env)->SetByteArrayRegion(env, msg_control_byte_array, 0, msghdr->msg_controllen, (jbyte *) msghdr->msg_control);
    (*env)->SetObjectField(env, reference_msghdr_object, msg_control_field_id, msg_control_byte_array);

    jfieldID msg_flags_field_id = (*env)->GetFieldID(env, reference_msghdr_class, REFERENCE_MSGHDR_MSG_FLAGS_FIELD_NAME, "I");
    (*env)->SetIntField(env, reference_msghdr_object, msg_flags_field_id, msghdr->msg_flags);

    return reference_msghdr_object;
}

struct sockaddr *reference_msghdr_to_msghdr(JNIEnv *env, jobject reference_msghdr_object) {
    jclass reference_msghdr_class = (*env)->FindClass(env, REFERENCE_MSGHDR_CLASS_NAME);

    struct msghdr *return_msghdr = calloc(1, sizeof(struct msghdr));

    return_msghdr->msg_name = get_byte_array_field(env, reference_msghdr_class, reference_msghdr_object, REFERENCE_MSGHDR_MSG_NAME_FIELD_NAME, &return_msghdr->msg_namelen);

    jobject msg_iov_field = get_object_array_field(env, reference_msghdr_class, reference_msghdr_object, REFERENCE_MSGHDR_MSG_IOV_FIELD_NAME, &return_msghdr->msg_iovlen);

    if(return_msghdr->msg_iovlen == 0) {
        return_msghdr->msg_iov = NULL;
    }
    else {
        return_msghdr->msg_iov = calloc(return_msghdr->msg_iovlen, sizeof(struct iovec));

        for(int loop = 0; loop < return_msghdr->msg_iovlen; loop++) {
            jobjectArray msg_iov = (*env)->GetObjectArrayElement(env, msg_iov_field, loop);

            return_msghdr->msg_iov[loop].iov_base = (*env)->GetByteArrayElements(env, msg_iov, 0);
            return_msghdr->msg_iov[loop].iov_len = (int) (*env)->GetArrayLength(env, msg_iov);
        }
    }

    int msg_control_length;
    char *msg_control = get_byte_array_field(env, reference_msghdr_class, reference_msghdr_object, REFERENCE_MSGHDR_MSG_CONTROL_FIELD_NAME, &msg_control_length);

    return_msghdr->msg_control = msg_control;
    return_msghdr->msg_controllen = msg_control_length;

    jfieldID msg_flags_field_id = (*env)->GetFieldID(env, reference_msghdr_class, REFERENCE_MSGHDR_MSG_FLAGS_FIELD_NAME, "I");
    return_msghdr->msg_flags = (*env)->GetIntField(env, reference_msghdr_object, msg_flags_field_id);

    return return_msghdr;
}
