AS=nasm
ASMFLAGS+=-g -f elf32
CFLAGS ?= -O2 -g
CFLAGS += -std=gnu99
CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value
CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error
CC += -m32 -no-pie -fno-pie

.PHONY: all

all: integral

integral: integral.o f1.o f2.o f3.o f1_derivative.o f2_derivative.o f3_derivative.o
	$(CC) $(CFLAGS) $^ -o $@

integral.o: integral.c
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
	rm -rf *.o integral

test: integral
	echo "\nФункция root:\n"
	./integral --test-root 1:2:3.0:8.5:0.001:6.09616967415785
	./integral --test-root 1:3:2.01:2.5:0.001:2.19174342502218
	./integral --test-root 2:3:4.0:4.5:0.001:4.224744871391
	echo "\nФункция integral:\n"
	./integral --test-integral 1:2.19174342502218:6.09616967415785:0.00001:5.39552
	./integral --test-integral 2:4.224744871391:6.09616967415785:0.00001:6.885131770958632
	./integral --test-integral 3:2.19174342502218:4.224744871391:0.00001:9.74677