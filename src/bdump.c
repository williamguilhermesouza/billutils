#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("%s\n", "wrong arg count");
    return 1;
  }

  char *filename = argv[1];
  FILE *file = fopen(filename, "rb");
  char buffer[100];
  memset(buffer, 0, 100);
  int byte_count;

  while ((byte_count = fread(buffer, sizeof(char), 100, file)) != 0) {
    for (int i = 0; i < byte_count; i++) {
      printf("%02x ", buffer[i]);
    }
    printf("\n");
    memset(buffer, 0, 100);
  }

  fclose(file);
}
