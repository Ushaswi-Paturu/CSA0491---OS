#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void grep(const char *pattern, FILE *file) {
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    grep(pattern, file);

    fclose(file);

    return EXIT_SUCCESS;
}

