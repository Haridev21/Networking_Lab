#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#define MAX 10

int main()
{

  int sock_desc;
  struct sockaddr_in server_addr;

  char buffer[MAX],result[MAX];

  memset(buffer,'\0',sizeof(buffer));
  memset(result,'\0',sizeof(result));

  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(9232);
  server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

  connect(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));

  printf("Connected to server\n");

  printf("Enter the string to be reversed\n");
  scanf("%s",buffer);

  write(sock_desc,buffer,sizeof(buffer));
  read(sock_desc,result,sizeof(result));

  printf("Reversed string :%s\n",result);
  close(sock_desc);

}


