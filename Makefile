CXX=g++
CXXFLAGS= -Wall -Wextra -std=c++20 -Wold-style-cast -g
SRC= main.o

all : $(addprefix src/,$(SRC))
	$(CXX) $(CPPFLAGS) -o cli_exec $^

clean :
	rm -f src/*.o
	rm -f cli_exec