#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){

  char buffer[100];
  int k;
  socklen_t len;
  struct sockaddr_in server,client;
  int sock_desc,temp_sock_desc;

  sock_desc = socket(AF_INET,SOCK_STREAM,0);
  if(sock_desc == -1){
    printf("Error in socket creation!!\n");
    return 1;
  }
  printf("Socket created sucessfully!!!\n");

  server.sin_family = AF_INET;
  server.sin_port = htons(3003);
  server.sin_addr.s_addr = INADDR_ANY;

  k = bind(sock_desc,(struct sockaddr *)&server,sizeof(server));
  if(k == -1){
    printf("Binding Error!!!\n");
    return 1;
  }
  printf("Socket Binded Successfully!!\n");

  k = listen(sock_desc,5);
  if (k == -1) {
    printf("Error In Listening!\n");
    return 1;
}
  printf("Waiting for connections...\n"); 

  len = sizeof(client);

  temp_sock_desc = accept(sock_desc,(struct sockaddr *)&client,&len);
  if (temp_sock_desc == -1) {
    printf("Error In Temporary Socket Creation!\n");
    return 1;
}
  printf("Client Connected Successfully!\n");

  k = recv(temp_sock_desc,buffer,sizeof(buffer)-1,0);
  if (k == -1) {
    printf("Error In Receiving Data!\n");
    return 1;
}
buffer[k] = '\0'; 
printf("Message From Client: %s\n", buffer);

close(temp_sock_desc);
    close(sock_desc);


  return 0;
}
