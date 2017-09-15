// Luiz Fernando Azevedo Vasconcellos
// lfav17@inf.ufpr.br

#include "vil_io.h"
#include "vil_data.h"

#include <stdlib.h>
#include <stdio.h>

image_t* read_file (char* file_name) {
    FILE *img_file = fopen(file_name, "r");
    if(!img_file) {
        fprintf(stderr, "Falha ao abrir arquivo %s\n",file_name);
        return NULL;
    }

    image_t *img = malloc(sizeof(*img));
    if(!img) {
        fprintf(stderr, "Falha ao alocar memoria ao ler a imagem %s\n", file_name);
        return NULL;
    }
    
    char format[10];
    fscanf(img_file,"%s", format);
    fscanf(img_file,"%i %i", &img->col, &img->row);;
    fscanf(img_file,"%i", &img->max);

    img->pixels = calloc(img->row, sizeof(*img->pixels));
    if(!img->pixels) {
        fprintf(stderr, "Falha ao alocar memoria para os pixels da imagem %s\n", file_name);
        fclose(img_file);
        return NULL;
    }
    for(int i=0; i < img->row; ++i) {
        img->pixels[i] = calloc(img->col, sizeof(**img->pixels));
        if(!img->pixels[i]) {
            fprintf(stderr, "Falha ao alocar memoria para os pixels da imagem %s na linha %i",
                    file_name, i);
            fclose(img_file);
            return NULL;
        }
    }

    for(int i=0; i < img->row; ++i) 
        for(int j=0; j < img->col; ++j) 
            fscanf(img_file,"%i", &img->pixels[i][j]);

    fclose(img_file);
    return img;
}

int write_file (char* file_name, image_t *img) {
    FILE *img_file = fopen(file_name,"w");
    if(!img_file) {
        fprintf(stderr,"Falha ao abrir arquivo %s\n",file_name);
        return -1;
    }

    fprintf(img_file,"P2\n%i %i\n%i\n", img->col, img->row, img->max);

    for(int i = 0; i < img->row; ++i) {
        for(int j = 0; j < img->col; ++j)
            fprintf(img_file,"%i ", img->pixels[i][j]);
        fprintf(img_file,"\n");
    }

    fclose(img_file);
    return 0;
}
