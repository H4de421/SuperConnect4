CXX=g++
CXXFLAGS= -Wall -Wextra -std=c++20 -Wold-style-cast -g
SRC= main.o Board_managment.o Automaton.o

all : $(addprefix src/,$(SRC))
	$(CXX) $(CPPFLAGS) -o SuperConect4 $^

clean :
	rm -f src/*.o
	rm -f SuperConect4