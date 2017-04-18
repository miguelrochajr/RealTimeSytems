#include <iostream>
#include <sys/types.h>
#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "BlackGPIO/BlackGPIO.h"
#include "BlackLib/BlackADC/BlackADC.h" // biblioteca para usar o ADC

using namespace std;

// função para simular carregamento da CPU
void carga(int k){
  float f = 0.999999;
  for(int i=0; i<k; i++)
    {
      f = f*f*f*f*f;
      f = 1.56;
        for(int j=0; j<k; j++)
           {
	     f = sin(f)*sin(f)*f*f*f;

            }
    }
}

int main(){
	int filho1, filho2;
	int iteration_count = 0;

	BlackLib::BlackADC  ad1(BlackLib::AIN0);
	BlackLib::BlackADC  ad2(BlackLib::AIN1);
	BlackLib::BlackGPIO led1(BlackLib::GPIO_46,BlackLib::output, BlackLib::SecureMode);
	BlackLib::BlackGPIO led2(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);

	//Inicia leds desligados
	led1.setValue(BlackLib::low);
	led2.setValue(BlackLib::low);

	filho1 = fork();
	//se for o filho 1
	if(filho1 == 0){
		while(true){
			//--CODIGO PARA FILHO1--
			//cout << "FILHO 1 | PRIORITY: "<< getpriority(PRIO_PROCESS,getpid()) << endl;
			carga(1150); //carga de uso intenso da cpu (duração aproximada de 1 s)

			//checagem se é uma iteracao par ou impar
			if(iteration_count%2 == 0){
				led1.setValue(BlackLib::high);
			}
			else{
				led1.setValue(BlackLib::low);
			}

			iteration_count++;
		}
	}
	else{
		//se for o filho 2
		filho2 = fork();
		if(filho2 == 0){
			while(true){
				//--CODIGO PARA FILHO2--
				//cout << "FILHO 2 | PRIORITY: "<< getpriority(PRIO_PROCESS,getpid()) << endl;
				carga(1150); //carga de uso intenso da cpu (duração aproximada de 1 s)

				//checagem se é uma iteracao par ou impar
				if(iteration_count%2 == 0){
					led2.setValue(BlackLib::high);
				}
				else{
					led2.setValue(BlackLib::high);
				}
				iteration_count++;
			}
		}
	}

	while(true){
		//--CODIGO PARA PAI--
		//cout << "PAI | PID: " << getpid()<< " | PRIORITY: "<< getpriority(PRIO_PROCESS,getpid()) << endl;

		setpriority(PRIO_PROCESS, getpid(), 0); // seta prioridade do pai pra 0
		usleep(500000); // sleep por 500 ms

		// !!! LE O VALOR DO AD1 E DO AD2 !!!

		//muda a prioridade dos filhos de acordo com os valores de ad1 e ad2
		if (ad1.getNumericValue() >= 1000){
			setpriority(PRIO_PROCESS, filho1, 5);
			cout<<"AD1: "<<ad1.getNumericValue()<<endl;
		}
		else{
			setpriority(PRIO_PROCESS, filho1, 19);
			cout<<"AD1: "<<ad1.getNumericValue()<<endl;
		}
		if (ad2.getNumericValue() >= 1000){
			setpriority(PRIO_PROCESS, filho2, 5);
			cout<<"AD2: "<<ad2.getNumericValue()<<endl;
		}
		else{
			setpriority(PRIO_PROCESS, filho2, 19);
			cout<<"AD2: "<<ad1.getNumericValue()<<endl;
		}
	}
}
