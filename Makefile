CC = g++
FLAGS = -Wall
EXAMPLE = examples/factorial

all: test.out

Token.o : src/Token.cpp src/Token.hpp
	$(CC) -c $(FLAGS) $< 

Lexer.o : src/Lexer.cpp src/Lexer.hpp Token.o
	$(CC) -c $(FLAGS) $< 

Parser.o : src/Parser.cpp src/Parser.hpp Lexer.o Token.o
	$(CC) -c $(FLAGS) $< 

test.out: src/main.cpp Token.o Lexer.o Parser.o
	$(CC) $(FLAGS) $^ -o $@
	./$@ $(EXAMPLE)

clean:
	rm -f test.out *.o