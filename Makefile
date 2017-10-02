# Luiz Fernando Azevedo Vasconcellos
# lfav17@inf.ufpr.br

CC = gcc
CFLAGS = -Wall

INCLUDEDIR = ./include
INCL = -I$(INCLUDEDIR)
SRCDIR = ./src

OBJS = vil_io.o vil_args.o vil_filters.o
FILTERS = pgmnega pgmrotacao pgmlimiar pgmmediana

all: $(FILTERS)

$(FILTERS): $(addsuffix .c, $(FILTERS)) $(OBJS)
	$(CC) $(CFLAGS) $(INCL) $< $(OBJS) -o bin/$@

%.o : $(SRCDIR)/%.c $(INCLUDEDIR)/vil_data.h
	$(CC) $(INCL) $(CFLAGS) -c $<

clean:
	rm -f *.o *.gch

purge: clean
	-rm -f bin/* pgmnega pgmrotacao pgmlimiar pgmmediana