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

bool buttonPressed = false;

using namespace std;


BlackLib::BlackGPIO led(BlackLib::GPIO_51, BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO button(BlackLib::GPIO_49, BlackLib::input, BlackLib::SecureMode);

//Setup dos pinos pro 7segment
BlackLib::BlackGPIO led_a(BlackLib::GPIO_23,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_b(BlackLib::GPIO_47,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_c(BlackLib::GPIO_46,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_d(BlackLib::GPIO_22,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_e(BlackLib::GPIO_27,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_f(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_g(BlackLib::GPIO_26,BlackLib::output, BlackLib::SecureMode);

BlackLib::BlackGPIO dot(BlackLib::GPIO_65,BlackLib::output, BlackLib::SecureMode);

BlackLib::BlackGPIO c1(BlackLib::GPIO_44,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO c2(BlackLib::GPIO_20,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO c3(BlackLib::GPIO_7,BlackLib::output, BlackLib::SecureMode);
// BlackLib::BlackGPIO c4(BlackLib::GPIO_62,BlackLib::output, BlackLib::SecureMode);

//função usada para escrever um número de 0 a 9 no display
void write_number(char value){
 switch(value){
   case '0': //write 0 to the display
      led_a.setValue(BlackLib::low);
      led_b.setValue(BlackLib::low);
      led_c.setValue(BlackLib::low);
      led_d.setValue(BlackLib::low);
      led_e.setValue(BlackLib::low);
      led_f.setValue(BlackLib::low);
      led_g.setValue(BlackLib::high);
     break;
   case '1': //write 1 to the display
     led_a.setValue(BlackLib::high);
     led_b.setValue(BlackLib::low);
     led_c.setValue(BlackLib::low);
     led_d.setValue(BlackLib::high);
     led_e.setValue(BlackLib::high);
     led_f.setValue(BlackLib::high);
     led_g.setValue(BlackLib::high);
     break;
   case '2': //write 2 to the display
     led_a.setValue(BlackLib::low);
     led_b.setValue(BlackLib::low);
     led_c.setValue(BlackLib::high);
     led_d.setValue(BlackLib::low);
     led_e.setValue(BlackLib::low);
     led_f.setValue(BlackLib::high);
     led_g.setValue(BlackLib::low);
     break;
   case '3': //write 3 to the display
     led_a.setValue(BlackLib::low);
     led_b.setValue(BlackLib::low);
     led_c.setValue(BlackLib::low);
     led_d.setValue(BlackLib::low);
     led_e.setValue(BlackLib::high);
     led_f.setValue(BlackLib::high);
     led_g.setValue(BlackLib::low);
     break;
   case '4': //write 4 to the display
     led_a.setValue(BlackLib::high);
     led_b.setValue(BlackLib::low);
     led_c.setValue(BlackLib::low);
     led_d.setValue(BlackLib::high);
     led_e.setValue(BlackLib::high);
     led_f.setValue(BlackLib::low);
     led_g.setValue(BlackLib::low);
     break;
   case '5': //write 5 to the display
     led_a.setValue(BlackLib::low);
     led_b.setValue(BlackLib::high);
     led_c.setValue(BlackLib::low);
     led_d.setValue(BlackLib::low);
     led_e.setValue(BlackLib::high);
     led_f.setValue(BlackLib::low);
     led_g.setValue(BlackLib::low);
     break;
   case '6': //write 6 to the display
     led_a.setValue(BlackLib::low);
     led_b.setValue(BlackLib::high);
     led_c.setValue(BlackLib::low);
     led_d.setValue(BlackLib::low);
     led_e.setValue(BlackLib::low);
     led_f.setValue(BlackLib::low);
     led_g.setValue(BlackLib::low);
     break;
   case '7': //write 7 to the display
     led_a.setValue(BlackLib::low);
     led_b.setValue(BlackLib::low);
     led_c.setValue(BlackLib::low);
     led_d.setValue(BlackLib::high);
     led_e.setValue(BlackLib::high);
     led_f.setValue(BlackLib::high);
     led_g.setValue(BlackLib::high);
     break;
   case '8': //write 8 to the display
     led_a.setValue(BlackLib::low);
     led_b.setValue(BlackLib::low);
     led_c.setValue(BlackLib::low);
     led_d.setValue(BlackLib::low);
     led_e.setValue(BlackLib::low);
     led_f.setValue(BlackLib::low);
     led_g.setValue(BlackLib::low);
     break;
   case '9': //write 9 to the display
     led_a.setValue(BlackLib::low);
     led_b.setValue(BlackLib::low);
     led_c.setValue(BlackLib::low);
     led_d.setValue(BlackLib::high);
     led_e.setValue(BlackLib::high);
     led_f.setValue(BlackLib::low);
     led_g.setValue(BlackLib::low);
     break;
   default: //erro
     led_a.setValue(BlackLib::high);
     led_b.setValue(BlackLib::high);
     led_c.setValue(BlackLib::high);
     led_d.setValue(BlackLib::high);
     led_e.setValue(BlackLib::high);
     led_f.setValue(BlackLib::high);
     led_g.setValue(BlackLib::high);
     dot.setValue(BlackLib::high);
     break;
 }
}


//função usada para celecionar o dígito (1 a 4) onde o número será escrito
void select_digit(int value){
 switch(value){
   case 1: //select digit 1 to write
     c1.setValue(BlackLib::high);
     c2.setValue(BlackLib::low);
     c3.setValue(BlackLib::low);
     //c4.setValue(BlackLib::low);
     break;
   case 2: //select digit 2 to write
     c1.setValue(BlackLib::low);
     c2.setValue(BlackLib::high);
     c3.setValue(BlackLib::low);
     //c4.setValue(BlackLib::low);
     break;
    case 3: //select digit 3 to write
      c1.setValue(BlackLib::low);
      c2.setValue(BlackLib::low);
      c3.setValue(BlackLib::high);
      //c4.setValue(BlackLib::low);
      break;
  //  case 4: //select digit 4 to write
  //    c1.setValue(BlackLib::low);
  //    c2.setValue(BlackLib::low);
  //    c3.setValue(BlackLib::low);
  //    c4.setValue(BlackLib::high);
  //    break;
   default: //erro
     c1.setValue(BlackLib::low);
     c2.setValue(BlackLib::low);
     c3.setValue(BlackLib::low);
     //c4.setValue(BlackLib::low);
     break;
 }
}


// função usada para escrever um ponto flutuante no display
void write_on_display(double number){
  //primeiramente devemos converter o número em um array de caracteres
  int SONINHO = 1000;
  int number_int = number * 1000;
  char number_array[4];
  sprintf(number_array, "%d", number_int);

  //checamos se o número é menor ou maior que 10s para colocarmos o ponto flutuante no local certo do display
  if(number < 1){
    select_digit(1);
    write_number('0');
    dot.setValue(BlackLib::low);
    usleep(SONINHO);
    write_number('e');

    select_digit(2);
    write_number(number_array[0]);
    dot.setValue(BlackLib::high);
    usleep(SONINHO);
    write_number('e');

     select_digit(3);
     write_number(number_array[1]);
     dot.setValue(BlackLib::high);
     usleep(SONINHO);
     write_number('e');

  //   select_digit(4);
  //   write_number(number_array[3]);
  //   dot.setValue(BlackLib::high);
  //   usleep(5);
  // }
  } else if (number>=1 && number < 10){
    select_digit(1);
    write_number(number_array[0]);
    dot.setValue(BlackLib::low);
    usleep(SONINHO);
    write_number('e');

    select_digit(2);
    write_number(number_array[1]);
    dot.setValue(BlackLib::high);
    usleep(SONINHO);
    write_number('e');

     select_digit(3);
     write_number(number_array[2]);
     dot.setValue(BlackLib::high);
     usleep(SONINHO);
     write_number('e');

  //   select_digit(4);
  //   write_number(number_array[3]);
  //   dot.setValue(BlackLib::high);
  //   usleep(5);
  // }
  }else{
    select_digit(1);
    write_number(number_array[0]);
    dot.setValue(BlackLib::high);
    usleep(SONINHO);

    select_digit(2);
    write_number(number_array[1]);
    dot.setValue(BlackLib::low);
    usleep(SONINHO);

     select_digit(3);
     write_number(number_array[2]);
     dot.setValue(BlackLib::high);
     usleep(SONINHO);
    //
    // select_digit(4);
    // write_number(number_array[3]);
    // dot.setValue(BlackLib::high);
    // usleep(5);

  }

}



enum STATES {
	INITIAL, //este estado faz um countdown de 3s
	LED_FLASH, // este estado liga o LED num intervalo randomico de 3s
	READ_USER_TIME, //este estado le o tempo do usuario
	DISPLAY_REACTION_TIME, //este estado mostra o tempo de racao do usuario no display de 7 segmentos
};


void state_INITIAL (STATES &state){
	led.setValue(BlackLib::low);
	select_digit(1);

	cout << "COWNTDOWN!\n";
	write_number('3');
	usleep(1000000);
	write_number('2');
	usleep(1000000);
	write_number('1');
	usleep(1000000);
	write_number('0');
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
	
	while(button.getValue() == "1"){ }//wait until the button is released

	reactionTime = (double)(clock2 - clock1)/(double)CLOCKS_PER_SEC;
	state = DISPLAY_REACTION_TIME;
}

void state_DISPLAY_REACTION_TIME (STATES &state, double reactionTime ){
	cout << "WRITE REACTION TIME: " << reactionTime << endl;
	float reaction = (float)(reactionTime);
	while(true){		
		write_on_display(reaction);
		if(button.getValue() == "1") break;
	}
	write_on_display(-1); // zerar o display
	state = INITIAL;
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
		}
	}
	return 0;
}
