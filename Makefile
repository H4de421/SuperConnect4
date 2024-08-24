CXX=g++
CXXFLAGS= -Wall -Wextra -std=c++20 -Wold-style-cast -g
SRC= main.o Board_managment.o Automaton.o Stratagems.o
DEB= main_DEBUG.o Board_managment.o Automaton.o Stratagems.o

all : $(addprefix src/,$(SRC))
	$(CXX) $(CPPFLAGS) -o SuperConect4 $^
	
debug : $(addprefix src/,$(DEB))
	$(CXX) $(CPPFLAGS) -o debug $^

clean :
	rm -f src/*.o
	rm -f SuperConect4