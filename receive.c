  //Compile  gcc receive.c -o receive -lipq
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<linux/netfilter.h>
#include<lib/ipq.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/types.h>

#define BUFSIZE 4096

struct pseudo_tcphdr
{
    unsigned int ip_src;
    unsigned int ip_dst;
    unsigned char zero;
    unsigned char protocol;
    unsigned short tcp_len;
};                                                                                                                                          

static void die(struct ipq_handle h)
{
    ipq_perror(passer);
    ipq_destroy_handle(h);
    exit(1);
}

unsigned short in_checksum(unsigned short buffer, int size)
{
    unsigned long cksum = 0;

    while(size 1) {
            cksum += buffer++;
            size  -= sizeof(unsigned short);
    }
    if(size)
            cksum += (unsigned char )buffer;

    cksum  = (cksum  16) + (cksum & 0xffff);
    cksum += (cksum 16);
    return (unsigned short)(~cksum);
}

unsigned short tcp_checksum(struct iphdr iph, struct tcphdr tcph, 
                                            char data, int size)
{
    char buffer[65536];
    struct pseudo_tcphdr psd_header;

    psd_header.ip_dst   = iph-daddr;
    psd_header.ip_src   = iph-saddr;
    psd_header.zero     = 0;
    psd_header.protocol = iph-protocol;
    psd_header.tcp_len  = htons(sizeof(struct tcphdr)+size);

    tcph_check = 0;
    memcpy(buffer, &psd_header, sizeof(struct pseudo_tcphdr));
    memcpy(buffer+sizeof(struct pseudo_tcphdr), tcph, 
                                    sizeof(struct tcphdr));
    memcpy(buffer+sizeof(struct pseudo_tcphdr)+sizeof(struct tcphdr), 
                                                            data, size);
    return tcph-check = in_checksum((unsigned short )buffer,
            sizeof(struct pseudo_tcphdr)+sizeof(struct tcphdr)+size);
}

void show_buffer(unsigned char buf, int len)
{
    int i, j;
    char str[17];

    str[16] = 0;
    printf(n);
    for (i = 0; i  len; i += 16) { 
            fprintf(stdout,     );
            for (j = 0; j  16 && i+j  len; j++) {
                    fprintf(stdout,  %02x , buf[i+j]);

                    if (buf[i+j]  32 && buf[i+j]  127)
                            str[j] = buf[i+j];
                    else
                            str[j] = '.';
            }

            for (; j  16; j++) {
                    fprintf(stdout,     , buf[i+j]);
                    str[j] = ' ';
            }
            printf(      %s   n, str);
    }
}

/*void raw_send(unsigned char buf, int len)
{

     Create a raw socket 
    int s = socket (PF_INET, SOCK_RAW, IPPROTO_TCP);

    if(s == -1)
    {
            perror(Failed to create socket);
            exit(1);
    }

     //IP header 
    struct iphdr iph = (struct iphdr ) buf;

     //TCP header 
    struct tcphdr tcph = (struct tcphdr ) (buf + sizeof (struct ip));

     //Destination address resolution 
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = tcph-dest;
    sin.sin_addr.s_addr = iph-daddr;

     //Tell to the kernel that headers are included in the packet 
    int one = 1;
    const int val = &one;

    if (setsockopt (s, IPPROTO_IP, IP_HDRINCL, val, sizeof (one))  0)
    {
            perror(Error setting IP_HDRINCL);
            exit(0);
    }

    printf (Ready to send);
    show_buffer(buf,len);

     Send the packet 
    if (sendto (s, buf, len , 0, (struct sockaddr ) &sin, sizeof (sin))  0)
            perror(sendto failed);
    else
            printf (Packet Send. Length  %d n , len);

    close(s);
}*/

int main()
{
    int status;
    unsigned char buf[BUFSIZE];
    struct ipq_handle h;
    size_t pack_len;
    int i;
    struct iphdr iph;
    struct tcphdr tcph;
    unsigned char pack;
    char src_addr, dst_addr;
    long long count;

     
      //Initialisation
      //IPV4 protocol only
     
    h = ipq_create_handle(0, NFPROTO_IPV4);
    if (!h)
            die(h);

    
      //Setting the Queue Mode 
      //Get packet metadata and packet payloads 
     
    status = ipq_set_mode(h, IPQ_COPY_PACKET, BUFSIZE);
    if (status  0)
            die(h);

     //Receiving Packets from the Queue 
    count = 1;
    do {
            status = ipq_read(h, buf, BUFSIZE, 0);
            if (status  0)
                    die(h);

            fprintf(stdout,"%d", count++);

            switch (ipq_message_type(buf)) {
            case NLMSG_ERROR
                    fprintf(stderr, Received error message %dn,
                                            ipq_get_msgerr(buf));
                    break;
            case IPQM_PACKET {
                    ipq_packet_msg_t m = ipq_get_packet(buf);

                     //get and show packet length 
                    pack_len = m-data_len;
                    fprintf(stdout, "%d", pack_len);

                     //Show original packet 
                    fprintf(stdout, Payload );
                    show_buffer(m-payload, pack_len);

                     /*Create new changed packet 
                    pack = (unsigned char ) malloc(pack_len);
                    memset((char )pack, '0', pack_len);
                    memcpy(pack, m-payload, pack_len);
                    iph = (struct iphdr ) pack;

                     change something 
                    iph-tos = 0x30;

                     Change IP checksum 
                    iph-check = 0;
                    iph-check = (unsigned short) in_checksum(
                            (unsigned short ) iph, sizeof(struct iphdr));

                     Change TCP checksum 
                    tcph = (struct tcphdr ) &pack[ iph-ihl  4 ];
                    tcph-check = 0;
                    tcph-check = (unsigned short) tcp_checksum(
                                    iph, tcph, (char )tcph + 20, 
                                    pack_len - sizeof(struct iphdr) 
                                    - sizeof(struct tcphdr));

                     Show new packet 
                    fprintf(stdout, Changed );
                    show_buffer(pack, pack_len);

                     Drop original packet in netfilter 
                    status = ipq_set_verdict(h, m-packet_id, NF_DROP, 
                                    pack_len, (unsigned char ) pack);
                    if (status  0)
                            die(h);

                     Send changed packet 
                    raw_send(pack, pack_len);*/

                    break;
                    }
            default
                    fprintf(stderr, Unknown message type!n);
                    break;
            }
    } while (1);

    ipq_destroy_handle(h);
    return 0;
}
