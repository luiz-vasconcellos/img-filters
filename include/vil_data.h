#ifndef VIL_DATA_H
#define VIL_DATA_H

typedef enum pgm_format { PGMDC, PGM2, PGM5 } pgm_format;

typedef struct image_t {
    pgm_format format;
    int col;
    int row;
    int max;
    int **pixels;
} image_t;

#endif
