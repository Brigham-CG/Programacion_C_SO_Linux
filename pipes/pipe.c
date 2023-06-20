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
        // sleep(2);
        strcpy(c,"hack the world!");
        close(fd[0]);
        write(fd[1], c, strlen(c)); 
        close(fd[1]);
        printf("soy el hijo y he escrito en fd[1]=%i: %s\n", fd[1], c);
    }
    else
    {
        close(fd[1]);
        read(fd[0], x, 20);
        close(fd[0]);   
        printf("soy el padre y he leido en fd[0]=%i: %s\n", fd[0], x);
    }
}