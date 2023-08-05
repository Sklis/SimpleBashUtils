#include "grep_lib.h"

int main(int argc, char *argv[]) {
  flags flag = {.c = 0,
                .e = 0,
                .f = 0,
                .file_name = {'\0'},
                .file_name_count = 0,
                .h = 0,
                .i = 0,
                .l = 0,
                .n = 0,
                .o = 0,
                .s = 0,
                .string_reg = {'\0'},
                .string_reg_count = 0};
  regex_t preg;
  regmatch_t pmatch;

  parser(argv, argc, &flag, &preg);

  for (int i = 0; i < flag.file_name_count; i++) {
    if (check_file(flag.file_name[i])) {
      processing_and_output(&flag, flag.file_name[i], i, &preg, &pmatch);
    }
  }
  regfree(&preg);

  return 0;
}