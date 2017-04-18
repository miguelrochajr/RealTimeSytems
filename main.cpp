
/**
 * Autores:
 	Carlos Gabriel
	Felipe Fernandes
	Phillipy
 * Universidade Federal do Rio Grande do Norte
 */

#include <iostream>
#include <pthread.h>
#include "BlackGPIO/BlackGPIO.h"
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include  <time.h>
#include <stdio.h>
#include <unistd.h>  // para: sleep()
#include <math.h>
#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#include "BlackADC/BlackADC.h" // biblioteca para usar o ADC

// Inclua as classes que achar necessario

using namespace std;

int main()
{

    BlackLib::BlackADC  pot1(BlackLib::AIN1);
    BlackLib::BlackGPIO led1(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);
    BlackLib::BlackGPIO led2(BlackLib::GPIO_23,BlackLib::output, BlackLib::SecureMode);

    //Inicia leds desligados
    led1.setValue(BlackLib::low);
    led2.setValue(BlackLib::low);

    while (true){

        cout<< "AD: "<<pot1.getNumericValue()<<endl;

        if(pot1.getNumericValue() > 1000)  // Verifica se a voltagem é maior que 1
        {
            led1.setValue(BlackLib::high);
            led2.setValue(BlackLib::low);
        }
        else
        {
            led1.setValue(BlackLib::low);
            led2.setValue(BlackLib::high);
        }
        usleep(500000); //500 mili segundos

    }

    return 0;
}
