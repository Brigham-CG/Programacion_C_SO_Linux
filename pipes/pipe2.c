#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd[2];

    pipe(fd);

    char c[20];
    char x[20];

    if(fork())
    {
        // redirigir la entrada al fd de lectura
        close(fd[1]);
        close(0);
        dup(fd[0]);
        read(0, x, 20);
        // scanf("%s", x);   
        printf("soy el padre y he leido en fd[0]=%i: %s\n", fd[0], x);
    }
    else
    {
        //  redirigir la impresion hacia el fd de escritura
        strcpy(c,"hack the world!");
        close(fd[0]);
        close(1);
        dup(fd[1]);
        // write(fd[1], c, strlen(c)); 
        close(fd[1]);
        printf("%s\n", c);
    }
}