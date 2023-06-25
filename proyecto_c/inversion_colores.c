#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct RGB
{
    int r; 
    int g; 
    int b; 
};

void invert_colors(struct RGB* data, bool edit)
{
    printf("\nColores antes de la conversion: %i %i %i\n", data->r, data->g, data->b);

    int r_ = 255 - data->r, g_ = 255 - data->g ,b_ = 255 - data->b;

    if(edit)
    {
        data->r = r_; data->g = g_; data->b = b_;
    }
    
    printf("Colores despues de la conversion: %i %i %i\n", r_, g_, b_);
}

bool count_lines_of_file(char * file_name, int *n_lines)
{   
    FILE * f;
    
    int line_size = 13;

    char* line_rgb = malloc(sizeof(char) * line_size);

    f = fopen(file_name, "r");

    if(f == NULL)
        return false;
    
    while(fgets(line_rgb, line_size, f) != NULL)
        (*n_lines)++;

    free(line_rgb);
    
    fclose(f);
    
    return true;
}

bool read_file(char * file_name, struct RGB* array_rgb, int *n_lines)
{

    FILE * f;


    int line_size = 13;
    char* line_rgb = malloc(sizeof(char) * line_size);
    char* value = malloc(sizeof(char) * 4);

    f = fopen(file_name, "r");

    if(f == NULL)
    {
        free(array_rgb);
        free(value);
        free(line_rgb);
        
        fclose(f);
        return false;
    }
    
    int index = 0;

    while(fgets(line_rgb, line_size, f) != NULL)
    {
        int pos_rgb = 0;
        int init = 0;
        
        for(char i = 0; i < strlen(line_rgb); i++)
        {
            if(line_rgb[i] == ' ' || line_rgb[i] == '\n')
            {
                char *val_char = malloc(sizeof(char) * ((i - init) + 1));

                for(int j = init, p; j < i; j++)
                    val_char[j - init] = line_rgb[j];

                int val = atoi(val_char);

                if(pos_rgb == 0)
                    array_rgb[index].r = val;
                else if(pos_rgb == 1)
                    array_rgb[index].g = val;
                else
                    array_rgb[index].b = val;

                init = i + 1;

                pos_rgb++;
                free(val_char);
            }

        }
        index++;
    }

    free(value);
    free(line_rgb);
    
    fclose(f);

    return true;
}

int main(int argc, char** argv)
{   
    if(argc > 2 || argc == 1)
    {
        printf("[!] Archivo con colores no pasado como parametro\n");
        return 1;
    }
    
    int n = 0;
    struct RGB *array_rgb; 

    if(!count_lines_of_file(argv[1], &n))
    {
        printf("[!] Error en la lectura del archivo\n");
        return 1;
    }

    printf("[+] Cantidad de colores: %i\n", n);

    array_rgb = malloc(sizeof(struct RGB) * (n));
 
    if(!read_file(argv[1], array_rgb, &n))
    {
        printf("[!] Error en la lectura del archivo\n");
        return 1;
    }
    
    printf("[+] Lectura del archivo correcta\n");

    for(int i = 0; i < n; i++)
    {
        invert_colors(&(array_rgb[i]), 1);
    }

    for(int i = 0; i < n; i++)
    {
        invert_colors(&(array_rgb[i]), 0);
    }
}

