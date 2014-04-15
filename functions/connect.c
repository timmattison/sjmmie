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
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalConnect(JNIEnv *env, jobject obj, jint s, jchar sa_family, jbyteArray sa_data_java, jint namelen) {
	int return_value;

	// Rebuild the sockaddr structure
    JAVA_C_SOCKADDR(sa_data_java, namelen);

	// Call the original function and store the result
	return_value = connect(s, C_SOCKADDR_UNROLL(sa_data_java), namelen);

	// Release the memory for the copy of the string data
    RELEASE_C_SOCKADDR(sa_data_java);

	// Return the result
	return return_value;
}

/**
 * This overrides the original connect function
 */
int SJMMIE_connect(int s, const struct sockaddr *name, socklen_t namelen) {
	if(java_connect_method != NULL) {
		JNIEnv *env = get_env();

        C_JAVA_SOCKADDR(name, namelen);

		jint return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_connect_method, s, JAVA_SOCKADDR_UNROLL(name), namelen);

        RELEASE_JAVA_SOCKADDR(name);
	
		return return_value;
	}
	else {
		return connect(s, name, namelen);
	}
}
