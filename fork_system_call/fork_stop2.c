#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int result = fork();

    if(result < 0)
    {
        printf("llamada a fork ha fallado\n");
        exit(-1);
    }
    
    if(result)
    {
        wait(NULL);
        printf("Salida ps:\n");
        execlp("ps", "ps" , (char*)0);

    }   
    else
    {
        printf("Salida ls:\n");
        execlp("ls", "ls" , (char*)0);

    }
}