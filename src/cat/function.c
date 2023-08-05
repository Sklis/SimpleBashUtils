#include "catlib.h"

void parsingFlag(int agrc, char *agrv[], allFlags *flags) {
  struct option longOptions[] = {{"number-nonblank", 0, NULL, 'b'},
                                 {"number", 0, NULL, 'n'},
                                 {"squeeze-blank", 0, NULL, 's'},
                                 {NULL, 0, NULL, 0}};

  int currFlag;
  while ((currFlag = getopt_long(agrc, agrv, "beEnstT", longOptions, NULL)) !=
         -1) {
    switch (currFlag) {
      case 'b':
        flags->flag_b = true;
        break;
      case 'e':
        flags->flag_e = true;
        flags->flag_v = true;
        break;
      case 'E':
        flags->flag_e = true;
        break;
      case 'n':
        flags->flag_n = true;
        break;
      case 's':
        flags->flag_s = true;
        break;
      case 't':
        flags->flag_t = true;
        flags->flag_v = true;
        break;
      case 'T':
        flags->flag_t = true;
        break;
    }
  }

  if (flags->flag_b == true && flags->flag_n == true) flags->flag_n = false;
}

void mainPars(FILE *file, allFlags *flags, int *strCount, bool *newLine) {
  size_t c = 0;
  int emptyLine = 0;

  while (fread(&c, 1, 1, file) > 0) {
    if (flags->flag_s) {
      if (c == '\n') {
        if (!(*newLine))
          emptyLine = 0;
        else
          emptyLine += 1;
        if (emptyLine > 1) continue;
      } else
        emptyLine = 0;
    }
    if (flags->flag_n && *newLine == true)
      printf("%6i\t", (*strCount)++);
    else if ((flags->flag_b && (*newLine) && c != '\n'))
      printf("%6i\t", (*strCount)++);

    print(c, flags);
    *newLine = (c == '\n') ? true : false;
  }
}

void print(int symbol, allFlags *flags) {
  if (symbol == '\n') {
    if (flags->flag_e)
      printf("$%c", symbol);
    else
      printf("%c", symbol);
  } else if (symbol == '\t') {
    if (flags->flag_t)
      printf("^I");
    else
      printf("%c", symbol);
  } else if (flags->flag_v)
    printNonPrint(symbol);
  else
    printf("%c", symbol);
}

void printNonPrint(unsigned int c) {
  if (c < 32)
    printf("^%c", c + 64);
  else if (c >= 32 && c < 127)
    printf("%c", c);
  else if (c == 127)
    printf("^%c", c - 64);
}
