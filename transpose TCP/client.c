#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#define MAX 10

int main()
{

  int A[MAX][MAX],B[MAX][MAX];
  int r,c;

  int sock_desc;
  struct sockaddr_in server_addr;

  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(7002);
  server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

  connect(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));

  printf("Connected to server\n");

  printf("Enter row and col :\n");
  scanf("%d%d",&r,&c);
  printf("Enter the matrix\n");
  for(int i=0;i<r;i++)
  {
     for(int j=0;j<c;j++)
     {
       scanf("%d",&A[i][j]);
     }
  }

  write(sock_desc,&r,sizeof(int));
  write(sock_desc,&c,sizeof(int));

  write(sock_desc,A,sizeof(A));

  read(sock_desc,B,sizeof(B));

  printf("Transpose matrix:\n");

  for(int i=0;i<c;i++)
  {
    for(int j=0;j<r;j++)
    {
       printf("%d ", B[i][j]);
    }
    printf("\n");
  }

  close(sock_desc);
}