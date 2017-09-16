// Luiz Fernando Azevedo Vasconcellos
// lfav17@inf.ufpr.br

#include "vil_filters.h"
#include "vil_data.h"
#include <stdlib.h>

void free_img(image_t *img) {
    for(int i = 0; i < img->row; ++i)
        free(img->pixels[i]);
    free(img->pixels);
    free(img);
}

image_t* alloc_img(image_t *img) {
    image_t *tmp = calloc(1, sizeof(*tmp));
    
    tmp->format = img->format;
    tmp->max = img->max;
    tmp->row = img->row;
    tmp->col = img->col;

    tmp->pixels = calloc(tmp->row, sizeof(*tmp->pixels));
    if(!tmp->pixels) {
        free(tmp);
        return NULL;
    }

    for(int i=0; i < tmp->row; ++i) {
        tmp->pixels[i] = calloc(tmp->col, sizeof(**tmp->pixels));
        if(!tmp->pixels[i]) {
            for(int j=0; j < i-1;++j)
                free(tmp->pixels[j]);
            free(tmp->pixels);
            free(tmp);
            return NULL;
        }
    }

    return tmp;
}

void img_nega(image_t* img) {
    for(int i = 0; i < img->row; ++i)
        for(int j = 0; j < img->col; ++j)
            img->pixels[i][j] = img->max - img->pixels[i][j];
}

void img_rotate(image_t* img) {
    image_t *tmp = alloc_img(img);
    for(int i = 0; i < img->row; ++i)
        for(int j = 0; j < img->col; ++j)
            tmp->pixels[i][j] = img->pixels[j][i];

    for(int i = 0; i < img->row; ++i)
        for(int j = 0; j < img->col; ++j)
            img->pixels[i][img->col - 1 - j] = tmp->pixels[i][j];

    free_img(tmp);
}

void img_lim(image_t* img, float lim) {
    float max = img->max * lim;
    for(int i = 0; i < img->row; ++i)
        for(int j = 0; j < img->col; ++j)
            img->pixels[i][j] = (img->pixels[i][j] > max) ? img->max : 0;
}