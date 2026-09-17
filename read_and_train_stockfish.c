#include <stdio.h>
#include <string.h>
#include "AI.h"

int read_and_train_stockfish(layer_t *layer) {
    FILE* fp = fopen(DATASET_FILE_PATH, "r");
    char buffer[256];
    char* value = NULL;
    int column = 0;
    int i = 0;

    while (fgets(buffer, 256, fp) && i < 30) {
        value = strtok(buffer, ",");
        while (value) {
            if (column == 0) {
                printf("fen : ");
                printf("%s\n", value);
            } else if (column == 1) {
                printf("move 1 : ");
                printf("%s\n", value);
            } else if (column == 2) {
                printf("move 2 : ");
                printf("%s\n", value);
            } else if (column == 3) {
                printf("move 3 : ");
                printf("%s\n", value);
            } else if (column == 4) {
                printf("move 4 : ");
                printf("%s\n", value);
            } else if (column == 5) {
                printf("move 5 : ");
                printf("%s\n", value);
            } else if (column == 6) {
                printf("evaluation : ");
                printf("%s\n", value);
            }
            printf("\n");
            value = strtok(NULL, ",");
            column++;
        }
        column = 0;
        i++;
    }
    

    fclose(fp);
    return 0;
}
