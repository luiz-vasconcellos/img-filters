// Luiz Fernando Azevedo Vasconcellos
// lfav17@inf.ufpr.br

#ifndef VIL_FILTERS_H
#define VIL_FILTERS_H

#include <vil_data.h>

void free_img(image_t *img);
image_t* alloc_img(image_t *img);

void img_nega(image_t *img);
void img_rotate(image_t *img);
void img_lim(image_t *img, float lim);
void img_median(image_t *img);

#endif 
