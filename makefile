cc := clang
debug_opts := -Wall -g


priority_queue: priority_queue.c
	clang -Wall -g -c priority_queue.c -o priority_queue.o

test: priority_queue test.o
	clang -Wall -g test.o priority_queue.o -o test

test.o: test.c
	clang -Wall -g -c test.c -o test.o

clean:
	rm priority_queue.o test.o test
