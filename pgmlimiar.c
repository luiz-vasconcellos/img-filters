// Luiz Fernando Azevedo Vasconcellos
// lfav17@inf.ufpr.br

#include <vil_data.h>
#include <vil_args.h>
#include <vil_io.h>
#include <vil_filters.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *ipt = NULL, *out = NULL;
    float lim = 0;
    read_args_numeric(argc, argv, &ipt, &out, &lim);

    image_t *img = read_file(ipt);
    img_lim(img, lim);
    write_file(out, img);

    free_img(img);
    free(ipt);
    free(out);

    return 0;
}
