#include<stdio.h>
#include<ctype.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
   char str[100];
   struct sockaddr_in server_addr;
   int sock_desc;


   sock_desc=socket(AF_INET,SOCK_STREAM,0);
   server_addr.sin_family=AF_INET;
   server_addr.sin_port=htons(1278);
   server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");


   connect(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));
   printf("Connected to Server\n");
   memset(str,'\0',sizeof(str));
   printf("Enter the String:\n");
//   scanf("%s",str);
   fgets(str,sizeof(str),stdin);

   write(sock_desc,str,sizeof(str));
   int v,d;
   read(sock_desc,&v,sizeof(int));
   read(sock_desc,&d,sizeof(int));
   printf("Vowels:%d\n Consonants:%d\n",v,d);
   char buffer[100];
   memset(buffer,'\0',sizeof(buffer));
   read(sock_desc,buffer,sizeof(buffer));
   printf("In Upper Case of String:%s\n",buffer);
   char store[100];
   memset(store,'\0',sizeof(store));
   read(sock_desc,store,sizeof(store));
   printf("Vowels from the string:%s\n",store);
   close(sock_desc);
}
