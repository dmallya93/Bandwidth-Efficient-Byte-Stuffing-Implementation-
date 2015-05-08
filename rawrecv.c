/*** IPPROTO_RAW receiver ***/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "strmanip.c"
char scrap[20];

int main(void)
{
	int s;
	struct sockaddr_in saddr;
        char packet[500];

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

        
	memset(packet, 0, sizeof(packet));
	socklen_t *len = (socklen_t *)sizeof(saddr);
	int fromlen = sizeof(saddr);

	while(1) {
                bzero(scrap,20);
		if (recvfrom(s, (char *)&packet, sizeof(packet), 0,
			(struct sockaddr *)&saddr, &fromlen) < 0)
			perror("packet receive error:");
                
		int i = sizeof(struct iphdr);	
		extract(packet,i,sizeof(packet)-1);
                strcpy(scrap,store);
                separate(scrap);
		printf("\n");
	}
	exit(EXIT_SUCCESS);
}
