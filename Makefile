CC=gcc
CFLAGS+=-m32 -Wall -g -O2 -W
AS=nasm
ASMFLAGS+=-g -f elf32

all: homework6_hse

homework6_hse: main.o f1.o f2.o f3.o f1_derivative.o f2_derivative.o f3_derivative.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) $^ -c -o $@

f1.o: f1.asm
	$(AS) $(ASMFLAGS) $^ -o $@

f2.o: f2.asm
	$(AS) $(ASMFLAGS) $^ -o $@

f3.o: f3.asm
	$(AS) $(ASMFLAGS) $^ -o $@

f1_derivative.o: f1_derivative.asm
	$(AS) $(ASMFLAGS) $^ -o $@

f2_derivative.o: f2_derivative.asm
	$(AS) $(ASMFLAGS) $^ -o $@

f3_derivative.o: f3_derivative.asm
	$(AS) $(ASMFLAGS) $^ -o $@

clean:
	rm -rf *.o homework6_hse