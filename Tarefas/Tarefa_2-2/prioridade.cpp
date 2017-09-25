// UFRN-CT-DCA
// Disciplina: Sistemas de Tempo Real
// Programa: prioridade.cpp


#include  <time.h>
#include <iostream> // para: cout
#include <stdio.h>
#include <unistd.h>  // para: sleep()
#include <stdlib.h>
#include <math.h>

#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>

//using std::cout;
using namespace std;


// função para simular carregamento da CPU
void carga(int k)
{
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


int main(int argc, char**argv){

     clock_t time_1, time_2; 
     double tempoCPU;
     int load = atoi(argv[1]); 

     time_1 = clock();
     carga(load);// funcão de uso intenso de CPU
     //sleep(6);
     time_2 = clock();

     tempoCPU = (double)(time_2 - time_1) / (double)(CLOCKS_PER_SEC);

     cout <<"O tempo de carga foi de " << tempoCPU << endl;
     
     return 0;
}
