#include "../sjmmie.h"

#include <netinet/in.h>
#include <string.h>

/**
 * This overrides the original sendmsg function
 */
ssize_t SJMMIE_sendmsg(int socket, const struct msghdr *message, int flags) {
    printf("sendmsg called\n");
    return sendmsg(socket, message, flags);
}
