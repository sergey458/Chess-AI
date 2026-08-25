#include <stdio.h>
#include "Chess-AI.h"

int write_in_file(char *json_str) {
    // write the JSON string to a file
    FILE *fp = fopen(AI_FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return 1;
    }
        //    printf("%s\n", json_str);
    fputs(json_str, fp);
    fclose(fp);
}
