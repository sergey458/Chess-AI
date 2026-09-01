#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "AI.h"

int free_layer(layer_t *layer) {
    layer_t *prev_layer = NULL;

    while (layer != NULL) {
        free(layer->weights);
        free(layer->weights_gradients);
        free(layer->biases);
        free(layer->biases_gradients);
        prev_layer = layer;
        layer = layer->next;
        free(prev_layer);
    }
    return 0;
}

int print_layers(layer_t *layer) {
    layer_t *prev_layer = NULL;

    while (layer != NULL) {
        printf("\n\nweights :\n");
        print_array_of_floats(layer->weights, layer->weights_number);
        printf("\n\nweights_gradients :\n");
        print_array_of_floats(layer->weights_gradients, layer->weights_gradients_number);
        printf("\n\nbiases :\n");
        print_array_of_floats(layer->biases, layer->biases_number);
        printf("\n\nbiases_gradients :\n");
        print_array_of_floats(layer->biases_gradients, layer->biases_gradients_number);
        prev_layer = layer;
        layer = layer->next;
    }
    return 0;
}

int main() {
    layer_t *layer = NULL;
    // layer_t *layer = malloc(sizeof(layer_t));
    // layer->next = NULL;
    char *text = NULL;

    if (access(AI_FILE_NAME, R_OK) == -1) {
        create_ai_json();
    }
    read_file(AI_FILE_NAME, &text);
    layer = convert_text_to_struct(text, layer);
    print_layers(layer);

    free(layer);
    free(text);
    return 0;
}
