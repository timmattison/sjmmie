jobject sockaddr_to_reference_sockaddr(JNIEnv *env, struct sockaddr *address, int address_length);
struct sockaddr *reference_sockaddr_to_sockaddr(JNIEnv *env, jobject reference_sockaddr_object, int *address_length);
void free_sockaddr(struct sockaddr *to_free);