#define CATLIB_H

#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  bool flag_n;
  bool flag_b;
  bool flag_s;
  bool flag_v;
  bool flag_e;
  bool flag_t;
} allFlags;

void parsingFlag(int agrc, char *agrv[], allFlags *flags);
void mainPars(FILE *file, allFlags *flags, int *strCount, bool *newLine);
void print(int symbol, allFlags *flags);
void printNonPrint(unsigned int c);