#include "grep_lib.h"

void parser(char **arguments, int count, flags *flag, regex_t *preg) {
  /*
  функция записывает флаги и имена файлов
  */
  int value = 0;
  const char *short_flags = "e:ivclnhsof:";

  while (value != -1) {
    value = getopt_long(count, arguments, short_flags, NULL, NULL);
    switch (value) {
      case 'e':
        flag->e = 1;
        if (flag->string_reg_count) {
          strcat(flag->string_reg, (char[2]){'|', '\0'});
        }
        strcat(flag->string_reg, optarg);
        flag->string_reg_count += 1;
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'o':
        flag->o = 1;
        break;
      case 'f':
        flag->f = 1;
        f_flag(optarg, flag);
        break;
      default:
        break;
    }
  }
  if (!flag->e && !flag->f) {
    strcat(flag->string_reg, arguments[optind]);
    flag->string_reg_count += 1;
  }
  if (flag->e || flag->f) {
    for (int i = 0; i < count - optind; i++) {
      flag->file_name[i] = arguments[i + optind];
      flag->file_name_count += 1;
    }
  } else {
    for (int i = 0; i < count - 1 - optind; i++) {
      flag->file_name[i] = arguments[i + 1 + optind];
      flag->file_name_count += 1;
    }
  }
  int parameter = REG_EXTENDED;
  if (flag->i) {
    parameter = REG_EXTENDED | REG_ICASE;
  }
  regcomp(preg, flag->string_reg, parameter);
}

void f_flag(char *file_name, flags *flag) {
  /*
  функци обрабатывает флаг f (возращает строки из файла)
  */
  opterr = 0;
  FILE *file = NULL;
  if (check_file(file_name)) {
    file = fopen(file_name, "r");
    size_t len_buffer = 0;
    char *buffer = NULL;
    while (getline(&buffer, &len_buffer, file) != -1) {
      if (flag->string_reg_count) {
        strcat(flag->string_reg, (char[2]){'|', '\0'});
      }
      int len = strlen(buffer);
      if (buffer[len - 1] == '\n') {
        if (len <= 2)
          buffer[len - 1] = '.';
        else
          buffer[len - 1] = '\0';
      }
      strcat(flag->string_reg, buffer);

      flag->string_reg_count += 1;
    }
    free(buffer);
    fclose(file);
  } else {
    exit(2);
  }
}

void processing_and_output(flags *flag, char *file_name, int file_number,
                           regex_t *preg, regmatch_t *pmatch) {
  FILE *file = fopen(file_name, "r");
  char *string_buffer = NULL;
  size_t len_buffer = 0;
  int thrue_counter = 0;
  int number_line = 0;
  while (getline(&string_buffer, &len_buffer, file) != -1) {
    number_line++;
    if ((!regexec(preg, string_buffer, 1, pmatch, 0)) ^ (flag->v)) {
      thrue_counter++;
      /*
      проверка на флаг h
      */
      if (flag->file_name_count > 1 && !flag->h && !flag->c && !flag->l)
        printf("%s:", file_name);
      if (!flag->c && !flag->l) {
        /*
        проверка на флаг n
        */
        if (flag->n) printf("%d:", number_line);
        if (!flag->o || flag->v) {
          printf("%s", string_buffer);
          if (string_buffer[strlen(string_buffer) - 1] != '\n') printf("\n");
        } else {
          /*
          флаг o
          */
          char *o_string = string_buffer;
          for (; !regexec(preg, o_string, 1, pmatch, 0);
               o_string += pmatch->rm_eo) {
            printf("%.*s\n", (int)(pmatch->rm_eo - pmatch->rm_so),
                   o_string + pmatch->rm_so);
          }
        }
      }
    }
    memset(string_buffer, '\0', len_buffer);
  }
  if (flag->c) {
    if (!flag->l) {
      chek_file_count(flag, file_name);
      printf("%d", thrue_counter);
    } else {
      if (thrue_counter) {
        chek_file_count(flag, file_name);
        printf("1");
      } else {
        chek_file_count(flag, file_name);
        printf("0");
      }
    }
    printf("\n");
  }
  if (flag->l && thrue_counter) {
    printf("%s", file_name);
    if ((file_number < flag->file_name_count - 1) || flag->l) printf("\n");
  }
  free(string_buffer);
  fclose(file);
}

int check_file(char *name) {
  /*
  функция проверяет файл на существование
  */
  opterr = 0;
  struct stat file_stat;
  int result = 0;
  if (stat(name, &file_stat) == 0) {
    result = 1;
  } else {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", name);
  }
  return result;
}

void chek_file_count(flags *flag, char *file_name) {
  if (flag->file_name_count > 1 && !flag->h) printf("%s:", file_name);
}