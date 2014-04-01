#include "../sjmmie.h"

#include <netinet/in.h>
#include <string.h>

jmethodID java_sendto_method;

const char *sendto_interceptor_name = "sendtoInterceptor";
const char *sendto_interceptor_arguments = "(I[BIIC[BI)I";

jmethodID sendto_interceptor;

/**
 * Java calls back into this function when it wants to call back to the original sendto function
 */
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalSendTo(JNIEnv *env, jobject obj, jint sockfd, jbyteArray buf_java, jint len, jint flags, jchar sa_family, jbyteArray dest_addr_sa_data_java, jint addrlen) {
	int return_value;

	// Get the bytes back
	char* buf_c = java_byte_array_to_char_array(env, buf_java);

	// Rebuild the sockaddr structure
	struct sockaddr dest_addr;
	dest_addr.sa_family = sa_family;

	// Get the string data and copy it to the sockaddr structure
	char* dest_addr_sa_data_c = java_byte_array_to_char_array(env, dest_addr_sa_data_java);
	if(dest_addr_sa_data_c != NULL) {
		memcpy(&dest_addr.sa_data[0], dest_addr_sa_data_c, sizeof(dest_addr.sa_data));
	}

	// Call the original function and store the result
	return_value = sendto(sockfd, buf_c, len, flags, (dest_addr_sa_data_c == NULL) ? NULL : &dest_addr, addrlen);

	// Release the memory for the copy of the string data
	safe_release_byte_array_elements(env, buf_java, (signed char *) buf_c);
	safe_release_byte_array_elements(env, dest_addr_sa_data_java, (signed char *) dest_addr_sa_data_c);

	// Return the result
	return return_value;
}

/**
 * This overrides the original sendto function
 */
ssize_t SJMMIE_sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) {
	if(java_sendto_method != NULL) {
		JNIEnv *env = get_env();

		jbyteArray data_to_send_java = char_array_to_java_byte_array(env, (char *) buf, len);

		jint return_value;

		if(dest_addr != NULL) {
            C_JAVA_SOCKADDR(dest_addr);
			return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_sendto_method, sockfd, data_to_send_java, len, flags, SOCKADDR_UNROLL(dest_addr), addrlen);
            RELEASE_JAVA_SOCKADDR(dest_addr);
		}
		else {
            printf("9\n");
			return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_sendto_method, sockfd, data_to_send_java, len, flags, 0, NULL, addrlen);
		}

        printf("10\n");
		safe_delete_local_ref(env, data_to_send_java);
	
		return return_value;
	}
	else {
		return sendto(sockfd, buf, len, flags, dest_addr, addrlen);
	}
}
