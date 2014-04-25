#include "../sjmmie.h"

jmethodID java_open_method;
jmethodID open_interceptor;

const char *open_interceptor_name = "openInterceptor";
const char *open_interceptor_arguments = "(Ljava/lang/String;I)I";

/**
 * Java calls back into this function when it wants to call back to the original open function
 */
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalOpen(JNIEnv *env, jobject obj, jbyteArray filename, jint flags) {
	int return_value;

    // Convert the string to a const char *
    char *filename_c = java_byte_array_to_char_array(env, filename);

	// Call the original function and store the result
	return_value = open(filename_c, flags);

	// Release the resources for the converted string
    free(filename_c);

	// Return the result
	return return_value;
}

/**
 * This overrides the original open function
 */
int SJMMIE_open(const char *filename, int flags, ...) {
	if(java_open_method != NULL) {
		JNIEnv *env = get_env();

        jbyteArray filename_java = char_array_to_java_byte_array(env, filename, strlen(filename));

		jint return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_open_method, filename_java, flags);

        // Copy the data back from Java to C and release the Java copy immediately
        java_byte_array_to_existing_char_array(env, filename_java, &filename);

        // Release the copy of the original C data
        safe_delete_local_ref(env, filename_java);

		return return_value;
	}
	else {
		return open(filename, flags);
	}
}
