#include "../sjmmie.h"

#include <netinet/in.h>
#include <string.h>

jmethodID java_recv_method;

const char *recv_interceptor_name = "recvInterceptor";
const char *recv_interceptor_arguments = "(I[BII)I";

jmethodID recv_interceptor;

/**
 * Java calls back into this function when it wants to call back to the original recv function
 */
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalRecv(JNIEnv *env, jobject obj, jint socket, jbyteArray buf_java, jint size, jint flags) {
	int return_value;

	// Get the bytes back
    char *buf_c = java_byte_array_to_char_array(env, buf_java);

	// Call the original function and store the result
	return_value = recv(socket, buf_c, size, flags);

	// Release the memory for the copy of the string data
    free(buf_c);

	// Return the result
	return return_value;
}

/**
 * This overrides the original recv function
 */
ssize_t SJMMIE_recv(int socket, void *buffer, size_t size, int flags) {
	if(java_recv_method != NULL) {
		JNIEnv *env = get_env();

        print_c_array("C buffer before:", buffer, size);

		// NOTE: Since this is recv we technically don't need to copy the data from C.  But to make sure that we reproduce normal
		//         behavior and bugs as well we will do it.  Otherwise we could mask issues where the caller was reading past the
		//         end of their original array into data that was put there by C.
        jbyteArray buf_java = char_array_to_java_byte_array(env, buffer, size);

        print_java_array(env, "Java buffer before:", buf_java);

		jint return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_recv_method, socket, buf_java, size, flags);

        print_java_array(env, "Java buffer after:", buf_java);

		// Copy the data back from Java to C and release the Java copy immediately
        java_byte_array_to_existing_char_array(env, buf_java, &buffer, size);

        print_c_array("C buffer after:", buffer, size);

		// Release the copy of the original C data
        printf("3\n");
        safe_delete_local_ref(env, buf_java);

        printf("4\n");
		return return_value;
	}
	else {
		return recv(socket, buffer, size, flags);
	}
}
