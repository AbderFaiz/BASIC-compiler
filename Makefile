CC = g++
FLAGS = -Wall

test.out: src/main.cpp
	$(CC) $(FLAGS) $^ -o $@
	./$@

clean:
	rm -f test *.o