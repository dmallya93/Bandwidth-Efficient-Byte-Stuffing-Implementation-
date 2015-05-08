#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define DEST "127.0.0.1"
#include "frame.c"
#include<math.h>


int main(int argc,char** argv)
{
         
        char c;
        int count=0;
        FILE* fp;
        int a[3];
        fp = fopen("message","r");
        int i;
	int s;
	struct sockaddr_in daddr;
	 
        
	struct iphdr *ip = (struct iphdr *)packet;  
    

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}
       	daddr.sin_family = AF_INET;
	daddr.sin_port = 0; /* not needed in SOCK_RAW */
	inet_pton(AF_INET, DEST, (struct in_addr *)&daddr.sin_addr.s_addr);
	memset(daddr.sin_zero, 0, sizeof(daddr.sin_zero));
       

           while(fscanf(fp,"%c",&c)!=EOF)
            {
              strcpy(packet,"                    ");
               count++;
               a[count-1]=(int)c;
               if(count%3==0)
                {
                  count=0;
                  convert(a,3);                
	          strcat(packet,"\0");
                  printf("\nPacket is %s\n",packet);
	          ip->ihl = 5;
	          ip->version = 4;
	          ip->tos = 0;
	          ip->tot_len = htons(40);	/* 16 byte value */
	          ip->frag_off = 0;		/* no fragment */
	          ip->ttl = 64;			/* default value */
	          ip->protocol = IPPROTO_RAW;	/* protocol at L4 */
	          ip->check = 0;			/* not needed in iphdr */
	          ip->saddr = daddr.sin_addr.s_addr;
	          ip->daddr = daddr.sin_addr.s_addr;

	          sleep(1);
		   if (sendto(s, (char *)packet, sizeof(packet), 0, 
			(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) < 0)
			perror("packet send error:");
                  bzero(packet,500);
               }
	}
	exit(EXIT_SUCCESS);
}
