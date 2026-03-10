#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
  int sock_desc;
  struct sockaddr_in server_addr;

  int n,a;

  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(1247);
  server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

  connect(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));
  printf("Connected to server\n");

  printf("Enter an integer to check prime or not:\n");
  scanf("%d",&n);

  write(sock_desc,&n,sizeof(int));

  read(sock_desc,&a,sizeof(int));

  if(a==1)
  {
     printf("Prime Number \n");
  }
  else
  {
     printf("Not Prime Number \n");
  }

  close(sock_desc);
}