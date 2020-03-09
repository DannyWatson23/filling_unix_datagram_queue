#ifndef __includes_h
#define __includes_h
#endif
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#define PORT 8080
#define GETSOCKETERRNO() (errno)
#define ISVALIDSOCKET(s) ((s) >= 0)
#define ISSUCCESSFUL(s) ((s < 0) ? errno : puts("Successful"))
#define EXIT_FAILURE 1
#define SA struct sockaddr
