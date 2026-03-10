#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{

  int sock_desc,n;
  struct sockaddr_in server_addr;
  char d[100];
  memset(d,'\0',sizeof(d));
  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(1213);
  server_addr.sin_addr.s_addr=INADDR_ANY;

  connect(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));
  printf("Connected to server\n");

  printf("Enter the number to reversed:\n");
  scanf("%d",&n);
  write(sock_desc,&n,sizeof(int));
  int r;
  read(sock_desc,&r,sizeof(int));


  read(sock_desc,d,sizeof(d));


  printf("Reversed String: %d\n",r);
  printf("%s\n ", d);

  close(sock_desc);
}

