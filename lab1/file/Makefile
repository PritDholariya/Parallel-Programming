# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2

# Thread flag
PTHREAD = -pthread

# Targets
all: p1 p3

# Sequential version
p1: p1.c
	$(CC) $(CFLAGS) p1.c -o p1

# Parallel version
p3: p3.c
	$(CC) $(CFLAGS) $(PTHREAD) p3.c -o p3

# Run examples
run_seq:
	./p1 1000000

run_par:
	./p3 1000000 4

# Clean build files
clean:
	rm -f p1 p3