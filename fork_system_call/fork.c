#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // int var = 1;

    // for(int i = 0; i < 3; i++)
    // {
    //     int result = fork();

    //     printf("%i ", i);

    //     if(result)
    //     {
    //         printf("Este es el proceso padre: %i | pid: %i ppid: %i \n", result, getpid(), getppid());
    //         // break;
    //     }
    //     else
    //     {
    //         printf("Este es el proceso hijo: %i | pid: %i ppid: %i \n", result, getpid(), getppid());
    //     }
    // }

    int var = 0;

    for (int i = 0; i < 4; i++)
    {
        if(fork())
        {
            var++;
            break;
        }
        else
        {
            var+=2;
        }
    }
    printf("Soy el proceso %i, mi padre es %i, el valor es: %i\n", getpid(), getppid(), var);
}