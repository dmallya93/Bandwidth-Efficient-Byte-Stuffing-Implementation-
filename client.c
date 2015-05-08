#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<strings.h>
void display(int a[],int* p)
{
 printf("\nThe received array is : \n");
 int q=*p,i;
 for(i=0;i<q;i++)
  printf("%d\t",a[i]);
}
int main(int argc,char** argv)
{
 int sockfd,n,portno;
 struct sockaddr_in serv_addr;
 struct hostent* server;
 char buffer[256],msg[300];

 server=gethostbyname(argv[1]);
 portno=atoi(argv[2]);

 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd<0)
  perror("\nError in creation of socket");
 
 bzero((char*)&serv_addr,sizeof(serv_addr));
 serv_addr.sin_family=AF_INET;
 bcopy(server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
 serv_addr.sin_port=htons(portno); 

 if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
  perror("\nError in connecting to server");
 
 int* t;
 int x[3];
  while(1)
  {  
   bzero(buffer,256);  
   printf("\nEnter the message for the server\n");
   gets(msg);
   strcat(msg,"\0");
   n=write(sockfd,msg,strlen(msg));
   if(n<0)
    perror("\nError in wrinting to server");
   n=read(sockfd,t,sizeof(t));
   if(n<0)
   perror("\nError in reading from the server\n");
   n=read(sockfd,x,sizeof(x));
   if(n<0)
    perror("\nError in reading from the server\n");
   display(x,t);
   //printf("\nMessage from the server is : %s \n",buffer);

   }
  return 0;

}
