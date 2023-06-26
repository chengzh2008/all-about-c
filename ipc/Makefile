CC=clang
CFLAGS=-g -Wall
OBJS=shared_memory.o
EXE=write_shmem.out read_shmem.out destroy_shmem.out read_message_queue.out write_message_queue.out

all: $(EXE)

%.out: %.o $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean: 
	rm -rf *.dSYM *.o *.out $(EXE)