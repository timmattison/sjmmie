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
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalSendTo(JNIEnv *env, jobject obj, jint sockfd, jbyteArray buf_java, jint len, jint flags, jchar sa_family, jbyteArray sa_data_java, jint addrlen) {
	int return_value;

	// Get the bytes back
    JAVA_C_CHAR_ARRAY(buf_java);

	// Rebuild the sockaddr structure
    JAVA_C_SOCKADDR(sa_data_java, sa_family);

	// Call the original function and store the result
	return_value = sendto(sockfd, CHAR_ARRAY_UNROLL(buf_java), len, flags, C_SOCKADDR_UNROLL(sa_data_java), addrlen);

	// Release the memory for the copy of the string data
    RELEASE_C_CHAR_ARRAY(buf_java);
    RELEASE_C_SOCKADDR(sa_data_java);

	// Return the result
	return return_value;
}

/**
 * This overrides the original sendto function
 */
ssize_t SJMMIE_sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen) {
	if(java_sendto_method != NULL) {
		JNIEnv *env = get_env();

        C_JAVA_CHAR_ARRAY(buf, len);

		jint return_value;

		if(dest_addr != NULL) {
            C_JAVA_SOCKADDR(dest_addr);
            return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_sendto_method, sockfd, CHAR_ARRAY_UNROLL(buf), len, flags, JAVA_SOCKADDR_UNROLL(dest_addr), addrlen);
            RELEASE_JAVA_SOCKADDR(dest_addr);
		}
		else {
			return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_sendto_method, sockfd, CHAR_ARRAY_UNROLL(buf), len, flags, 0, NULL, addrlen);
		}

        RELEASE_JAVA_CHAR_ARRAY(buf);

		return return_value;
	}
	else {
		return sendto(sockfd, buf, len, flags, dest_addr, addrlen);
	}
}
