# Luiz Fernando Azevedo Vasconcellos
# lfav17@inf.ufpr.br

CC=gcc
CFLAGS=-Wall

all: nega rot lim median

nega: pgmnega.o vil_io.o vil_args.o vil_filters.o
	$(CC) pgmnega.o vil_io.o vil_args.o vil_filters.o $(CFLAGS) -o pgmnega

rot: pgmrotaciona.o vil_io.o vil_args.o vil_filters.o
	$(CC) pgmrotaciona.o  vil_io.o vil_args.o vil_filters.o $(CFLAGS) -o pgmrotacao

lim: pgmlimiar.o vil_io.o vil_args.o vil_filters.o
	$(CC) pgmlimiar.o  vil_io.o vil_args.o vil_filters.o $(CFLAGS) -o pgmlimiar

median: pgmmediana.o vil_io.o vil_args.o vil_filters.o
	$(CC) pgmmediana.o  vil_io.o vil_args.o vil_filters.o $(CFLGAS) -o pgmmediana

vil_io.o: vil_io.c vil_io.h 
	$(CC) -c vil_io.c  $(CFLAGS)

vil_args.o: vil_args.c vil_args.h 
	$(CC) -c vil_args.c  $(CFLAGS)

vil_filters.o: vil_filters.c vil_filters.h 
	$(CC) -c vil_filters.c  $(CFLAGS)

clean:
	-rm *.o
	-rm *.gch

purge: clean
	-rm pgmnega pgmrotacao pgmlimiar pgmmediana