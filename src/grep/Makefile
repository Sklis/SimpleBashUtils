FLAGS = gcc -Wall -Werror -Wextra -std=c11

all: s21_grep

s21_grep: s21_grep.c grep_fun.c grep_lib.h
	$(FLAGS) s21_grep.c grep_fun.c -o s21_grep


clean:
	rm -fr s21_grep s21_grep.log grep.log
	rm -fr *.o

clang:
	clang-format -i -style Google *.c *.h