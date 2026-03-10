#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#define MAX 10

void Transpose(int A[MAX][MAX],int B[MAX][MAX],int r,int c)
{
  for(int i=0;i<r;i++)
  {
    for(int j=0;j<c;j++)
    {
       B[j][i]=A[i][j];
    }
  }
}
int main()
{

  int A[MAX][MAX],B[MAX][MAX];
  int r,c;

  int sock_desc,client_desc;
  socklen_t client_size;
  struct sockaddr_in server_addr,client_addr;

  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(7002);
  server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

  bind(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));
  listen(sock_desc,4);
  printf("Server waiting \n");
  client_size=sizeof(client_addr);
  client_desc=accept(sock_desc,(struct sockaddr *)&client_addr,&client_size);

  printf("Connected to client\n");


  read(client_desc,&r,sizeof(int));
  read(client_desc,&c,sizeof(int));

  read(client_desc,A,sizeof(A));

  Transpose(A,B,r,c);

  write(client_desc,B,sizeof(B));

  close(sock_desc);
  close(client_desc);



}