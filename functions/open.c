#include "../sjmmie.h"

jmethodID java_open_method;
jmethodID open_interceptor;

const char *open_interceptor_name = "openInterceptor";
const char *open_interceptor_arguments = "(Ljava/lang/String;I)I";

/**
 * Java calls back into this function when it wants to call back to the original open function
 */
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalOpen(JNIEnv *env, jobject obj, jstring filename, jint flags) {
	int return_value;

	// Convert the string to a const char *
	const char *c_filename = (*env)->GetStringUTFChars(env, filename, NULL);

	// Call the original function and store the result
	return_value = open(c_filename, flags);

	// Release the resources for the converted string
	(*env)->ReleaseStringUTFChars(env, filename, c_filename);

	// Return the result
	return return_value;
}

/**
 * This overrides the original open function
 */
int SJMMIE_open(const char *filename, int flags, ...) {
	if(java_open_method != NULL) {
		jclass open_callback_class;

		JNIEnv *env = get_env();

		jint return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_open_method, (*env)->NewStringUTF(env, filename), flags);
	
		return return_value;
	}
	else {
		//printf("OPEN no callback\n");
		return open(filename, flags);
	}
}
