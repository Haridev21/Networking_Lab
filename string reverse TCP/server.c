#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#define MAX 10



void reverse(char str[])
{
  int i,len;
  char temp;
  len=strlen(str);
  for(i=0;i<len/2;i++)
  {
     temp=str[i];
     str[i]=str[len-i-1];
     str[len-i-1]=temp;
  }
}


int main()
{

  int sock_desc,client_desc;
  struct sockaddr_in server_addr,client_addr;
  socklen_t client_size;
  char buffer[MAX];

  memset(buffer,'\0',sizeof(buffer));
//  memset(result,'\0',sizeof(result));

  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(9232);
  server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

  bind(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));
  listen(sock_desc,4);
  printf("Server waiting\n");

  client_size=sizeof(client_addr);
  client_desc=accept(sock_desc,(struct sockaddr *)&client_addr,&client_size);
  printf("Client Connected\n");

  read(client_desc,buffer,sizeof(buffer));

  reverse(buffer);
  printf("Output from server: %s",buffer);
  write(client_desc,buffer,sizeof(buffer));
  close(sock_desc);
  close(client_desc);



}