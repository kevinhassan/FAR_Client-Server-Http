# Makefile

GCC=gcc
FILES=client.c server.c
OBJ=$(FILES:%.c=%.o)
BIN=client server

all: $(OBJ)
	$(GCC) -o client client.o
	$(GCC) -o server server.o

clean:
	rm -f *~ *.o $(BIN)

.SUFFIXES: .c .o

.zf.res:
	$(GCC) -c $<
