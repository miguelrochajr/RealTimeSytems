#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

#define N 3
#define RUNNING 0
#define WATING_TRACKS 1
#define USING_TRACKS 2

sem_t lock;
sem_t tracks[N];

void *train(void *num);
void use_tracks(int);
void release_tracks(int);
void test(int);

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
        printf("Train %d is RUNNING\n",i);
    }

    //esperamos as N threads retornarem
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}

void *train(void *train_num)
{
    int *i = train_num;

    while(1)
    {
        sleep(1);
        use_tracks(*i);
        sleep(0);

    }
}

void use_tracks(int train_num)
{
    //esperamos o lock para poder entrar na região crítica
    sem_wait(&lock);
    state[train_num] = WATING_TRACKS;
    printf("Train %d is WATING_TRACKS\n",train_num);

    sem_wait(&tracks[train_num]);
    sem_wait(&tracks[(train_num+1)%N]);
    //do the thing
    state[train_num] = USING_TRACKS;
    sleep(2);
    printf("Train %d takes tracks %d and %d\n",train_num,train_num,(train_num+1)%N);
    printf("Train %d is USING_TRACKS\n",train_num);


    sem_post(&tracks[train_num]);
    sem_post(&tracks[(train_num+1)%N]);
    sem_post(&lock);

    sleep(1);
    state[train_num] = RUNNING;
    printf("Train %d releasing tracks %d and %d \n", train_num,train_num,(train_num+1)%N);
    printf("Train %d is RUNNING\n",train_num);
}
