#include "../sjmmie.h"

#include <netinet/in.h>
#include <string.h>

jmethodID java_connect_method;

const char *connect_interceptor_name = "connectInterceptor";
const char *connect_interceptor_arguments = "(IC[BI)I";

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
	if(java_connect_method != NULL) {
		JNIEnv *env = get_env();

        jobject reference_sockaddr_object = sockaddr_to_reference_sockaddr(env, name, namelen);
        C_JAVA_SOCKADDR(name, namelen);

		jint return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_connect_method, s, reference_sockaddr_object);

        RELEASE_JAVA_SOCKADDR(name);
	
		return return_value;
	}
	else {
		return connect(s, name, namelen);
	}
}
