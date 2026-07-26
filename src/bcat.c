#include <stdio.h>
#include <string.h>

void log_err(char *msg) {
    printf("[ERROR]:    %s\n", msg);
}

int main(int argc, char *argv[]) {
    char buffer[1024];
    int read;
    FILE *fd;

    if (argc != 2) {
        printf("Invalid arg count. Usage: ./bcat <filename>\n");
        return 1;
    }

    fd = fopen(argv[1], "rt");
    do {
        memset(&buffer, 0, sizeof buffer);
        read = fread(&buffer, sizeof buffer, 1, fd);
        int err = fprintf(stdout, "%s\n", buffer);
        if (err < 0) {
            log_err("failed writing to output");
            break;
        }

    } while (read != 0);

    if (feof(stdin) == 0) {
        int err = ferror(fd);
        if (err != 0) {
            perror("fread");
        }
    }
    fclose(fd);

    return 0;
}
