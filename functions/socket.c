#include "../sjmmie.h"

jmethodID java_socket_method;
jmethodID socket_interceptor;

const char *socket_interceptor_name = "socketInterceptor";
const char *socket_interceptor_arguments = "(III)I";

/**
 * Java calls back into this function when it wants to call back to the original socket function
 */
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalSocket(JNIEnv *env, jobject obj, jint domain, jint type, jint protocol) {
	// Call the original function and store the result
	return socket(domain, type, protocol);
}

/**
 * This overrides the original socket function
 */
int SJMMIE_socket(int domain, int type, int protocol) {
	if(java_socket_method != NULL) {
		jclass socket_callback_class;

		JNIEnv *env = get_env();

		return (*env)->CallIntMethod(env, sjmmie_instance, java_socket_method, domain, type, protocol);
	}
	else {
		return socket(domain, type, protocol);
	}
}
