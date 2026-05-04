CC = clang
CFLAGS = -Wall -Wextra -g -O2 -std=c17

main: main.c
	$(CC) $(CFLAGS) -o main main.c

run: main
	./main

clean:
	rm -f main

.PHONY: run clean
