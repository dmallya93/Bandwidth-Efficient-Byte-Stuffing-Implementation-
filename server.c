#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<strings.h>
int main(int argc,char** argv)
{
 int sockfd,newsockfd,n,portno,cli_len;
 struct sockaddr_in serv_addr,cli_addr;
 char buffer[256];
 char msg[500];

 if(argc<2)
 perror("\nInsufficient number of arguments\n");

 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd<0)
  perror("\nError in socket creation");  

 bzero((char*)&serv_addr,sizeof(serv_addr));
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_addr.s_addr=INADDR_ANY;
 serv_addr.sin_port=htons(atoi(argv[1]));

 if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
  perror("\nError in binding");

 cli_len=sizeof(cli_addr);
 listen(sockfd,5);
 newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&cli_len);
 if(newsockfd<0)
  perror("\nError in accepting connection");
 int x[3]={1,2,3};
 int count=3;
 while(1)
 {   
 bzero(buffer,256); 
 n=read(newsockfd,buffer,255);
 if(n<0)
  perror("\nError in reading from the client");


 printf("\nMessage from client is %s \n",buffer);
 printf("\nEnter the message for the client\n");
 gets(msg);
 strcat(msg,"\0");
 n=write(newsockfd,&count,sizeof(int));  
 n=write(newsockfd,x,sizeof(x)); 
}
 
 return 0;
}
