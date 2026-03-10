#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int sock;
    struct sockaddr_in server_addr;

    char infix[100], postfix[100];

    sock = socket(AF_INET,SOCK_STREAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));

    printf("Enter Infix Expression: ");
    scanf("%s",infix);

    write(sock,infix,sizeof(infix));

    read(sock,postfix,sizeof(postfix));

    printf("Postfix Expression: %s\n",postfix);

    close(sock);
}