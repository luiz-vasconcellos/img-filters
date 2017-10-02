# Luiz Fernando Azevedo Vasconcellos
# lfav17@inf.ufpr.br

CC = gcc
CFLAGS = -Wall

OBJS = vil_io.o vil_args.o vil_filters.o
FILTERS = pgmnega pgmrotacao pgmlimiar pgmmediana

all: $(FILTERS)

$(FILTERS): $(addsuffix .o, $(FILTERS)) $(OBJS)
	$(CC) $< $(OBJS) $(CFLAGS) -o bin/$@

%.o : %.c vil_data.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o *.gch

purge: clean
	-rm -f bin/* pgmnega pgmrotacao pgmlimiar pgmmediana