#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "AI.h"

float relu(float neuron) {
    if (neuron > 0.0f) {
        return neuron;
    } else {
        return 0.0f;
    }
}

float my_tanh(float neuron) {
    return tanhf(neuron);
}

int calculate_new_neurons_values(int inputs[INPUT_SIZE], layer_t *layer, int expected) {
    int k = 0;
    layer_t *prev_layer;

    for (int i = 0; i < layer->neurons_number; i++) {
        for (int j = 0; j < INPUT_SIZE; j++) {
            layer->neurons[i] = layer->neurons[i] + (inputs[j] * layer->weights[k]);
            k++;
        }
        layer->neurons[i] = layer->neurons[i] + layer->biases[i];
        layer->neurons[i] = relu(layer->neurons[i]);
    }
    k = 0;
    while (layer->next != NULL) {
        prev_layer = layer;
        layer = layer->next;

        for (int i = 0; i < layer->neurons_number; i++) {
            for (int j = 0; j < prev_layer->neurons_number; j++) {
                layer->neurons[i] = layer->neurons[i] + (prev_layer->neurons[j] * layer->weights[k]);
            }
            layer->neurons[i] = layer->neurons[i] + layer->biases[i];
            layer->neurons[i] = relu(layer->neurons[i]);
        }
        k = 0;
    }
    layer->neurons[0] = my_tanh(layer->neurons[0]);
}

int read_and_train_stockfish(layer_t *layer) {
    FILE* fp = fopen(DATASET_FILE_PATH, "r");
    int inputs[INPUT_SIZE] = {0, 1};
    char buffer[256];
    char *value = NULL;
    int column = 0;
    int i = 0;
    float expected = 0.0f;

    while (fgets(buffer, 256, fp) && i < 2) {
        if (i == 0) {
            i++;
            continue;
        }
        value = strtok(buffer, ",");
        while (value) {
            if (column == 0) {
                // convert_fen_to_binary(value, inputs);
            } else if (column == 1) {
            } else if (column == 2) {
            } else if (column == 3) {
            } else if (column == 4) {
            } else if (column == 5) {
            } else if (column == 6 && !strchr(value, 'M')) {
                expected = atoi(value);
                if (expected >= 0) {
                    expected = expected / MAX_DATASET_EVALUATION;
                } else {
                    expected = -expected / MIN_DATASET_EVALUATION;
                }
                print_all_neuron_network(inputs, layer);
                calculate_new_neurons_values(inputs, layer, expected);
                printf("#######################################\n");
                print_all_neuron_network(inputs, layer);
            }
            value = strtok(NULL, ",");
            column++;
        }

        column = 0;
        i++;
    }
    // print_array_of_ints(inputs, INPUT_SIZE);
    fclose(fp);
    return 0;
}
