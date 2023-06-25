#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{

    int result = fork();
    int codigo;

    if(result < 0)
    {
        printf("llamada a fork ha fallado\n");
        exit(-1);
    }
    
    if(result)
    {
        printf("Soy el padre, ejecutare un ps, pero antes espero al hijo\n");
        wait( &codigo);
        if(codigo != 0)
        {
            printf("el proceso hijo tuvo un error\n");
        }
        printf("salido hjo: %i\n", codigo);
        printf("Ejecutando ps\n");
    }
    else
    {
        printf("Soy el hijo, ejecutare un ls\n");
        // exit(-1);
    }

}