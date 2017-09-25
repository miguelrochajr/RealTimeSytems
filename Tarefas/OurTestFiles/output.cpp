/**
 * Autor: Tiago Fernandes de Miranda
 * Universidade Federal do Rio Grande do Norte
 */

#include <iostream>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"

// Inclua as classes que achar necessario

#define UNIT_MS 1000;
#define UNIT_SEC 1000000;

using namespace std;

int main(int argc, char * argv[])
{
	cout << "Example - GPIO" << endl;
	BlackLib::BlackGPIO led(BlackLib::GPIO_38, BlackLib::output, BlackLib::SecureMode);
	
	while(true){
		long tempo = UNIT_SEC;
		led.setValue(BlackLib::high);
		usleep(tempo);
		led.setValue(BlackLib::low);
		usleep(tempo);
	}
	return 0;
}
