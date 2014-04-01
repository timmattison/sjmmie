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
    JAVA_C_CHAR_ARRAY(buf_java);

	// Call the original function and store the result
	return_value = send(socket, CHAR_ARRAY_UNROLL(buf_java), length, flags);

	// Release the memory for the copy of the string data
    RELEASE_C_CHAR_ARRAY(buf_java);

	// Return the result
	return return_value;
}

/**
 * This overrides the original send function
 */
ssize_t SJMMIE_send(int socket, const void *buffer, size_t length, int flags) {
	if(java_send_method != NULL) {
		JNIEnv *env = get_env();

        C_JAVA_CHAR_ARRAY(buffer, length);

        jint return_value;

		return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_send_method, socket, CHAR_ARRAY_UNROLL(buffer), length, flags);

        // Copy the data back from Java to C and release the Java copy immediately
        JAVA_C_CHAR_ARRAY_COPY_BACK(buffer, length);

        // Release the copy of the original C data
        RELEASE_JAVA_CHAR_ARRAY(buffer);

        return return_value;
	}
	else {
		return send(socket, buffer, length, flags);
	}
}
