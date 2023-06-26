CC=clang
CFLAGS=-g -Wall
BINS=macro

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $^ -o $@

pre: 
	$(CC) $(CFLAGS) -E macro.c

clean: 
	$(RM) -r $(BINS) *.dSYM *.out