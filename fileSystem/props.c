#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char **argv)
{

    if(argc != 2)
    {
        printf("Uso: nombre de fichero\n");
        exit(-1);
    }

    struct stat data;
    char file_type[32];

    if(stat(argv[1], &data) != 0)
    {
        printf("Ha fallado la llamada a stat\n");
        exit(-1);
    }

    printf("Fichero:       %s\n", argv[1]);

    switch(data.st_mode & __S_IFMT)
    {
        case __S_IFREG:
            strcpy(file_type,"Es un fichero regular" );
            break;
        case __S_IFDIR:
            strcpy(file_type,"Es un directorio" );
            break;
        case __S_IFLNK:
            strcpy(file_type,"Es un enlace simbolico" );
            break;
        case __S_IFIFO:
            strcpy(file_type,"Es un tuberia FIFO" );
            break;
        default:
            strcpy(file_type,"Error, no tipo desconocido" );
    }

    printf("Tipo:          %s\n", file_type);
    printf("Propietario:   %lu\n", data.st_uid);
    printf("Permisos:      %o\n", data.st_mode & 0777);
    printf("Enlaces duros: %lu\n", data.st_nlink);
    printf("Tamaño:        %lu\n", data.st_size);
    printf("INODO:         %lu\n", data.st_ino);
    printf("Ultimo acceso: %s\n", ctime(&data.st_mtime));
}