struct sockaddr *reference_msghdr_to_msghdr(JNIEnv *env, jobject reference_sockaddr_object, int *address_length);
jobject msghdr_to_reference_msghdr(JNIEnv *env, struct msghdr *msghdr, int address_length);
