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
	char* sa_data_c = (char *) (*env)->GetByteArrayElements(env, sa_data_java, 0);
	memcpy(&temp.sa_data[0], sa_data_c, sizeof(temp.sa_data));

	// Call the original function and store the result
	return_value = connect(s, &temp, namelen);

	// Release the memory for the copy of the string data
	(*env)->ReleaseByteArrayElements(env, sa_data_java, (signed char *) sa_data_c, JNI_ABORT);

	// Return the result
	return return_value;
}

/**
 * This overrides the original connect function
 */
int SJMMIE_connect(int s, const struct sockaddr *name, socklen_t namelen) {
	if(java_connect_method != NULL) {
		get_env();

		int size_of_sa_data = sizeof(name->sa_data);
		jbyteArray sa_data_java = (*env)->NewByteArray(env, size_of_sa_data);
		(*env)->SetByteArrayRegion(env, sa_data_java, 0, size_of_sa_data, (jbyte*) name->sa_data);
		jint return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_connect_method, s, name->sa_family, sa_data_java, namelen);

		// XXX - Is this correct?  http://stackoverflow.com/questions/8574241/jni-newbytearray-memory-leak
		(*env)->DeleteLocalRef(env, sa_data_java);
	
		return return_value;
	}
	else {
		return connect(s, name, namelen);
	}
}
