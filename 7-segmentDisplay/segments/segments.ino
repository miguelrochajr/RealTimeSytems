/*
    A
   ----
F |    | B
  | G  |
   ----  
E |    | C
  |    |
   ----
    D
 */


int pin_a = 2;
int pin_b = 3;
int pin_c = 4;
int pin_d = 5;
int pin_e = 6;
int pin_f = 8;
int pin_g = 9;
int dot = 7;

int c1 = 10;
int c2 = 11;
int c3 = 12;
int c4 = 13;

//função usada para escrever um número de 0 a 9 no display
void write_number(char value){
  switch(value){
    case '0': //write 0 to the display 
      digitalWrite(pin_a, LOW);
      digitalWrite(pin_b, LOW);
      digitalWrite(pin_c, LOW);
      digitalWrite(pin_d, LOW);
      digitalWrite(pin_e, LOW);
      digitalWrite(pin_f, LOW);
      digitalWrite(pin_g, HIGH);
      break;
    case '1': //write 1 to the display 
      digitalWrite(pin_a, HIGH);   
      digitalWrite(pin_b, LOW);   
      digitalWrite(pin_c, LOW);   
      digitalWrite(pin_d, HIGH);   
      digitalWrite(pin_e, HIGH);   
      digitalWrite(pin_f, HIGH);   
      digitalWrite(pin_g, HIGH); 
      break;
    case '2': //write 2 to the display 
      digitalWrite(pin_a, LOW);   
      digitalWrite(pin_b, LOW);   
      digitalWrite(pin_c, HIGH);   
      digitalWrite(pin_d, LOW);   
      digitalWrite(pin_e, LOW);   
      digitalWrite(pin_f, HIGH);   
      digitalWrite(pin_g, LOW);
      break;
    case '3': //write 3 to the display 
      digitalWrite(pin_a, LOW);   
      digitalWrite(pin_b, LOW);   
      digitalWrite(pin_c, LOW);   
      digitalWrite(pin_d, LOW);   
      digitalWrite(pin_e, HIGH);   
      digitalWrite(pin_f, HIGH);   
      digitalWrite(pin_g, LOW); 
      break;    
    case '4': //write 4 to the display 
      digitalWrite(pin_a, HIGH);   
      digitalWrite(pin_b, LOW);   
      digitalWrite(pin_c, LOW);   
      digitalWrite(pin_d, HIGH);   
      digitalWrite(pin_e, HIGH);   
      digitalWrite(pin_f, LOW);   
      digitalWrite(pin_g, LOW); 
      break; 
    case '5': //write 5 to the display 
      digitalWrite(pin_a, LOW);   
      digitalWrite(pin_b, HIGH);   
      digitalWrite(pin_c, LOW);   
      digitalWrite(pin_d, LOW);   
      digitalWrite(pin_e, HIGH);   
      digitalWrite(pin_f, LOW);   
      digitalWrite(pin_g, LOW); 
      break; 
    case '6': //write 6 to the display 
      digitalWrite(pin_a, LOW);   
      digitalWrite(pin_b, HIGH);   
      digitalWrite(pin_c, LOW);   
      digitalWrite(pin_d, LOW);   
      digitalWrite(pin_e, LOW);   
      digitalWrite(pin_f, LOW);   
      digitalWrite(pin_g, LOW);  
      break;
    case '7': //write 7 to the display 
      digitalWrite(pin_a, LOW);   
      digitalWrite(pin_b, LOW);   
      digitalWrite(pin_c, LOW);   
      digitalWrite(pin_d, HIGH);   
      digitalWrite(pin_e, HIGH);   
      digitalWrite(pin_f, HIGH);   
      digitalWrite(pin_g, HIGH);
      break;
    case '8': //write 8 to the display 
      digitalWrite(pin_a, LOW);   
      digitalWrite(pin_b, LOW);   
      digitalWrite(pin_c, LOW);   
      digitalWrite(pin_d, LOW);   
      digitalWrite(pin_e, LOW);   
      digitalWrite(pin_f, LOW);   
      digitalWrite(pin_g, LOW); 
      break;
    case '9': //write 9 to the display 
      digitalWrite(pin_a, LOW);   
      digitalWrite(pin_b, LOW);   
      digitalWrite(pin_c, LOW);   
      digitalWrite(pin_d, HIGH);   
      digitalWrite(pin_e, HIGH);   
      digitalWrite(pin_f, LOW);   
      digitalWrite(pin_g, LOW); 
      break;
    default: //erro
      digitalWrite(pin_a, LOW);   
      digitalWrite(pin_b, HIGH);   
      digitalWrite(pin_c, HIGH);   
      digitalWrite(pin_d, LOW);   
      digitalWrite(pin_e, HIGH);   
      digitalWrite(pin_f, HIGH);   
      digitalWrite(pin_g, LOW);
      break;     
  } 
}

