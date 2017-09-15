run:
	gcc -Wall teste.c vil_data.h vil_io.c vil_args.c
	./a.out -i t.pgm -o saida.pgm
