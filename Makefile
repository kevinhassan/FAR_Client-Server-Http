# Makefile

GCC=gcc
FILES=client.c
OBJ=$(FILES:%.c=%.o)
BIN=client

all: $(OBJ)
	$(GCC) -o client client.o

clean:
	rm -f *~ *.o $(BIN)

.SUFFIXES: .c .o

.zf.res:
	$(GCC) -c $<
