CC = g++
FLAGS = -Wall
EXAMPLE = examples/factorial

all: test.out

Token.o : src/Token.cpp src/Token.hpp
	$(CC) -c $(FLAGS) $< 

Lexer.o : src/Lexer.cpp src/Lexer.hpp
	$(CC) -c $(FLAGS) $< 

test.out: src/main.cpp Token.o Lexer.o
	$(CC) $(FLAGS) $^ -o $@
	./$@ $(EXAMPLE)

clean:
	rm -f test.out *.o