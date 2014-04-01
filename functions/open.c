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
    JAVA_C_STRING(filename);

	// Call the original function and store the result
	return_value = open(STRING_UNROLL(filename), flags);

	// Release the resources for the converted string
    RELEASE_C_STRING(filename);

	// Return the result
	return return_value;
}

/**
 * This overrides the original open function
 */
int SJMMIE_open(const char *filename, int flags, ...) {
	if(java_open_method != NULL) {
		JNIEnv *env = get_env();

        C_JAVA_STRING(filename);
		jint return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_open_method, STRING_UNROLL(filename), flags);
        RELEASE_JAVA_STRING(filename);
	
		return return_value;
	}
	else {
		return open(filename, flags);
	}
}
