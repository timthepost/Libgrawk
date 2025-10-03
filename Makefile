# Makefile for libgrawk + CLI

CC ?= gcc
CFLAGS := -std=c11 -Wall -Wextra -O2 -fPIC
LDFLAGS :=

all: libgrawk.so libgrawk_tests grawk ngrawk

libgrawk.so: libgrawk.o
	$(CC) -shared -Wl,-soname,libgrawk.so -o $@ $^

libgrawk.o: libgrawk.c grawk.h
	$(CC) $(CFLAGS) -c libgrawk.c -o $@

ngrawk: grawk_main.c libgrawk.o
	$(CC) $(CFLAGS) -o $@ grawk_main.c libgrawk.o $(LDFLAGS)

# Older (v1 version) of grawk (does not link against libgrawk)
grawk: grawk.c
	$(CC) $(CFLAGS) -o $@ grawk.c

libgrawk_tests: libgrawk_tests.c libgrawk.o
	$(CC) $(CFLAGS) -o $@ libgrawk_tests.c libgrawk.o $(LDFLAGS)

.PHONY: tests
tests:
	$(SH) ./libgrawk_tests || false
	$(SH) ./grawk_tests.sh || false
	@echo "Tests complete."

.PHONY: clean
clean:
	rm -f *.o *.so grawk ngrawk libgrawk_tests

.PHONY: distclean
distclean: clean
	@echo "Distclean complete."
