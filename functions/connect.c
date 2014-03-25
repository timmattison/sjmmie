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
	struct sockaddr temp;
	temp.sa_family = sa_family;

	// Get the string data and copy it to the sockaddr structure
	char* sa_data_c = java_byte_array_to_char_array(env, sa_data_java);
	memcpy(&temp.sa_data[0], sa_data_c, sizeof(temp.sa_data));

	// Call the original function and store the result
	return_value = connect(s, &temp, namelen);

	// Release the memory for the copy of the string data
	safe_release_byte_array_elements(env, sa_data_java, (signed char *) sa_data_c);

	// Return the result
	return return_value;
}

/**
 * This overrides the original connect function
 */
int SJMMIE_connect(int s, const struct sockaddr *name, socklen_t namelen) {
	if(java_connect_method != NULL) {
		JNIEnv *env = get_env();

		int size_of_sa_data = sizeof(name->sa_data);
		jbyteArray sa_data_java = char_array_to_java_byte_array(env, (char *) name->sa_data, size_of_sa_data);

		jint return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_connect_method, s, name->sa_family, sa_data_java, namelen);

		// XXX - Is this correct?  http://stackoverflow.com/questions/8574241/jni-newbytearray-memory-leak
		safe_delete_local_ref(env, sa_data_java);
	
		return return_value;
	}
	else {
		return connect(s, name, namelen);
	}
}
