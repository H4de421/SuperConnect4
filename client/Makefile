CC=gcc
CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla
SRC= main.c

all : #$(addprefix src/,$(ALL))
	$(CC) $(CFLAGS) -o client src/main.c

clean :
	rm -f *.o
	rm -f client