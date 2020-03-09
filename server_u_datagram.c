#include "includes.h"
#include "ret_check.h"
#include <sys/un.h>
#define SV_SOCK_PATH "/tmp/unix_dgram.sock"
#define BACKLOG 10
extern int errno;
#define BUFLEN 512

void clear_socket_file()
{
    if (remove(SV_SOCK_PATH) == -1){
     if (errno == ENOENT)
      puts("Socket file does not exist, continuing...");
     else
     {
     fprintf(stderr, "Failed to remove socket file! %s", strerror(errno));
     exit(EXIT_FAILURE);
     }
    }
}

int setup_socket()
{
  int listen = socket(AF_UNIX, SOCK_DGRAM, 0);
  check_return_code(listen);
  return listen;
}

void bind_socket(int sockfd, struct sockaddr_un addr)
{
  check_return_code(bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)));
}

int main(int argc, char *argv[])
{
  struct sockaddr_un addr, clientaddr;
  int len;
  unsigned char buffer[BUFLEN];
  int sockfd;
  clear_socket_file();
  sockfd = setup_socket();
  memset(&addr, 0, sizeof(addr));
  memset(&clientaddr, 0, sizeof(clientaddr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);
  bind_socket(sockfd, addr);
  len = sizeof(struct sockaddr_un);
  int n, total;
  for (; ;){
    fflush(stdout);
    n = recvfrom(sockfd, buffer, BUFLEN,0, (struct sockaddr *)&clientaddr, &len);
    total = total + n;
    printf("%s\n", buffer);
    sleep(3);
    printf("Total bytes received: %i\n", total);
  }
  //recv_data()
}
