CC=gcc
CFLAGS+=-m32 -Wall -g -O2 -W
AS=nasm
ASMFLAGS+=-g -f elf32

all: homework6_hse

homework6_hse: test.o root_functions.o
	$(CC) $(CFLAGS) $^ -o $@

test.o: test.c
	$(CC) $(CFLAGS) $^ -c -o $@

root_functions.o: root_functions.asm
	$(AS) $(ASMFLAGS) $^ -o $@

clean:
	rm -rf *.o homework6_hse