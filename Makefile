nega:
	gcc -Wall pgmnega.c vil_data.h vil_io.c vil_args.c vil_filters.c -o pgmnega

rot:
	gcc -Wall pgmrotaciona.c vil_data.h vil_io.c vil_args.c vil_filters.c -o pgmrotacao

lim:
	gcc -Wall pgmlimiar.c vil_data.h vil_io.c vil_args.c vil_filters.c -o pgmlimiar

teste:	
	gcc -Wall teste.c vil_data.h vil_io.c vil_args.c
