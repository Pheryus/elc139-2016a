#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

typedef struct 
 {
   double *a;
   double *b;
   double c; 
   int wsize;
   int repeat; 
 } dotdata_t;


long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

void fill(double *a, int size, double value)
{  
   int i;
   for (i = 0; i < size; i++) {
      a[i] = value;
   }
}
   


// Variaveis globais, acessiveis por todas threads
dotdata_t dotdata;

int main(int argc, char **argv){
	int nthreads, wsize, repeat;
   long start_time, end_time;

   if ((argc != 4)) {
      printf("Uso: %s <nthreads> <worksize> <repetitions>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   nthreads = atoi(argv[1]); 
   wsize = atoi(argv[2]);  // worksize = tamanho do vetor de cada thread
   repeat = atoi(argv[3]); // numero de repeticoes dos calculos (para aumentar carga)

   // Cria vetores
   dotdata.a = (double *) malloc(wsize*nthreads*sizeof(double));
   fill(dotdata.a, wsize*nthreads, 0.01);
   dotdata.b = (double *) malloc(wsize*nthreads*sizeof(double));
   fill(dotdata.b, wsize*nthreads, 1.0);
   dotdata.c = 0.0;
   dotdata.wsize = wsize;
   dotdata.repeat = repeat;

   // Calcula c = a . b em nthreads, medindo o tempo
   start_time = wtime();

   int i, j, k;
   double *a = dotdata.a;
   double *b = dotdata.b;     
   wsize = dotdata.wsize;
   double mysum;
   double aux = 0;

   #pragma omp parallel for num_threads(nthreads) reduction(+: aux) private(j,mysum,i, k)
   for (j=0; j < nthreads; j++){
      for (k = 0; k < dotdata.repeat; k++) {
         mysum = 0.0;
         for (i = 0; i < wsize;i++)  
            mysum += (a[i] * b[i]);
      }
       aux += mysum;    
   }
   dotdata.c = aux;

   end_time = wtime();

   // Mostra resultado e estatisticas da execucao
   printf("%f\n", dotdata.c);
   printf("%d thread(s), %ld usec\n", nthreads, (long) (end_time - start_time));
   fflush(stdout);

   free(dotdata.a);
   free(dotdata.b);

   return EXIT_SUCCESS;
}


