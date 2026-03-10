#include<stdio.h>
#include<ctype.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
   char str[100],buffer[100];
   struct sockaddr_in server_addr,client_addr;
   int sock_desc,client_desc;
   socklen_t client_size;
   memset(str,'\0',sizeof(str));
   memset(buffer,'\0',sizeof(buffer));

   sock_desc=socket(AF_INET,SOCK_STREAM,0);
   server_addr.sin_family=AF_INET;
   server_addr.sin_port=htons(1278);
   server_addr.sin_addr.s_addr=INADDR_ANY;

   bind(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));
   listen(sock_desc,4);
   printf("Server waiting ....\n");

   client_size=sizeof(client_addr);
   client_desc=accept(sock_desc,(struct sockaddr *)&client_addr,&client_size);
   printf("Connected to Client\n");
   int v=0;
   int c=0;
   read(client_desc,str,sizeof(str));
   char store[100];
   memset(store,'\0',sizeof(store));
   int j=0;
   char ch;
   for(int i=0;str[i]!='\0';i++)
   {
      ch=str[i];
      if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'||
         str[i]=='A'||str[i]=='E'||str[i]=='I'||str[i]=='O'||str[i]=='U')
      {
          v++;
          store[j++]=ch;
      }
      else if((str[i]>='a' && str[i]<='z')||(str[i]>='A' && str[i]<='Z'))
      {
         c++;
      }
   }
   store[j]='\0';
   write(client_desc,&v,sizeof(int));
   write(client_desc,&c,sizeof(int));
   for(int i=0;str[i]!='\0';i++)
   {
      buffer[i]=toupper(str[i]);
   }
   write(client_desc,buffer,sizeof(buffer));
   write(client_desc,store,sizeof(store));