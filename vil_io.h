// Luiz Fernando Azevedo Vasconcellos
// lfav17@inf.ufpr.br

#ifndef VIL_IO_H
#define VIL_IO_H

#include "vil_data.h"

int read_file (char *file_name, image_t *img);
int write_file(char *file_name, image_t *img);

#endif 
