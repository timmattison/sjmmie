#include "../sjmmie.h"

#include <netinet/in.h>
#include <string.h>

/**
 * This overrides the original sendmsg function
 */
ssize_t SJMMIE_recvmsg(int socket, struct msghdr *message, int flags) {
    if (java_recvfrom_method != NULL) {
        JNIEnv *env = get_env();

        C_JAVA_MSGHDR(message);

        jint return_value;

        return_value = (*env)->CallIntMethod(env, sjmmie_instance, java_recvmsg_method, socket, JAVA_MSGHDR_UNROLL(message), flags);

        //JAVA_C_INT_ARRAY_COPY_BACK(addrlen, 1);
        //JAVA_C_CHAR_ARRAY_COPY_BACK(buf, len);

        //RELEASE_JAVA_CHAR_ARRAY(buf);
        //RELEASE_JAVA_INT_ARRAY(addrlen);

        return return_value;
    }
    else {
        return recvmsg(socket, message, flags);
    }
}
