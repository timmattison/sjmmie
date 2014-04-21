#include "../sjmmie.h"

#include <netinet/in.h>
#include <string.h>

jmethodID java_recvfrom_method;

const char *recvfrom_interceptor_name = "recvfromInterceptor";
const char *recvfrom_interceptor_arguments = "(I[BIIC[BI)I";

jmethodID recvfrom_interceptor;

/**
 * Java calls back into this function when it wants to call back to the original recvfrom function
 */
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalRecvFrom(JNIEnv *env, jobject obj, jint sockfd, jbyteArray buf_java, jint len, jint flags, jchar sa_family, jbyteArray sa_data_java, jintArray addrlen) {
	int return_value;

	// Get the bytes back
    JAVA_C_CHAR_ARRAY(buf_java);

    // Get the size back
    JAVA_C_INT_ARRAY(addrlen);

    // Rebuild the sockaddr structure
    JAVA_C_SOCKADDR(sa_data_java, INT_ARRAY_UNROLL(addrlen)[0])

	// Call the original function and store the result
	return_value = recvfrom(sockfd, CHAR_ARRAY_UNROLL(buf_java), len, flags, C_SOCKADDR_UNROLL(sa_data_java), (socklen_t *) INT_ARRAY_UNROLL(addrlen));

	// Release the memory for the copy of the string data
    RELEASE_C_CHAR_ARRAY(buf_java);
    RELEASE_C_INT_ARRAY(addrlen);
    RELEASE_C_SOCKADDR(sa_data_java);

	// Return the result
	return return_value;
}

/**
 * This overrides the original recvfrom function
 */
ssize_t SJMMIE_recvfrom(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t *addrlen) {
	if(java_recvfrom_method != NULL) {
		JNIEnv *env = get_env();

        C_JAVA_CHAR_ARRAY(buf, len);
        C_JAVA_INT_ARRAY(addrlen, 1);

		jint return_value;

		if(dest_addr != NULL) {
            C_JAVA_SOCKADDR(dest_addr, addrlen);
            return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_recvfrom_method, sockfd, CHAR_ARRAY_UNROLL(buf), len, flags, JAVA_SOCKADDR_UNROLL(dest_addr), INT_ARRAY_UNROLL(addrlen));
            RELEASE_JAVA_SOCKADDR(dest_addr);
		}
		else {
			return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_recvfrom_method, sockfd, CHAR_ARRAY_UNROLL(buf), len, flags, 0, NULL, addrlen);
		}

        JAVA_C_INT_ARRAY_COPY_BACK(addrlen, 1);
        JAVA_C_CHAR_ARRAY_COPY_BACK(buf, len);

        RELEASE_JAVA_CHAR_ARRAY(buf);
        RELEASE_JAVA_INT_ARRAY(addrlen);

		return return_value;
	}
	else {
		return recvfrom(sockfd, buf, len, flags, dest_addr, addrlen);
	}
}
