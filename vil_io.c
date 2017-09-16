// Luiz Fernando Azevedo Vasconcellos
// lfav17@inf.ufpr.br

#include "vil_io.h"
#include "vil_data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

image_t* read_file (char* file_name) {
    // Open file and check the operation result
    FILE *img_file = fopen(file_name, "r");
    if(!img_file) {
        fprintf(stderr, "Falha ao abrir arquivo %s\n",file_name);
        return NULL;
    }

    // Alocate memory for the img
    image_t *img = malloc(sizeof(*img));
    if(!img) {
        fprintf(stderr, "Falha ao alocar memoria ao ler a imagem %s\n", file_name);
        return NULL;
    }
    
    // Read the header
    // TODO: ignore comments lines
    char format[10];
    fscanf(img_file,"%s", format);
    fscanf(img_file,"%i %i", &img->col, &img->row);;
    fscanf(img_file,"%i", &img->max);

    // Allocate memory for pixels, free stuff in case of failure
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

    if(!strcmp(format, "P2")) { // Read ASCII values
        img->format = PGM2;

        for(int i=0; i < img->row; ++i) 
            for(int j=0; j < img->col; ++j) 
                fscanf(img_file,"%i", &img->pixels[i][j]);
    } else if (!strcmp(format,"P5")) { // Read binarie values
        img->format = PGM5;
        int sz = (img->max < 256) ? 1 : 2; // 1 or 2 bytes for each pixel
        for(int i=0; i < img->row; ++i)
            for(int j=0; j < img->col; ++j)
                fread(&img->pixels[i][j], sz, 1, img_file);
    } else { // Don't know how to read this
        fprintf(stderr,"Formato de arquivo invalido.\n");
        fclose(img_file);
        return NULL;
    }

    // Close the file and return the image
    fclose(img_file);
    return img;
}

int write_file (char* file_name, image_t *img) {
    // Open file to write and check the operation result
    FILE *img_file = fopen(file_name,"w");
    if(!img_file) {
        fprintf(stderr,"Falha ao abrir arquivo %s\n",file_name);
        return -1;
    }

    if(img->format == PGM2) { // Writing in ASCII format
        fprintf(img_file,"P2\n%i %i\n%i\n", img->col, img->row, img->max);

        for(int i = 0; i < img->row; ++i) {
            for(int j = 0; j < img->col; ++j)
                fprintf(img_file,"%i ", img->pixels[i][j]);
            fprintf(img_file,"\n");
        }
    } else if (img->format == PGM5) { // Writing in binary format
        fprintf(img_file,"P5\n%i %i\n%i\n", img->col, img->row, img->max);
        int sz = (img->max < 256) ? 1 : 2;

        for(int i=0; i < img->row; ++i) 
            for(int j=0; j < img->col; ++j) 
                fwrite(&img->pixels[i][j], sz, 1, img_file); 
    }

    // Close file
    fclose(img_file);
    return 0;
}
