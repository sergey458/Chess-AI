#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "AI.h"

int main() {
    layer_t *layer;
    char *text = NULL;

    if (access(AI_FILE_NAME, R_OK) == -1) {
        create_ai_json();
    }
    read_file(AI_FILE_NAME, &text);
    read_ai_json(layer);
    //printf("%s\n", text);

    free(text);
    return 0;
}
