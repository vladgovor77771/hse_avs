TARGET = app
ASM = nasm
ASMFLAGS = -f elf64
CC = gcc

all: $(TARGET)
clean:
	rm -f bin/*.*
	
$(TARGET): asmproc.o
	$(CC) -o bin/$(TARGET) src/main.c bin/asmproc.o

asmproc.o:
	$(ASM) $(ASMFLAGS) -o bin/asmproc.o src/asmproc.asm

benchmark: asmproc.o
	$(CC) -o bin/benchmark src/benchmark.c bin/asmproc.o