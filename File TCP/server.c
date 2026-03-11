  int sock_desc,client_desc;
  struct sockaddr_in server_addr,client_addr;
  socklen_t client_size;
  char file[100],out[100];
  //memset(file,'\0',sizeof(file));
  //memset(out,'\0',sizeof(out));
  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(4214);
  server_addr.sin_addr.s_addr=INADDR_ANY;

  bind(sock_desc,(struct sockaddr *)&server_addr,sizeof(server_addr));
  listen(sock_desc,4);

  printf("Server Waiting for connecting \n");
  client_size=sizeof(client_addr);
  //client_desc=accept(sock_desc,(struct sockaddr *)&client_addr,&client_size);


  while(1)
  {
      client_desc=accept(sock_desc,(struct sockaddr *)&client_addr,&client_size);
      printf("Client Connected\n");
      pid_t pid =fork();
      int a;
      a=getpid();
      if(pid==0)
      {

          //client_desc=accept(sock_desc,(struct sockaddr *)&client_addr,&client_size);
          memset(file,'\0',sizeof(file));
          memset(out,'\0',sizeof(out));
          read(client_desc,file,sizeof(file));
          f1=fopen(file,"r");
          fgets(out,sizeof(out),f1);
          write(client_desc,out,sizeof(out));
          write(client_desc,&a,sizeof(int));
      }
      else
      {
         close(sock_desc);
         close(client_desc);
      }
  }


}
