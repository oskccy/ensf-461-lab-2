# ensf 461 lab 02 - exercise 01
# oscar (30242380), somrit (30230926)

# compiler used throughout the makefile
CC = gcc

OS := $(shell uname -s)
TARGETS = gen_numbers.out select_arg.out gen_in_range.out

.PHONY: all
ifeq ($(OS),Linux)
all: $(TARGETS)
else
all:
	@echo "Sorry, I prefer Linux"
endif

# programs that depend on the random number utilities
gen_numbers.out select_arg.out: %.out: %.c utils.c utils.h
	$(CC) -o $@ $(filter %.c,$^)

gen_in_range.out: %.out: %.c
	$(CC) -o $@ $<

# builds every executable, runs it with valid arguments and fails if any exit code is not 0
.PHONY: test
test: $(TARGETS)
	./gen_numbers.out 5 || (echo "test failed: gen_numbers.out"; exit 1)
	./select_arg.out apple banana cherry || (echo "test failed: select_arg.out"; exit 1)
	./gen_in_range.out 10 20 || (echo "test failed: gen_in_range.out"; exit 1)
	@echo "all tests passed"

.PHONY: clean
clean:
	rm -f *.out
