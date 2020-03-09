#include "includes.h"
#include "ret_check.h"
#include <sys/un.h>
#define SV_SOCK_PATH "/tmp/unix_dgram.sock"
#define BACKLOG 10
extern int errno;
#define BUFLEN 512


int main(int argc, char *argv[])
{
 struct sockaddr_un srv, cli;
 int sockfd;
 unsigned char buffer[BUFLEN];
 char *hello = "Hello from client!!";
 sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
 check_return_code(sockfd);
 memset(&cli, 0, sizeof(cli));
 memset(&srv,0,sizeof(srv));
 cli.sun_family = AF_UNIX;
 srv.sun_family = AF_UNIX;
 strncpy(cli.sun_path, SV_SOCK_PATH, sizeof(cli.sun_path) -1);
 strncpy(srv.sun_path, SV_SOCK_PATH, sizeof(srv.sun_path) -1);
 printf("%s\n", cli.sun_path);
 printf("%i\n", strlen(hello));
 int count=1;
 for ( ; ; ){
 sendto(sockfd, hello, strlen(hello)+1,0, (struct sockaddr *)&srv, sizeof(struct sockaddr_un));
 printf("Sent\n");
 count++;
 printf("%i\n", count);
 if (count >= 200){
   close(sockfd);
   break;
  }
 }
 puts("Finished sending UDP datagrams...");
 return 0;

}
