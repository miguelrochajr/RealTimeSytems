#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<iostream>

using namespace std;

#define HELLO_PORT 9733
#define HELLO_GROUP "225.0.0.37"
#define MSGBUFSIZE 256

float vetorP[3];

int main(int argc, char *argv[]){
     struct sockaddr_in addr; // socket address
     int fd;          // fd, number of bytes
     socklen_t addrlen;       //socket address lenght
     struct ip_mreq mreq;     //

     u_int yes=1;            /*** MODIFICATION TO ORIGINAL */

     /* create what looks like an ordinary UDP socket */
     if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
	  perror("socket");
	  exit(1);
     }

    /* allow multiple sockets to use the same PORT number */
    if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
       perror("Reusing ADDR failed");
       exit(1);
       }

     /* set up destination address */
     memset(&addr,0,sizeof(addr));
     addr.sin_family=AF_INET;
     addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
     addr.sin_port=htons(HELLO_PORT);

     /* bind to receive address */
     if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
	  perror("bind");
	  exit(1);
     }

     /* use setsockopt() to request that the kernel join a multicast group */
     mreq.imr_multiaddr.s_addr=inet_addr(HELLO_GROUP);
     mreq.imr_interface.s_addr=htonl(INADDR_ANY);
     if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
	  perror("setsockopt");
	  exit(1);
     }

     /* now just enter a read-print loop */
     while (1) {
    	  addrlen=sizeof(addr);
    	  recvfrom(fd,&vetorP,sizeof(vetorP),0, (struct sockaddr *) &addr,&addrlen);

          printf("Valores recebidos: %.2f, %.2f, %.2f \n", vetorP[0],vetorP[1],vetorP[2] );
    }
    return 0;
}
