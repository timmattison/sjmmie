#include "../sjmmie.h"

#include <netinet/in.h>
#include <string.h>

jmethodID java_send_method;

const char *send_interceptor_name = "sendInterceptor";
const char *send_interceptor_arguments = "(I[BII)I";

jmethodID send_interceptor;

/**
 * Java calls back into this function when it wants to call back to the original send function
 */
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalSend(JNIEnv *env, jobject obj, jint socket, jbyteArray buf_java, jint length, jint flags) {
	int return_value;

	// Get the bytes back
	char* buf_c = java_byte_array_to_char_array(env, buf_java);

	// Call the original function and store the result
	return_value = send(socket, buf_c, length, flags);

	// Release the memory for the copy of the string data
	safe_release_byte_array_elements(env, buf_java, (signed char *) buf_c);

	// Return the result
	return return_value;
}

/**
 * This overrides the original send function
 */
ssize_t SJMMIE_send(int socket, const void *buffer, size_t length, int flags) {
	printf("IN SJMMIE_send\n");
	if(java_send_method != NULL) {
		JNIEnv *env = get_env();

		jbyteArray data_to_send_java = char_array_to_java_byte_array(env, (char *) buffer, length);

		jint return_value;

		return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_send_method, socket, data_to_send_java, length, flags);

		safe_delete_local_ref(env, data_to_send_java);
	
		return return_value;
	}
	else {
		return send(socket, buffer, length, flags);
	}
}
