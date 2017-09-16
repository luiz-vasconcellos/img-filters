// Luiz Fernando Azevedo Vasconcellos
// lfav17@inf.ufpr.br

#include "vil_data.h"
#include "vil_args.h"
#include "vil_io.h"
#include "vil_filters.h"

#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *ipt = NULL, *out = NULL;
    read_args(argc, argv, &ipt, &out);

    image_t *img = read_file(ipt);
    img_median(img);
    write_file(out, img);

    free_img(img);
    free(ipt);
    free(out);

    return 0;
}
