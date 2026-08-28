#include <stdio.h>
#include <stdlib.h>
#include "AI.h"

char *read_line(FILE *file) {
    size_t capacity = 64;
    size_t length = 0;

    char *buffer = malloc(capacity);
    if (buffer == NULL)
        return NULL;

    int c;

    while ((c = fgetc(file)) != EOF) {

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;

            char *tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = tmp;
            capacity = new_capacity;
        }

        buffer[length++] = (char)c;
    }

    if (c == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';

    return buffer;
}

int write_in_file(char *file_name, char *text) {
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return -1;
    }
    fputs(text, fp);
    fclose(fp);
    return 0;
}

int read_file(char *file_name, char **text) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return -1;
    }

    *text = read_line(fp);

    fclose(fp);
    return 0;
}
