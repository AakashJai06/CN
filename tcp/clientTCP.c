#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
  int sockfd,newsock;
  struct sockaddr_in server;
  socklen_t len = sizeof(server);
  char buffer[BUFFER_SIZE];

  sockfd = socket(AF_INET,SOCK_STREAM,0);

  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;

  connect(sockfd,(struct sockaddr *) &server,sizeof(server));

  printf("Enter Message to send : ");
  fgets(buffer,100,stdin);
  send(sockfd,buffer,strlen(buffer),0);

    close(sockfd);
  return 0;
}
