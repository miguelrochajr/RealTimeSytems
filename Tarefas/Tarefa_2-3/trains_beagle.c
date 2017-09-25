#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include "BlackGPIO/BlackGPIO.h"
#include "ADC/Adc.h" // biblioteca para usar o ADC

#define N 3
#define RUNNING 0
#define WATING_TRACKS 1
#define USING_FIRST_TRACK 2
#define USING_SECOND_TRACK 3

sem_t lock;
sem_t tracks[N];

void *train(void *num);
void update_leds(int train_num, int state);
int time_to_sleep(int train_num);
int convert_to_seconds(int ad_read);

int state[N];
int train_num[N]={0,1,2};


BlackLib::BlackGPIO r1(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO r2(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO r3(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);

BlackLib::BlackGPIO g1(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO g2(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO g3(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);

BlackLib::BlackGPIO b1(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO b2(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);
BlackLib::BlackGPIO b3(BlackLib::GPIO_45,BlackLib::output, BlackLib::SecureMode);

ADC ad0(AIN0);
ADC ad1(AIN1);
ADC ad2(AIN2);


int main()
{
    int i;

    //criamos as trhead para cada trem
    pthread_t thread_id[N];

    //inicializamos um lock com valor 1
    sem_init(&lock,0,1);

    //inicializamos N semaforos com valor 0.
    //cada semaforo representa uma das 3 regiões cŕiticas
    for(i=0;i<N;i++)
        sem_init(&tracks[i],0,1);

    // criamos as N threads
    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,train,&train_num[i]);
    }

    //esperamos as N threads retornarem
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}

void *train(void *num)
{
    int train_num = *((int*)(num));

    while(1)
    {
        // PRIMEIRO ESTADO: USANDO O TRILHO INDIVIDUAL
        state[train_num] = RUNNING;
        update_leds(train_num, state[train_num]);
        sleep(time_to_sleep(train_num));

        //esperamos o lock para poder entrar na região crítica
        sem_wait(&lock);
        sem_wait(&tracks[train_num]);
        sem_wait(&tracks[(train_num+1)%N]);
        printf("-- Train %d takes tracks %d and %d --\n",train_num,train_num,(train_num+1)%N);

        // TERCEIRO ESTAGIO: USANDO O PRIMEIRO TRILHO COMPARTILHADO
        state[train_num] = USING_FIRST_TRACK;
        update_leds(train_num, state[train_num]);
        sleep(time_to_sleep(train_num));

        state[train_num] = USING_SECOND_TRACK;
        update_leds(train_num, state[train_num]);
        sleep(time_to_sleep(train_num));

        //postamos os semáforos e saimos da região cŕitica
        sem_post(&tracks[train_num]);
        sem_post(&tracks[(train_num+1)%N]);
        sem_post(&lock);
        printf("-- Train %d releasing tracks %d and %d --\n", train_num,train_num,(train_num+1)%N);
    }
}

int time_to_sleep(int train_num){
    int time = 0;
    int division_factor = 500;

    switch (train_num) {
        case 0:
            time = convert_to_seconds(ad0.getIntValue()); /// ### LER AD0 ###;
            break;
        case 1:
            time = convert_to_seconds(ad1.getIntValue());  // ### LER AD1 ###
            break;
        case 2:
            time = convert_to_seconds(ad2.getIntValue()); // ### LER AD2 ###
            break;
        default:
            return -1;
    }

    return time;
}

void update_leds(int train_num, int state){
    if(train_num == 0){
        switch (state) {
            case RUNNING:
                r1.setValue(BlackLib::high); // ### r1 = ON  ###
                r2.setValue(BlackLib::low);  // ### r2 = OFF ###
                r3.setValue(BlackLib::low);  // ### r3 = OFF ###
                printf("Train %d is RUNNING\n",train_num);
                break;
            case USING_FIRST_TRACK:
                r1.setValue(BlackLib::low);  // ### r1 = OFF ###
                r2.setValue(BlackLib::high); // ### r2 = ON  ###
                r3.setValue(BlackLib::low);  // ### r3 = OFF ###
                printf("Train %d is USING_FIRST_TRACK\n",train_num);
                break;
            case USING_SECOND_TRACK:
                r1.setValue(BlackLib::low);  // ### r1 = OFF ###
                r2.setValue(BlackLib::low);  // ### r2 = OFF ###
                r3.setValue(BlackLib::high); // ### r3 = ON  ###
                printf("Train %d is USING_SECOND_TRACK\n",train_num);
                break;
        }
    }
    else if(train_num == 1){
        switch (state) {
            case RUNNING:
                g1.setValue(BlackLib::high); // ### g1 = ON  ###
                g2.setValue(BlackLib::low);  // ### g2 = OFF ###
                g3.setValue(BlackLib::low);  // ### g3 = OFF ###
                printf("Train %d is RUNNING\n",train_num);
                break;
            case USING_FIRST_TRACK:
                g3.setValue(BlackLib::low);  // ### g3 = OFF ###
                g1.setValue(BlackLib::high); // ### g1 = ON  ###
                g2.setValue(BlackLib::low);  // ### g2 = OFF ###
                printf("Train %d is USING_FIRST_TRACK\n",train_num);
                break;
            case USING_SECOND_TRACK:
                g1.setValue(BlackLib::low);  // ### g1 = OFF ###
                g2.setValue(BlackLib::low);  // ### g2 = OFF ###
                g3.setValue(BlackLib::high); // ### g3 = ON  ###
                printf("Train %d is USING_SECOND_TRACK\n",train_num);
                break;
        }
    }
    else if (train_num == 2) {
        switch (state) {
            case RUNNING:
                b1.setValue(BlackLib::high); // ### b1 = ON  ###
                b2.setValue(BlackLib::low);  // ### b2 = OFF ###
                b3.setValue(BlackLib::low);  // ### b3 = OFF ###
                printf("Train %d is RUNNING\n",train_num);
                break;
            case USING_FIRST_TRACK:
                b3.setValue(BlackLib::low);  // ### b3 = OFF ###
                b1.setValue(BlackLib::high); // ### b1 = ON  ###
                b2.setValue(BlackLib::low);  // ### b2 = OFF ###
                printf("Train %d is USING_FIRST_TRACK\n",train_num);
                break;
            case USING_SECOND_TRACK:
                b1.setValue(BlackLib::low);  // ### b1 = OFF ###
                b2.setValue(BlackLib::low);  // ### b2 = OFF ###
                b3.setValue(BlackLib::high); // ### b3 = ON  ###
                printf("Train %d is USING_SECOND_TRACK\n",train_num);
                break;
        }
    }
    else{
        printf("!DEU MERDA!");
    }
}

int convert_to_seconds(int ad_read){
    int ad_min = 0;
    int ad_max = 4096;
    int time_min = 0;
    int time_max = 10;

    convertion_factor = (time_max - time_min) / (ad_max - ad_min)

    int time = (ad_read - ad_min) * convertion_factor + time_min;
    if(time <= 1)
        time =1;

    return time
}
