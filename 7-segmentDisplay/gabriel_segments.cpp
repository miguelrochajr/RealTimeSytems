#include <iostream>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h"

// SETUP (MUDAR O PINOS!)
BlackLib::BlackGPIO led_a(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_b(BlackLib::GPIO_52,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_c(BlackLib::GPIO_53,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_d(BlackLib::GPIO_54,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_e(BlackLib::GPIO_55,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_f(BlackLib::GPIO_56,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO led_g(BlackLib::GPIO_57,BlackLib::output, BlackLib::SecureMode);

BlackLib::BlackGPIO dot(BlackLib::GPIO_58,BlackLib::output, BlackLib::SecureMode);

BlackLib::BlackGPIO c1(BlackLib::GPIO_59,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO c2(BlackLib::GPIO_60,BlackLib::output, BlackLib::SecureMode);
// BlackLib::BlackGPIO c3(BlackLib::GPIO_61,BlackLib::output, BlackLib::SecureMode);
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
     led_a.setValue(BlackLib::low);
     led_b.setValue(BlackLib::high);
     led_c.setValue(BlackLib::high);
     led_d.setValue(BlackLib::low);
     led_e.setValue(BlackLib::high);
     led_f.setValue(BlackLib::high);
     led_g.setValue(BlackLib::low);
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
     c4.setValue(BlackLib::low);
     break;
   case 2: //select digit 2 to write
     c1.setValue(BlackLib::low);
     c2.setValue(BlackLib::high);
     c3.setValue(BlackLib::low);
     c4.setValue(BlackLib::low);
     break;
  //  case 3: //select digit 3 to write
  //    c1.setValue(BlackLib::low);
  //    c2.setValue(BlackLib::low);
  //    c3.setValue(BlackLib::high);
  //    c4.setValue(BlackLib::low);
  //    break;
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
     c4.setValue(BlackLib::low);
     break;
 }
}

// função usada para escrever um ponto flutuante no display
void write_on_display(double number){
  //primeiramente devemos converter o número em um array de caracteres
  int number_int = number * 1000;
  char number_array[3];
  sprintf(number_array, "%d", number_int);

  //checamos se o número é menor ou maior que 10s para colocarmos o ponto flutuante no local certo do display
  if(number < 10){
    select_digit(1);
    write_number(number_array[0]);
    dot.setValue(BlackLib::low);
    usleep(5);

    select_digit(2);
    write_number(number_array[1]);
    dot.setValue(BlackLib::high);
    usleep(5);

  //   select_digit(3);
  //   write_number(number_array[2]);
  //   dot.setValue(BlackLib::high);
  //   usleep(5);
  //
  //   select_digit(4);
  //   write_number(number_array[3]);
  //   dot.setValue(BlackLib::high);
  //   usleep(5);
  // }
  else{
    select_digit(1);
    write_number(number_array[0]);
    dot.setValue(BlackLib::high);
    usleep(5);

    select_digit(2);
    write_number(number_array[1]);
    dot.setValue(BlackLib::low);
    usleep(5);

    // select_digit(3);
    // write_number(number_array[2]);
    // dot.setValue(BlackLib::high);
    // usleep(5);
    //
    // select_digit(4);
    // write_number(number_array[3]);
    // dot.setValue(BlackLib::high);
    // usleep(5);

  }

}


int main(int argc, char * argv[]){
  while(1){
    //escreve um número no display
    write_on_display(3.546);
  }

  return 0;
}
