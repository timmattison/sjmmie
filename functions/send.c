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
    char *buf_c = java_byte_array_to_char_array(env, buf_java);

	// Call the original function and store the result
	return_value = send(socket, buf_c, length, flags);

    // Release the memory for the copy of the string data
    free(buf_c);

	// Return the result
	return return_value;
}

/**
 * This overrides the original send function
 */
ssize_t SJMMIE_send(int socket, const void *buffer, size_t length, int flags) {
	if(java_send_method != NULL) {
		JNIEnv *env = get_env();

        jbyteArray buf_java = char_array_to_java_byte_array(env, buffer, length);

        jint return_value;

		return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_send_method, socket, buf_java, length, flags);

        // Copy the data back from Java to C and release the Java copy immediately
        java_byte_array_to_existing_char_array(env, buf_java, &buffer, length);

        // Release the copy of the original C data
        safe_delete_local_ref(env, buf_java);

        return return_value;
	}
	else {
		return send(socket, buffer, length, flags);
	}
}
