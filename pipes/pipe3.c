#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv)
{

    int pipe1[2];

    pipe(pipe1);


    if(argc != 2)
    {
        printf("Pasar un nombre de fichero");
        exit(-1);
    }

    if(fork())
    {

        close(pipe1[1]);
        close(0);
        dup(pipe1[0]);
        close(pipe1[0]); 
        
        close(1);
        open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0755);

        execlp("sort", "sort", "-u", NULL);
        printf("error sort");


    }
    else
    {
        int pipe2[2];

        pipe(pipe2);

        if(fork())
        {
            close(pipe2[1]);
            close(0);
            dup(pipe2[0]);
            close(pipe2[0]); 
            

            close(pipe1[0]);
            close(1);
            dup(pipe1[1]);
            close(pipe1[1]);

            execlp("cut", "cut", "-c5-12", NULL);
            printf("error cut");
        }
        else
        {
            close(pipe2[0]);
            close(1);
            dup(pipe2[1]);
            close(pipe2[1]); 
            execlp("ps", "ps", "-efl", NULL);
            printf("error ps");
        }
    }
}
