CC = gcc
CFLAGS = -Wall -g

build: main

main: main.o operations.o aux_functions.o commands.o
	$(CC) -o main $^ 

main.o: main.c
	$(CC) $(CFLAGS) -c $^

operations.o: operations.c
	$(CC) $(CFLAGS) -c $^

aux_functions.o: aux_functions.c
	$(CC) $(CFLAGS) -c $^

commands.o: commands.c
	$(CC) $(CFLAGS) -c $^

run: build
	./main

clean:
	rm -f *.o main