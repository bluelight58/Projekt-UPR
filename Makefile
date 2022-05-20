CC = gcc
CFLAGS += -lm -g -fsanitize=address

PROGRAM = main

$(PROGRAM): $(PROGRAM).c
	$(CC) $(PROGRAM).c -o $(PROGRAM) $(CFLAGS)