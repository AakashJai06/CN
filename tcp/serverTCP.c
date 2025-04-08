#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
  int sockfd,newsock;
  struct sockaddr_in server,client;
  socklen_t len = sizeof(client);
  char buffer[BUFFER_SIZE];

  sockfd = socket(AF_INET,SOCK_STREAM,0);

  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;

  bind(sockfd,(struct sockaddr *) &server,sizeof(server));
  listen(sockfd,5);

  newsock = accept(sockfd,(struct sockaddr *) &client,&len);
  recv(newsock,buffer,BUFFER_SIZE,0);

  printf("Message From Client: %s\n", buffer);

    close(newsock);
    close(sockfd);
  return 0;
}
