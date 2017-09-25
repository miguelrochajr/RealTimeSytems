#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

//definimos o endereço IP do servidor na rede interna
#define BUFSIZE 2048
#define MULTICAST_ADDR "225.0.0.37"
#define MULTICAST_PORT 9733

float vetorP[3];

int main(int argc, char *argv[]){
  struct sockaddr_in addr;
  int fd, cnt;
  struct ip_mreq mreq;

  /* create what looks like an ordinary UDP socket */
  if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
   perror("socket");
   exit(1);
  }

  /* set up destination address */
  memset(&addr,0,sizeof(addr));
  addr.sin_family=AF_INET;
  addr.sin_addr.s_addr=inet_addr(MULTICAST_ADDR);
  addr.sin_port=htons(MULTICAST_PORT);

  /* now just sendto() our destination! */

  for(int i = 0; i<3;i++)
    vetorP[i] = (i+1)*10;

  int cont = 0;
  while(1){
      printf("Servidor esperando ...\n");
      sleep(1);//sleep por meio segundo

      if (sendto(fd,vetorP,sizeof(vetorP),0,(struct sockaddr *) &addr,
		     sizeof(addr)) < 0) {
	       perror("sendto");
	       exit(1);
	    }

      for(int i = 0; i<3;i++)
         vetorP[i] = (i+1)*10 + cont;


      printf("Valores enviados: %.2f, %.2f, %.2f \n", vetorP[0],vetorP[1],vetorP[2] );
      cont++;

  }

}
