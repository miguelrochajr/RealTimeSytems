#include <time.h> //clock()
#include <iostream>
#include <pthread.h>
#include <math.h>
#include <unistd.h>// sleep() and usleep()
#include <string>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"

// Inclua as classes que achar necessario

#define UNIT_MS 1000;
#define UNIT_SEC 1000000;

using namespace std;


BlackLib::BlackGPIO led(BlackLib::GPIO_51, BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO button(BlackLib::GPIO_49, BlackLib::input, BlackLib::SecureMode);


enum STATES {
	INITIAL,
	LED_FLASH,
	READ_USER_TIME,
	DISPLAY_REACTION_TIME,
	TURN_OFF_DISPLAY
};


void state_INITIAL (STATES &state){
	cout << "COWNTDOWN!\n";
	cout << "3 \n";
	usleep(1000000);
	cout << "2 \n";
	usleep(1000000);
	cout <<"1 \n";
	state = LED_FLASH;
}

void state_LED_FLASH (STATES &state){

	float r2 = static_cast<float> (rand())/ (static_cast<float>(RAND_MAX/3)); //generates a random float
	int sleepTime;

	r2 *= 1000000;
	sleepTime = (int)(r2);
	usleep(sleepTime);
	led.setValue(BlackLib::high);
	state = READ_USER_TIME;
}

void state_READ_USER_TIME (STATES &state, double &reactionTime){
	cout << "READ USER TIME \n";	
	clock_t clock1, clock2;
	string input = "1";
	
	clock1 = clock();
	while(true){
		if(button.getValue() == "1") break;
	}
	clock2 = clock();
	reactionTime = (double)(clock2 - clock1)/(double)CLOCKS_PER_SEC;
	state = DISPLAY_REACTION_TIME;
}
void state_DISPLAY_REACTION_TIME (STATES &state, double reactionTime ){
	static bool flag = 1;
	if(flag){
		cout << "Reaction time: "<< reactionTime << endl;
		flag = 0;
	}
}
void state_TURN_OFF_DISPLAY (STATES &state){
	cout << "TURN OFF DISPLAY \n";	
}
int main(int argc, char * argv[])
{
	cout << "GPIO - Tarefa 1.4" << endl;
	STATES state;
	double reactionTime = 0;
	state = INITIAL;

	while(true){
		switch(state){
			case INITIAL: state_INITIAL(state); break;
			case LED_FLASH: state_LED_FLASH(state); break;
			case READ_USER_TIME: state_READ_USER_TIME(state, reactionTime); break;
			case DISPLAY_REACTION_TIME: state_DISPLAY_REACTION_TIME(state, reactionTime); break;
			case TURN_OFF_DISPLAY: state_TURN_OFF_DISPLAY(state); break;
		}
	}
	return 0;
}
