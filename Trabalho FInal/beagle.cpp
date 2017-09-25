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
#include<semaphore.h>
#include<pthread.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"

using namespace std;

#define BUFSIZE 2048
#define POT_ADDR "225.0.0.37"
#define POT_PORT 9733

#define LED_PORT 9743
#define LED_ADDR "225.0.0.42"
#define MSGBUFSIZE 256

void *Server_pot(void* arg);
void *Server_leds(void* arg);
void *Update_vectors(void* arg);
int normalize(int ad_read);

BlackLib::BlackGPIO led0(BlackLib::GPIO_44,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led1(BlackLib::GPIO_26,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led2(BlackLib::GPIO_46,BlackLib::output, BlackLib::SecureMode);

ADC ad0(AIN3);
ADC ad1(AIN1);
ADC ad2(AIN2);

float vetorP[3];
bool vetorLeds[9];

int main(void){
  pthread_t pot_thread, led_thread, update_thread;

  pthread_create(&pot_thread, NULL, Server_pot, NULL);
  pthread_create(&led_thread, NULL, Server_leds, NULL);
  pthread_create(&update_thread, NULL, Update_vectors, NULL);

  pthread_join(pot_thread, NULL);
  pthread_join(led_thread, NULL);
  pthread_join(update_thread, NULL);

  return 0;
}

void *Server_pot(void* arg){
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
  addr.sin_addr.s_addr=inet_addr(POT_ADDR);
  addr.sin_port=htons(POT_PORT);

  /* now just sendto() our destination! */
  while(1){
      sleep(1);//sleep por 1 segundo
      if (sendto(fd,vetorP,sizeof(vetorP),0,(struct sockaddr *) &addr,
		     sizeof(addr)) < 0) {
	       perror("sendto");
	       exit(1);
	    }
  }
}

void *Server_leds(void* arg){
  struct sockaddr_in addr;
    int fd, nbytes;
    socklen_t addrlen;
    struct ip_mreq mreq;

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
    addr.sin_port=htons(LED_PORT);

    /* bind to receive address */
    if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
   perror("bind");
   exit(1);
    }

    /* use setsockopt() to request that the kernel join a multicast group */
    mreq.imr_multiaddr.s_addr=inet_addr(LED_ADDR);
    mreq.imr_interface.s_addr=htonl(INADDR_ANY);
    if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
   perror("setsockopt");
   exit(1);
    }

    /* now just enter a read-print loop */
    while (1) {
       addrlen=sizeof(addr);
       recvfrom(fd,&vetorLeds,sizeof(vetorLeds),0, (struct sockaddr *) &addr,&addrlen);

    }
}

void *Update_vectors(void* arg){

  for(int i = 0; i<3;i++)
    vetorP[i] = (i+1)*10;

  int cont = 0;

  while(1){
    sleep(1);

    vetorP[0] = normalize(ad0.getIntValue());
    vetorP[1] = normalize(ad1.getIntValue());
    vetorP[2] = normalize(ad2.getIntValue());

    if(vetorLeds[0] == true);
      led0.setValue(BlackLib::high);
    else
      led0.setValue(BlackLib::low);

    if(vetorLeds[1] == true);
      led1.setValue(BlackLib::high);
    else
      led1.setValue(BlackLib::low);

    if(vetorLeds[2] == true);
      led2.setValue(BlackLib::high);
    else
      led2.setValue(BlackLib::low);

    printf("Valores enviados: %.2f, %.2f, %.2f \n", vetorP[0],vetorP[1],vetorP[2] );
    printf("Valores recebidos: %d, %d, %d \n",vetorLeds[0], vetorLeds[1], vetorLeds[2]);

  }
}

int normalize(int ad_read){
    int ad_min = 0;
    int ad_max = 4096;
    int min = 0;
    int max = 100;

    float convertion_factor =(float)(max - min) / (float)(ad_max - ad_min);

    int normal = (ad_read - ad_min) * convertion_factor + min;

    return normal;
}
