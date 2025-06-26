CC = g++
FLAGS = -Wall
EXAMPLE = examples/factorial

all: test.out

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

test.out: src/main.cpp Token.o Lexer.o Parser.o Symbol.o Emitter.o
	$(CC) $(FLAGS) $^ -o $@
	./$@ $(EXAMPLE)
	cat out.c

test: test.out
	./$^ $(EXAMPLE)
	cat out.c

clean:
	rm -f test.out *.o