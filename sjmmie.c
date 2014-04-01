#include "sjmmie.h"

const char *SJMMIE_JVM_OPTS_VARIABLE = "SJMMIE_JVM_OPTS";
const char *SJMMIE_CLASS_VARIABLE    = "SJMMIE_CLASS";

const int NOT_INITIALIZED = 0;
const int INITIALIZED = 1;
const int INITIALIZING = 2;

int initialized = NOT_INITIALIZED;

int SJMMIE_open(const char *filename, int flags, ...);
int SJMMIE_connect (int sd, const struct sockaddr* addr, socklen_t alen);
int SJMMIE_close(int fildes);
ssize_t SJMMIE_sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
int SJMMIE_socket(int domain, int type, int protocol);
ssize_t SJMMIE_send(int socket, const void *buffer, size_t length, int flags);
ssize_t SJMMIE_recv (int socket, void *buffer, size_t size, int flags);

/* The names of everything except the section are arbitrary */
typedef	struct	interposer {
	void*	replacement;
	void*	original;
} interpose_t;

static const interpose_t interposers[] \
	 __attribute__ ((section("__DATA, __interpose"))) = {
		{ .replacement = SJMMIE_open, .original = open },
		{ .replacement = SJMMIE_close, .original = close },
		{ .replacement = SJMMIE_connect, .original = connect },
		{ .replacement = SJMMIE_sendto, .original = sendto },
		{ .replacement = SJMMIE_socket, .original = socket },
		{ .replacement = SJMMIE_send, .original = send },
		{ .replacement = SJMMIE_recv, .original = recv },
};

static void con() __attribute__((constructor));

// This gets called when the library is loaded
// http://stackoverflow.com/questions/9759880/automatically-executed-functions-when-loading-shared-libraries
void con() {
	// Force the interpose struct to be referenced so the compiler doesn't optimize it out
	interposers[0];

	// Make sure the environment is loaded
	get_env();
}
