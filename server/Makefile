CC=gcc
CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla
SRC= main.c

all : #$(addprefix src/,$(ALL))
	$(CC) $(CFLAGS) -o server src/main.c

clean :
	rm -f *.o
	rm -f server