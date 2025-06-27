CC = g++
FLAGS = -Wall

all: basic_compiler

Token.o : src/Token.cpp src/Token.hpp
	$(CC) -c $(FLAGS) $< 

Symbol.o : src/Symbol.cpp src/Symbol.hpp
	$(CC) -c $(FLAGS) $< 

Emitter.o : src/Emitter.cpp src/Emitter.hpp
	$(CC) -c $(FLAGS) $< 

Lexer.o : src/Lexer.cpp src/Lexer.hpp Token.o
	$(CC) -c $(FLAGS) $< 

Parser.o : src/Parser.cpp src/Parser.hpp Lexer.o Token.o Symbol.o Emitter.o
	$(CC) -c $(FLAGS) $< 

basic_compiler: src/main.cpp Token.o Lexer.o Parser.o Symbol.o Emitter.o
	$(CC) $(FLAGS) $^ -o $@
	
clean:
	rm -f *.o *.out *.c basic_compiler