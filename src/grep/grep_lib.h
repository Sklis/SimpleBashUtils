#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char *file_name[4096];
  char string_reg[4096];
  int string_reg_count;
  int file_name_count;
} flags;

void parser(char **arguments, int count, flags *flag, regex_t *preg);
void f_flag(char *file_name, flags *flag);
void processing_and_output(flags *flag, char *file_name, int file_number,
                           regex_t *preg, regmatch_t *pmatch);
int check_file(char *name);
void chek_file_count(flags *flag, char *file_name);