//função usada para celecionar o dígito (1 a 4) onde o número será escrito
void select_digit(int value){
  switch(value){
    case 1: //select digit 1 to write 
      digitalWrite(c1, HIGH);
      digitalWrite(c2, LOW);
      digitalWrite(c3, LOW);
      digitalWrite(c4, LOW);
      break;
    case 2: //select digit 2 to write
      digitalWrite(c1, LOW);
      digitalWrite(c2, HIGH);
      digitalWrite(c3, LOW);
      digitalWrite(c4, LOW);
      break;
    case 3: //select digit 3 to write
      digitalWrite(c1, LOW);
      digitalWrite(c2, LOW);
      digitalWrite(c3, HIGH);
      digitalWrite(c4, LOW);
      break;
    case 4: //select digit 4 to write
      digitalWrite(c1, LOW);
      digitalWrite(c2, LOW);
      digitalWrite(c3, LOW);
      digitalWrite(c4, HIGH);
      break;
    default: //erro
      digitalWrite(c1, LOW);
      digitalWrite(c2, LOW);
      digitalWrite(c3, LOW);
      digitalWrite(c4, LOW);
      break;
  }
}

// função usada para escrever um ponto flutuante no display
void write_on_display(double number){
  //primeiramente devemos converter o número em um array de caracteres
  int number_int = number *1000;
  char number_array[5];
  sprintf(number_array, "%d", number_int);

  //checamos se o número é menor ou maior que 10s para colocarmos o ponto flutuante no local certo do display
  if(number < 10){
    select_digit(1);
    write_number(number_array[0]);
    digitalWrite(dot, LOW);
    delay(5);
    select_digit(2);
    write_number(number_array[1]);
    digitalWrite(dot, HIGH);
    delay(5);
    select_digit(3);
    write_number(number_array[2]);
    digitalWrite(dot, HIGH);
    delay(5); 
    select_digit(4);
    write_number(number_array[3]);
    digitalWrite(dot, HIGH);
    delay(5); 
  }
  else{
     select_digit(1);
    write_number(number_array[0]);
    digitalWrite(dot, HIGH);
    delay(5);
    select_digit(2);
    write_number(number_array[1]);
    digitalWrite(dot, LOW);
    delay(5);
    select_digit(3);
    write_number(number_array[2]);
    digitalWrite(dot, HIGH);
    delay(5); 
    select_digit(4);
    write_number(number_array[3]);
    digitalWrite(dot, HIGH);
    delay(5);
    
  }
    
}


void setup() {
  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  pinMode(pin_c, OUTPUT);
  pinMode(pin_d, OUTPUT);
  pinMode(pin_e, OUTPUT);
  pinMode(pin_f, OUTPUT);
  pinMode(pin_g, OUTPUT);

  pinMode(dot, OUTPUT);
  digitalWrite(dot, HIGH);

  pinMode(c1, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(c3, OUTPUT);
  pinMode(c4, OUTPUT);

  write_on_display(3.546);
}

void loop() {
  
  
  
}
