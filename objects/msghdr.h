struct sockaddr *reference_msghdr_to_msghdr(JNIEnv *env, jobject reference_sockaddr_object);
jobject msghdr_to_reference_msghdr(JNIEnv *env, struct msghdr *msghdr);
