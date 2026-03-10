#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>


int isPrime(int n)
{
  if(n<=1) return 0;

  for(int i=2;i*i<=n;i++)
  {
    if(n%i==0)
    {
      return 0;
    }
  }
  return 1;
}
int main()
{
  int sock_desc,client_desc;
  struct sockaddr_in server_addr,client_addr;
  socklen_t client_size;

  int n,a;

  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(1247);
  server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

  bind(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));
  listen(sock_desc,4);
  printf("Server waiting .....\n");

  client_size=sizeof(client_addr);
  client_desc=accept(sock_desc,(struct sockaddr *)&client_addr,&client_size);

  printf("Client Connected\n");

  read(client_desc,&n,sizeof(int));

  a=isPrime(n);

  write(client_desc,&a,sizeof(int));
  close(sock_desc);
  close(client_desc);

}