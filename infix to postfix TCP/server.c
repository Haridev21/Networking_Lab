#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<ctype.h>

int priority(char x)
{
    if(x=='+' || x=='-') return 1;
    if(x=='*' || x=='/') return 2;
    return 0;
}

void infixToPostfix(char infix[], char postfix[])
{
    char stack[100];
    int top=-1,i=0,k=0;

    while(infix[i]!='\0')
    {
        if(isalnum(infix[i]))
        {
            postfix[k++]=infix[i];
        }
        else if(infix[i]=='(')
        {
            stack[++top]=infix[i];
        }
        else if(infix[i]==')')
        {
            while(stack[top]!='(')
            {
                postfix[k++]=stack[top--];
            }
            top--;
        }
        else
        {
            while(top!=-1 && priority(stack[top])>=priority(infix[i]))
            {
                postfix[k++]=stack[top--];
            }
            stack[++top]=infix[i];
        }
        i++;
    }

    while(top!=-1)
        postfix[k++]=stack[top--];

    postfix[k]='\0';
}

int main()
{
    int sock_desc, client_desc;
    struct sockaddr_in server_addr,client_addr;
    socklen_t client_size;

    char infix[100], postfix[100];

    sock_desc = socket(AF_INET,SOCK_STREAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr));

    listen(sock_desc,1);

    printf("Server Waiting...\n");

    client_size = sizeof(client_addr);
    client_desc = accept(sock_desc,(struct sockaddr*)&client_addr,&client_size);

    read(client_desc,infix,sizeof(infix));

    infixToPostfix(infix,postfix);

    write(client_desc,postfix,sizeof(postfix));

    close(client_desc);
    close(sock_desc);
}