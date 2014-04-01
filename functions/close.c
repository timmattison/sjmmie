#include "../sjmmie.h"

jmethodID java_close_method;

const char *close_interceptor_name = "closeInterceptor";
const char *close_interceptor_arguments = "(I)I";

jmethodID close_interceptor;

/**
 * Java calls back into this function when it wants to call back to the original close function
 */
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalClose(JNIEnv *env, jobject obj, jint fildes) {
	int return_value;

	// Call the original function and store the result
	return_value = close(fildes);

	// Return the result
	return return_value;
}

/**
 * This overrides the original close function
 */
int SJMMIE_close(int fildes) {
	if(java_close_method != NULL) {
		JNIEnv *env = get_env();

		jint return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_close_method, fildes);
	
		return return_value;
	}
	else {
		return close(fildes);
	}
}
