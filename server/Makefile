CC=gcc
CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -Wvla
SRC= main.o

all : $(addprefix src/,$(SRC))
	$(CC) $(CFLAGS) -o ser_exec $^

clean :
	rm -f src/*.o
	rm -f ser_exec