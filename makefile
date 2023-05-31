CC=gcc
CFLAGS= -std=c17 -Wall -Werror
DEPS=lzw.h
OBJ=lzw.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) main main.o input/sort/*
