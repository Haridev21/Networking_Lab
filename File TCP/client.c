#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main()
{

  int sock_desc;
  struct sockaddr_in server_addr;
  char file[100],out[100];
  memset(file,'\0',sizeof(file));
  memset(out,'\0',sizeof(out));
  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(4214);
  server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

  connect(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));
  printf("Connected to server..\n");

  printf("Enter the file name:\n");
  scanf("%s",file);

  write(sock_desc,file,sizeof(file));
  read(sock_desc,out,sizeof(out));
  int a;
  read(sock_desc,&a,sizeof(int));
  printf("Content of File:%s and PID=%d\n",out,a);

  close(sock_desc);

}
