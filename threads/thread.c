#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_funct(void* arg)
{

    char* value = (char*) arg;
    printf("Este la funcion thread\n");
    printf("el valor de %s", value);

}


int main()
{

    pthread_t thread;

    char* value = "hack the planet";
    pthread_create(&thread, NULL, thread_funct, (void *)value);
    pthread_join(thread, NULL);
}