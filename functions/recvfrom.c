#include "../sjmmie.h"

#include <netinet/in.h>
#include <string.h>

jmethodID java_recvfrom_method;

const char *recvfrom_interceptor_name = "recvfromInterceptor";
const char *recvfrom_interceptor_arguments = "(I[BIIC[B[I)I";

jmethodID recvfrom_interceptor;

/**
 * Java calls back into this function when it wants to call back to the original recvfrom function
 */
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalRecvFrom(JNIEnv *env, jobject obj, jint sockfd, jbyteArray buf_java, jint len, jint flags, jchar sa_family, jbyteArray sa_data_java, jintArray addrlen) {
	int return_value;

	// Rebuild the sockaddr structure
	struct sockaddr temp;
	temp.sa_family = sa_family;

	// Get the int data and copy it to the addrlen structure
	unsigned int* addrlen_c = (unsigned int *) (*env)->GetIntArrayElements(env, addrlen, 0);

	// Get the string data and copy it to the sockaddr structure
	char* sa_data_c = (char *) (*env)->GetByteArrayElements(env, sa_data_java, 0);
	memcpy(&temp.sa_data[0], sa_data_c, addrlen_c[0]);

	// Get the bytes back
	char* buf_c = java_byte_array_to_char_array(env, buf_java);

	// Call the original function and store the result
	return_value = recvfrom(sockfd, buf_c, len, flags, &temp, addrlen_c);

	// Release the memory for the copy of the string data and copy it back
	safe_release_byte_array_elements_copy_back(env, buf_java, (signed char *) buf_c);

	// Release the memory for the copy of the string data and copy it back
	safe_release_byte_array_elements_copy_back(env, sa_data_java, (signed char *) sa_data_c);

	// Release the memory for the copy of the int data
	safe_release_byte_array_elements_copy_back(env, addrlen, (int *) addrlen_c);

	// Return the result
	return return_value;
}

/**
 * This overrides the original recvfrom function
 */
ssize_t SJMMIE_recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {
	printf("IN SJMMIE_recvfrom 1\n");
	if(java_recvfrom_method != NULL) {
		JNIEnv *env = get_env();

		int size_of_sa_data = sizeof(src_addr->sa_data);
		jbyteArray sa_data_java = (*env)->NewByteArray(env, size_of_sa_data);
		(*env)->SetByteArrayRegion(env, sa_data_java, 0, size_of_sa_data, (jbyte*) src_addr->sa_data);

		// NOTE: Since this is recvfrom we technically don't need to copy the data from C.  But to make sure that we reproduce normal
		//         behavior and bugs as well we will do it.  Otherwise we could mask issues where the caller was reading past the
		//         end of their original array into data that was put there by C.
		jbyteArray data_to_recv_java = char_array_to_java_byte_array(env, (char *) buf, len);

		jbyteArray addrlen_java = int_array_to_java_int_array(env, (int *) addrlen, 1);

		jint return_value;

		return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_recvfrom_method, sockfd, data_to_recv_java, len, flags, src_addr->sa_family, sa_data_java, addrlen_java);

		// Copy the data back from Java to C and release the Java copy immediately
		char* temp_buf = java_byte_array_to_char_array(env, data_to_recv_java);
		memcpy(buf, temp_buf, len);
		safe_release_byte_array_elements(env, data_to_recv_java, (signed char *) temp_buf);

		int* temp_addrlen = java_int_array_to_int_array(env, addrlen_java);

		char* temp_src_addr_sa_data = java_byte_array_to_char_array(env, sa_data_java);
		memcpy(src_addr->sa_data, temp_src_addr_sa_data, addrlen[0]);
		safe_release_byte_array_elements(env, data_to_recv_java, (signed char *) temp_buf);
		safe_release_int_array_elements(env, addrlen_java, (signed char *) temp_addrlen);

		// Release the copy of the original C data
		safe_delete_local_ref(env, data_to_recv_java);
		safe_delete_local_ref(env, sa_data_java);
		safe_delete_local_ref(env, addrlen_java);
	
		return return_value;
	}
	else {
		return recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
	}
}
