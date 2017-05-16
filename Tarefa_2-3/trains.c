#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>


#define N 3
#define RUNNING 0
#define WATING_TRACKS 1
#define USING_FIRST_TRACK 2
#define USING_SECOND_TRACK 3

sem_t lock;
sem_t tracks[N];

void *train(void *num);
int time_to_sleep(int train_num);
void update_leds(int train_num, int state);

int state[N];
int train_num[N]={0,1,2};


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

        // // SEGUNDO ESTADO: ESPERANDO LIBERAÇÃO DOS TRILHOS
        // state[train_num] = WATING_TRACKS;
        // printf("Train %d is WATING_TRACKS\n",train_num);
        // update_leds(train_num, state[train_num]);
        // sleep(time_to_sleep(train_num));

        //esperamos o lock para poder entrar na região crítica
        sem_wait(&lock);
        sem_wait(&tracks[train_num]);
        sem_wait(&tracks[(train_num+1)%N]);
        printf("-- Train %d takes tracks %d and %d --\n",train_num,train_num,(train_num+1)%N);

        // SEGUNDO ESTAGIO: USANDO O PRIMEIRO TRILHO COMPARTILHADO
        state[train_num] = USING_FIRST_TRACK;
        update_leds(train_num, state[train_num]);
        sleep(time_to_sleep(train_num));

        // TERCEIRO ESTAGIO: USANDO O PRIMEIRO TRILHO COMPARTILHADO
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

    switch (train_num) {
        case 0:
            // ### LER AD0 ###
            time = 1;
            break;
        case 1:
            // ### LER AD1 ###
            time = 2;
            break;
        case 2:
            // ### LER AD2 ###
            time = 15;
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
                // ### R1 = ON  ###
                // ### R2 = OFF ###
                // ### R3 = OFF ###
                printf("Train %d is RUNNING\n",train_num);
                break;
            case USING_FIRST_TRACK:
                // ### R1 = OFF ###
                // ### R2 = ON  ###
                // ### R3 = OFF ###
                printf("Train %d is USING_FIRST_TRACK\n",train_num);
                break;
            case USING_SECOND_TRACK:
                // ### R1 = OFF ###
                // ### R2 = OFF ###
                // ### R3 = ON  ###
                printf("Train %d is USING_SECOND_TRACK\n",train_num);
                break;
        }
    }
    else if(train_num == 1){
        switch (state) {
            case RUNNING:
                // ### G1 = ON  ###
                // ### G2 = OFF ###
                // ### G3 = OFF ###
                printf("Train %d is RUNNING\n",train_num);
                break;
            case USING_FIRST_TRACK:
                // ### G1 = OFF ###
                // ### G2 = ON  ###
                // ### G3 = OFF ###
                printf("Train %d is USING_FIRST_TRACK\n",train_num);
                break;
            case USING_SECOND_TRACK:
                // ### G1 = OFF ###
                // ### G2 = OFF ###
                // ### G3 = ON  ###
                printf("Train %d is USING_SECOND_TRACK\n",train_num);
                break;
        }
    }
    else if (train_num == 2) {
        switch (state) {
            case RUNNING:
                // ### B1 = ON  ###
                // ### B2 = OFF ###
                // ### B3 = OFF ###
                printf("Train %d is RUNNING\n",train_num);
                break;
            case USING_FIRST_TRACK:
                // ### B1 = OFF ###
                // ### B2 = ON  ###
                // ### B3 = OFF ###
                printf("Train %d is USING_FIRST_TRACK\n",train_num);
                break;
            case USING_SECOND_TRACK:
                // ### B1 = OFF ###
                // ### B2 = OFF ###
                // ### B3 = ON  ###
                printf("Train %d is USING_SECOND_TRACK\n",train_num);
                break;
        }
    }
    else{
        printf("!DEU MERDA!");
    }
}
