#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100

int *array;
int n_thread;
int *a_sum; 


void *sum(void *id_thread)
{
    int id_t = *(int*)id_thread;

    int div = SIZE / n_thread;
    int start = div *id_t;
    int end = start + div;

    if(id_t == n_thread - 1)
        end = SIZE;

    int sum = 0; 
    for(int i = start; i < end; i++)
        sum += array[i]; 

    a_sum[id_t] = sum;
    printf("El hilo %i tine como resultado la suma %i\n", id_t, sum);
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Se necesita pasar la cantidad de hilos a usar como parametro\n");
        exit(-1);
    }


    n_thread = atoi(argv[1]);
    int *id_thread = malloc(sizeof(int) * n_thread);
    pthread_t *t_array = malloc(sizeof(pthread_t) * n_thread);
    a_sum = malloc(sizeof(int) * n_thread);

    array = malloc(sizeof(int) * SIZE);

    int total = 0;
    
    for(int i = 1; i <= 100; i++)
        array[i - 1] = i;
    
    for(int i = 0; i < n_thread; i++)
    {
        id_thread[i] = i; 
        pthread_create(&t_array[i], NULL, sum, (void*) &id_thread[i]);
    }

    for(int i = 0; i < n_thread; i++)
    {
        pthread_join(t_array[i], NULL);
        total+=a_sum[i];
    }

    printf("total %i\n", total);
    free(id_thread);
    free(t_array);
    free(array);
}   