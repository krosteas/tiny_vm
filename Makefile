CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g
CPPFLAGS =
LDFLAGS =
LDLIBS =

.PHONY: all clean

all: hexview disassembler

hexview: hexview.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

disassembler: disassembler.o isa.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

-include hexview.d disassembler.d isa.d

clean:
	rm -f hexview disassembler hexview.o disassembler.o isa.o hexview.d disassembler.d isa.d