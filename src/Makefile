CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
GCOVFLAGS:=-fprofile-arcs -ftest-coverage
LDFLAGS:=-lcheck -lgcov -fprofile-arcs --coverage
ifeq ($(shell uname), Linux)
LDFLAGS +=-lpthread -lrt -lm -lsubunit
endif

SRC:= $(wildcard s21_*.c)
OBJ = $(addprefix obj/,$(SRC:.c=.o))
OBJ_GCOV = $(addprefix gcov_obj/,$(SRC:.c=.o))
TEST_SRC:= $(wildcard tests/s21_*.c)
TEST_OBJ = $(addprefix tests/,$(TEST_SRC:.c=.o))

.PHONY: all clean test s21_decimal.a rebuild gcov_report

all: clean s21_decimal.a test

s21_decimal_gcov.a: $(OBJ_GCOV)
	ar -src $@ $(OBJ_GCOV) 

s21_decimal.a: $(OBJ)
	ar -src $@ $(OBJ) 

test: tests/s21_test_decimal.o s21_decimal_gcov.a
	$(CC) -g tests/s21_test_decimal.o s21_decimal_gcov.a -o $@ $(LDFLAGS) $(GCOVFLAGS)
	./test

gcov_report: test
	lcov -c -d gcov_obj/. -o gcov_obj/coverage.info
	genhtml gcov_obj/coverage.info --output-directory out
ifeq ($(shell uname), Linux)
	xdg-open out/index.html
else ifeq ($(shell uname), Darwin)
	open out/index.html
endif

gcov_obj/%.o: %.c
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rebuild: clean all

rebuild_gcov: clean test gcov_report s21_decimal_gcov.a

clean:
	rm -f */*.o
	rm -f gcov_obj/*.gc*
	rm -f ./test
	rm -f -r out
	rm -f gcov_obj/*.info
	rm -f .DS_Store
	rm -f *.a
	rm -rf test.dSYM
	rm -f tests/*.o
	rm -f ../.DS_Store
	
clang:
	clang-format -i *.c *.h tests/*.c

leaks: rebuild
	leaks -atExit -- ./test

valgrind:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes -s ./test
