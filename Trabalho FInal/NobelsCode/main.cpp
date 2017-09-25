#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define BUFSIZE 2048
#define SERVICE_PORT	21234	

#include "BlackGPIO/BlackGPIO.h"
struct Saidas {
      bool vetorLeds[9];
};
void ascenderLed(int i, bool valor);

BlackLib::BlackGPIO r1(BlackLib::GPIO_49,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO r2(BlackLib::GPIO_66,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO r3(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);

BlackLib::BlackGPIO g1(BlackLib::GPIO_47,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO g2(BlackLib::GPIO_27,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO g3(BlackLib::GPIO_67,BlackLib::output, BlackLib::SecureMode);

BlackLib::BlackGPIO b1(BlackLib::GPIO_68,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO b2(BlackLib::GPIO_44,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO b3(BlackLib::GPIO_26,BlackLib::output, BlackLib::SecureMode);
int
main(int argc, char **argv)
{
	struct sockaddr_in myaddr;	/* our address */
	struct sockaddr_in remaddr;	/* remote address */
	socklen_t addrlen = sizeof(remaddr);		/* length of addresses */
	int recvlen;			/* # bytes received */
	int fd;				/* our socket */
	int msgcnt = 0;			/* count # of messages we received */
	unsigned char buf[BUFSIZE];	/* receive buffer */
	Saidas saidas;


	/* create a UDP socket */

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		return 0;
	}

	/* bind the socket to any valid IP address and a specific port */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}

	/* now loop, receiving data and printing what we received */
	for (;;) {
		printf("waiting on port %d\n", SERVICE_PORT);
		recvlen = recvfrom(fd, &saidas, sizeof(saidas), 0, (struct sockaddr *)&remaddr, &addrlen);
		if (recvlen > 0) {
			buf[recvlen] = 0;
			for(int i =0;i<9;i++){
				ascenderLed(i,saidas.vetorLeds[i]);
			}
		}
		else
			printf("uh oh - something went wrong!\n");
		
	}
	/* never exits */
}


void ascenderLed(int i, bool valor){
    switch (i) {
      case 0:
          if(valor){
              r1.setValue(BlackLib::high);
         }else{
              r1.setValue(BlackLib::low);
          }
          break;
       case 1:
           if(valor){
               r2.setValue(BlackLib::high);
         }else{
              r2.setValue(BlackLib::low);
              }
              break;
      case 2:
          if(valor){
               r3.setValue(BlackLib::high);
         }else{
              r3.setValue(BlackLib::low);

          }
      break;
      case 3:
          if(valor){
              g1.setValue(BlackLib::high);
         }else{
              g1.setValue(BlackLib::low);

          }
      break;
      case 4:
          if(valor){
               g2.setValue(BlackLib::high);
         }else{
              g2.setValue(BlackLib::low);
			  }
      break;
      case 5:
          if(valor){
              g3.setValue(BlackLib::high);
         }else{
              g3.setValue(BlackLib::low);
          }
      break;
      case 6:
          if(valor){
              b1.setValue(BlackLib::high);
         }else{
              b1.setValue(BlackLib::low);
          }
      break;
      case 7:
          if(valor){
              b2.setValue(BlackLib::high);
         }else{
              b2.setValue(BlackLib::low);
          }
      break;
      case 8:
          if(valor){
              b3.setValue(BlackLib::high);
         }else{
              b3.setValue(BlackLib::low);
          }
      break;
    }
}