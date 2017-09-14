// Luiz Fernando Azevedo Vasconcellos
// lfav17@inf.ufpr.br

#include "vil_args.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int read_args (int nargs, char *args[], char **ipt, char **out) {
    for(int i=1; i < nargs - 1; ++i) {
        if(!strcmp(args[i], "-i")) {
            ++i;
            *ipt = malloc(strlen((args[i])+1) * sizeof(*ipt));
            if(!ipt) {
                fprintf(stderr, "Falha ao alocar memoria para argumento ipt\n");
                return -1;
            }
            strcpy(*ipt, args[i]);

        }
        else if (!strcmp(args[i], "-o")) {
            ++i;
            *out = malloc(strlen(args[i]+1) * sizeof(ipt));
            if(!out) {
                fprintf(stderr, "Falha ao alocar memoria para argumento out\n");
                return -1;
            }
            strcpy(*out, args[i]);
        }
        else {
            fprintf(stderr, "Argumento invalido: %s \n", args[i]);
            return -1;
        }
    }
    
    if(!ipt) {
        fprintf(stderr, "Argumento -i obrigatorio, com arquivo de entrada.\n");
        return -1;
    }
    if(!out) {
        fprintf(stderr, "Argumento -o obrigatorio, com arquivo de saida.\n");
        return -1;
    }

    return 0;
}

int read_args_numeric (int nargs, char *args[], char **ipt, char **out, float *lim) {
    int has_lim_opt = 0;

    for (int i=1; i < nargs - 1; ++i) {
        if (!strcmp(args[i], "-i")) {
            ++i;
            *ipt = malloc(strlen((args[i])+1) * sizeof(*ipt));
            if(!ipt) {
                fprintf(stderr,"Falha ao alocar memoria para argumento ipt\n");
                return -1;
            }
            strcpy(*ipt, args[i]);

        }
        else if (!strcmp(args[i], "-o")) {
            ++i;
            *out = malloc(strlen(args[i]+1) * sizeof(ipt));
            if(!out) {
                fprintf(stderr,"Falha ao alocar memoria para argumento out\n");
                return -1;
            }
            strcpy(*out, args[i]);
        }
        else if (!strcmp(args[i], "-l")) {
            has_lim_opt = 1;
            ++i;
            char tmp[10];
            strcpy(tmp, args[i]);
            *lim = atof(tmp);
        }
        else {
            fprintf(stderr, "Argumento invalido: %s \n", args[i]);
            return -1;
        }
    }

    if(!ipt) {
        fprintf(stderr, "Argumento -i obrigatorio, com arquivo de entrada.\n");
        return -1;
    }
    if(!out) {
        fprintf(stderr, "Argumento -o obrigatorio, com arquivo de saida.\n");
        return -1;
    }

    if(!has_lim_opt)
        *lim = 0.5;
    if(*lim < 0.0f) *lim = 0.0f;
    if(*lim > 1.0f) *lim = 1.0f;

    return 0;
}
