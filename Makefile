CC=gcc
CFLAGS= -std=c11 -g #-Wall -Werror -Wextra
GCOVFLAGS=-fprofile-arcs -ftest-coverage
LFLAGS=-lgcov --coverage
CHECKFLAGS=$(shell pkg-config --libs check) #-lcheck -lm -lpthread -lrt -lsubunit
SRC=s21_string.c s21_string_test.c
OBJ=s21_string.o s21_string_test.o
LIB=s21_string.a
OBJ_TARG=s21_string_test 
TARGET=/

.PHONY: help all clean test s21_string.a gcov_report

help:
	@echo "Available targets:"
	@echo "  make test"
	@echo "  make s21_string.a"
	@echo "  make gcov_report"

clean:
	rm -rf s21_string_test test *.gcda *.gcno *.a *.o *.json coverage.* *.info ./report/
all:	build

build: s21_string
	
rebuild: clean build

s21_string.a: s21_string.c s21_string.h  s21_sprintf.o
	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o
	ar -rc libs21_string.a s21_string.o s21_sprintf.o
	ranlib libs21_string.a

s21_sprintf.o: s21_sprintf.c  s21_sprintf.h
	$(CC) $(CFLAGS) -c s21_sprintf.c -o s21_sprintf.o

s21_string_test.o:	s21_string_test.check
	checkmk ./s21_string_test.check >s21_string_test.c
	$(CC) $(CFLAGS) -c s21_string_test.c -o s21_string_test.o

test:	s21_string_test.o s21_string.a
	$(CC) $(CFLAGS) -o s21_string_test s21_string_test.o -L. -ls21_string $(CHECKFLAGS)
#	leaks -atExit -- ./s21_string_test
#	valgrind --tool=memcheck --track-origins=yes --leak-check=yes ./s21_string_test
	./s21_string_test

gcov_lib:	s21_string.c s21_string.h
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(LFLAGS) -c s21_string.c -o s21_string.o
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(LFLAGS) -c s21_sprintf.c -o s21_sprintf.o
	ar -rc libs21_string.a s21_string.o s21_sprintf.o
	ranlib libs21_string.a

gcov_test:	s21_string_test.check gcov_lib
#	checkmk ./s21_string_test.check >s21_string_test.c
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c s21_string_test.c -o s21_string_test.o
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(LFLAGS) s21_string_test.o -L./ -ls21_string $(CHECKFLAGS) -o s21_string_test


gcov_report:	clean gcov_lib gcov_test
	./s21_string_test
	valgrind --tool=memcheck --leak-check=yes ./s21_string_test
#	lcov -t "s21_string_test" -o s21_string_test.info -c -d .
#	genhtml -o report s21_string_test.info
	gcovr --html-details coverage.html
