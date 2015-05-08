#include "headers.c"
int main(void)
{
	int s;
	struct sockaddr_in saddr;
	char packet[1500];

	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
		perror("error:");
		exit(EXIT_FAILURE);
	}

	memset(packet, 0, sizeof(packet));
	//socklen_t *len = (socklen_t *)sizeof(saddr);
        int fromlen = sizeof(saddr);

	while(1) {
		if (recvfrom(s, (char *)&packet, sizeof(packet), 0,
			(struct sockaddr *)&saddr, &fromlen) < 0)
			perror("packet receive error:");
			
		printf("Received");
		int i = sizeof(struct ip);	
                printf("\nVALUE of i is %d\n",i);
		while (i < sizeof(packet)) {
			printf("%c", packet[i]);
			i++;
		}
		printf("\n");
	}
	exit(EXIT_SUCCESS);
}
