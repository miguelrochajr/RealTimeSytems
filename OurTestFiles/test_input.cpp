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
	long tempo = 1*UNIT_SEC;
	BlackLib::BlackGPIO button(BlackLib::GPIO_74, BlackLib::input, BlackLib::SecureMode);
	
	while(true){
		//if (button.getValue() == "1"){
		//	cout << "BUTTON PRESSED"<< endl;
		//}
		cout << "Valor: " << button.getValue() << endl;
		usleep(tempo);
	}

	return 0;
}

