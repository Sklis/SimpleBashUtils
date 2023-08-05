#include "catlib.h"

int main(int argc, char *argv[]) {
  int strCount = 1;
  bool newLine = true;
  allFlags flags = {false, false, false, false, false, false};
  parsingFlag(argc, argv, &flags);

  for (char **filename = &argv[1], **end = &argv[argc]; filename != end;
       filename++) {
    if (**filename == '-') continue;
    FILE *file = fopen(*filename, "r");

    if (errno) {
      fprintf(stderr, "%s: ", argv[0]);
      perror(*filename);
      continue;
    }
    mainPars(file, &flags, &strCount, &newLine);
    fclose(file);
  }

  return 0;
}