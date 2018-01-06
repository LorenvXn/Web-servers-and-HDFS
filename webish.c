#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<netinet/in.h>

/*
*Had to change the pic; old link won't work
*/

char webish[]=
"<!DOCTYPEhtml>\r\n"
"<html><head><title>Rul3rOvWorldZ</title>\r\n"
"<style>body{background-color:#F433FF}</style></head>\r\n"
"<body><center><h1>IRULEDAHUNIVERSE!!1!</h1><br>\r\n"
"<img src=\"https://i.pinimg.com/736x/2f/9d/69/2f9d69a9135e098235cc382a623d94d6--star-wars-games-star-wars-art.jpg\" style=\"width:24
0px;height:328px\"></center></body></html>\r\n"; 

int main(int  argc, char **argv)
{
  struct sockaddr_in server_addr,client_addr;
  socklen_t sin_len=sizeof(client_addr);
  int server,client;
  char buf[70000];
  int lilkylo;
  int on=1;
  server=socket(AF_INET,SOCK_STREAM,0);
  
  if(server<0)
  {
    perror("socket");
    exit(1);
  }
  setsockopt(server,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(int));
  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr=INADDR_ANY;
  server_addr.sin_port=htons(8666);
  
  if(bind(server,(struct sockaddr*)&server_addr,sizeof(server_addr))==1)
  {
    perror("bind");
    close(server);
    exit(1);
  }
  
  if(listen(server,10)==1)
  {
    perror("listen");
    close(server);
    exit(1);
  }

  while(1)
  {
  client=accept(server,(struct sockaddr*)&client_addr,&sin_len);
    if(client==1)
    {
    perror("can'tconnect\n");
    continue;
    }
    printf("got client connection\n");
      if(!fork())
        {
          close(server);
          memset(buf,0,sizeof(buf));
          read(client,buf,sizeof(buf)-1);
          printf("%s\n",buf);

/*
* YOLO, no time for different ways!!
* if(!strncmp(buf,"GET/doctest.jpg",16))
*{
*lilkylo=open("doctest.jpg",O_RDONLY);
*sendfile(client,lilkylo,NULL,68000);
*close(lilkylo);
*}
*else
*/

          write(client,webish,sizeof(webish)-1);
         }
      close(client);
      printf("closing....");
      exit(0);
      }
return 0;
}

  
  
