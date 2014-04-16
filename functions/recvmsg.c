#include "../sjmmie.h"

#include <netinet/in.h>
#include <string.h>

/**
 * This overrides the original sendmsg function
 */
ssize_t SJMMIE_recvmsg(int socket, struct msghdr *message, int flags) {
    printf("recvmsg called\n");
    return recvmsg(socket, message, flags);
}
