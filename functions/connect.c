#include "../sjmmie.h"

#include <netinet/in.h>
#include <string.h>

jmethodID java_connect_method;

const char *connect_interceptor_name = "connectInterceptor";
const char *connect_interceptor_arguments = "(I" REFERENCE_SOCKADDR_CLASS_NAME ")I";

jmethodID connect_interceptor;

/**
 * Java calls back into this function when it wants to call back to the original connect function
 */
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalConnect(JNIEnv *env, jobject obj, jint s, jobject reference_sockaddr_object) {
	int return_value;

	// Rebuild the sockaddr structure
    int address_length;
    struct sockaddr* address = reference_sockaddr_to_sockaddr(env, reference_sockaddr_object, &address_length);

	// Call the original function and store the result
	return_value = connect(s, address, address_length);

	// Return the result
	return return_value;
}

/**
 * This overrides the original connect function
 */
int SJMMIE_connect(int s, const struct sockaddr *name, socklen_t namelen) {
    printf("SJMMIE_connect %d %d\n", name->sa_len, namelen);

    if(name->sa_family == AF_INET) {
        struct sockaddr_in *name4 = name;
        int total_size = sizeof(struct sockaddr_in);
        int computed_total_size = sizeof(name4->sin_addr) + sizeof(name4->sin_family) + sizeof(name4->sin_len) + sizeof(name4->sin_port) + sizeof(name4->sin_zero);
        printf("SJMMIE_connect IPv4 size %d %d\n", total_size, computed_total_size);
    }
    else if(name->sa_family == AF_INET6) {
        struct sockaddr_in6 *name6 = name;
        int total_size = sizeof(struct sockaddr_in6);
        int computed_total_size = sizeof(name6->sin6_addr) + sizeof(name6->sin6_family) + sizeof(name6->sin6_flowinfo) + sizeof(name6->sin6_len) + sizeof(name6->sin6_port) + sizeof(name6->sin6_scope_id);
        printf("SJMMIE_connect IPv6 size %d %d\n", total_size, computed_total_size);
    }

    if(java_connect_method != NULL) {
        printf("SJMMIE_connect SUCCESS 1\n");
		JNIEnv *env = get_env();

        printf("SJMMIE_connect SUCCESS 2\n");
        jobject reference_sockaddr_object = sockaddr_to_reference_sockaddr(env, name, namelen);

        printf("SJMMIE_connect SUCCESS 3\n");
		jint return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_connect_method, s, reference_sockaddr_object);

        printf("SJMMIE_connect SUCCESS 4\n");
		return return_value;
	}
	else {
        printf("SJMMIE_connect FAILURE\n");
		return connect(s, name, namelen);
	}
}
