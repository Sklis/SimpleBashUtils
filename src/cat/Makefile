CC = gcc
LDFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
SOURCES = cat.c function.c catlib.h

s21_cat: $(SOURCES)

	${CC} ${LDFLAGS} -o $@ $(SOURCES)

clean: 
	rm -f s21_cat