#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

const int BUFFER_SIZE = 1024;

typedef struct {
  int count_chars;
  int count_words;
  int count_lines;
} Config;

Config parse_args(int argc, char *argv[]) {
  Config config;

  if (argc == 1) {
    config.count_chars = 1;
    config.count_words = 1;
    config.count_lines = 1;
    return config;
  }

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      continue;
    }

    for (int j = 1; argv[i][j] != '\0'; j++) {
      switch (argv[i][j]) {
      case 'c':
        config.count_chars = 1;
        break;
      case 'w':
        config.count_words = 1;
        break;
      case 'l':
        config.count_lines = 1;
        break;
      }
    }
  }

  return config;
}

int main(int argc, char *argv[]) {
  char buffer[BUFFER_SIZE];

  int count_chars = 0;
  int count_words = 0;
  int count_lines = 0;

  Config config = parse_args(argc, argv);

  int c;
  int in_word = 0;
  while ((c = getc(stdin)) != EOF) {
    count_chars++;

    if (c == '\n') {
      count_lines++;
    }

    if (isspace(c)) {
      in_word = 0;
    } else if (in_word == 0) {
      in_word = 1;
      count_words++;
    }
  }

  if (config.count_chars == 1) {
    printf("chars:\t%d\n", count_chars);
  }

  if (config.count_words == 1) {
    printf("words:\t%d\n", count_words);
  }

  if (config.count_lines == 1) {
    printf("lines:\t%d\n", count_lines);
  }

  return 0;
}
