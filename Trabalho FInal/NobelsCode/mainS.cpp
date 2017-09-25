#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include "ADC/Adc.h" // biblioteca para usar o 

ADC ad0(AIN0);
ADC ad1(AIN1);
ADC ad2(AIN2);

struct dado {
          int idade;
          char nome[34];
      };
struct Entradas {
          float pot[3];
    };
    struct Saidas {
          bool vetorLeds[9];
    };
void DieWithError(char *errorMessage);
void readAD(Entradas* entradas);
void readADb(Saidas* saidas);



int main(int argc, char *argv[])
{
    int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
    char broadcastIP[256];                /* IP broadcast address */
    unsigned short broadcastPort;     /* Server port */
    int broadcastPermission;          /* Socket opt to set permission to broadcast */
    unsigned int sendStringLen;       /* Length of string to broadcast */

    strcpy(broadcastIP, "225.0.0.37");       /* First arg:  broadcast IP address */
    broadcastPort = 9736;    /* Second arg:  broadcast port */


    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        exit(1);

    /* Construct local address structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);/* Broadcast IP address */
    broadcastAddr.sin_port = htons(broadcastPort);         /* Broadcast port */
    Entradas entradas;
    readAD(&entradas);

    
    sendStringLen = sizeof(entradas);
//printf("Teste\n");
    while (1){
		readAD(&entradas);
		//montar struct
         /* Broadcast sendString in datagram to clients every 3 seconds*/
       /* printf("Teste\n");
        for(int i =0;i<3;i++){
      printf("%i :%lf\n",i,entradas.pot[i]);
    }   */   
  if (sendto(sock, &entradas, sizeof(entradas), 0, (struct sockaddr *)
               &broadcastAddr, sizeof(broadcastAddr)) != sendStringLen)
             exit(3);
  /* Avoids flooding the network */
    }
    /* NOT REACHED */
}

void readAD(struct Entradas* entradas){
  entradas->pot[0] = ad0.getFloatValue()*100/1.8;
  entradas->pot[1] = ad1.getFloatValue()*100/1.8;
  entradas->pot[2] = ad2.getFloatValue()*100/1.8;
}