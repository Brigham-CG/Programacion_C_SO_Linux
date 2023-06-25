#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <errno.h>

int num_threads = 1, num_files;
char *path, *name, *extension;

void *create_file(void *id_pointer)
{

    int id = *(int*) id_pointer;


    int files_to_create = num_files / num_threads;

    int start = files_to_create * id;
    int end =  start + files_to_create;

    if(id == num_threads - 1)
    {
        end = num_files;
    }

    char file[256];
    for(int i = start; i < end; i++)
    {
        sprintf(file, "%s/%s%03i.%s",path, name, i + 1,extension);  
        FILE *f = fopen(file, "w");
        printf("Soy el hilo \033[01;33m%i\033[0m voy a crear el fichero \033[01;34m'%s'\033[0m!\n", id, file);
    }
    pthread_exit(0);
}

void start_threads()
{

    pthread_t threads[num_threads];
    int thread_ids[num_threads];

    for(int i = 0; i < num_threads; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, create_file, (void *)&thread_ids[i]);

    }

    for(int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);
}

void eval_args(int argc, char **argv)
{

    if(argc < 5)
    {
        printf("Uso: nombre extension numero-de-ficheros ruta n°-hilos(opc)\n");
        exit(-1);
    }

    DIR *dir = opendir(argv[4]);

    if(errno == ENOENT)
    {
        printf("EL directorio %s no existe\n", argv[4]);
        exit(-1);
    }

    closedir(dir);

    name = argv[1];
    extension = argv[2];
    num_files = atoi(argv[3]);
    path = argv[4];

    if(argc == 6)
        num_threads = atoi(argv[5]);        
}

int main(int argc, char **argv)
{
    eval_args(argc, argv);
    start_threads();
}