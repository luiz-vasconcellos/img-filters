// Luiz Fernando Azevedo Vasconcellos
// lfav17@inf.ufpr.br

#include "vil_filters.h"
#include "vil_data.h"
#include <stdlib.h>
#include <stdio.h>

int get_median(int x, int y, image_t *img);

void free_img(image_t *img) {
    // Free each row of the image
    for(int i = 0; i < img->row; ++i)
        free(img->pixels[i]);
    // Free array of rows and the struct itself
    free(img->pixels);
    free(img);
}

image_t* alloc_img(image_t *img) {
    image_t *tmp = calloc(1, sizeof(*tmp));
    
    // Copy the "header" info
    tmp->format = img->format;
    tmp->max = img->max;
    tmp->row = img->row;
    tmp->col = img->col;

    // Allocate array of rows and free in case of errors
    tmp->pixels = calloc(tmp->row, sizeof(*tmp->pixels));
    if(!tmp->pixels) {
        free(tmp);
        return NULL;
    }

    // Allocate rows and free everything in case of errors
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
    //Just calculate the complement for every pixel
    for(int i = 0; i < img->row; ++i)
        for(int j = 0; j < img->col; ++j)
            img->pixels[i][j] = img->max - img->pixels[i][j];
}

void img_rotate(image_t* img) {
    // 90 degress clockwise is the same as 270 anti-clockwise
    // Copy the image with 90 a.c rotation
    image_t *tmp = alloc_img(img);
    for(int i = 0; i < img->row; ++i)
        for(int j = 0; j < img->col; ++j)
            tmp->pixels[i][j] = img->pixels[j][i];

    // Rotate more 180 a.c degrees
    for(int i = 0; i < img->row; ++i)
        for(int j = 0; j < img->col; ++j)
            img->pixels[i][img->col - 1 - j] = tmp->pixels[i][j];

    free_img(tmp);
}

void img_lim(image_t* img, float lim) {
    // Just calculate the limiar and apply it to each pixel
    float max = img->max * lim;
    for(int i = 0; i < img->row; ++i)
        for(int j = 0; j < img->col; ++j)
            img->pixels[i][j] = (img->pixels[i][j] > max) ? img->max : 0;
}

int get_median(int x, int y, image_t *img) {
    // Gather the valid neighbours for the x,y position
    int numbers[9] = {0}, sz = 0;
    for(int i=-1; i<2; ++i)
        for(int j=-1; j<2; ++j)
            if( (x+i >= 0) && (x+i < img->row) && (x+j >= 0) && (x+j < img->col))
                numbers[sz++] = img->pixels[x+i][y+j];

    // Sort them
    for(int i=0; i<sz;++i)
        for(int j=i; j<sz;++j) 
            if(numbers[i] > numbers[j]) {
                int tmp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = tmp;
            }

    // And return the median
    return numbers[sz/2];
}

void img_median(image_t *img) {
    // Just calculate the median for each pixel
    for(int i = 0; i < img->row; ++i)
        for(int j = 0; j < img->col; ++j)
            img->pixels[i][j] = get_median(i, j, img);
}