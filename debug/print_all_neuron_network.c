#include <stdlib.h>
#include <stdio.h>
#include "../AI.h"

int print_all_neuron_network(int inputs[INPUT_SIZE], layer_t *layer) {
    int k = 0;
    int j = 0;

    print_array_of_ints(inputs, INPUT_SIZE);
    printf("\n");
    while (layer != NULL) {
        j = 0;
        for (int i = 0; i < layer->neurons_number; i++) {
            for (; j < layer->weights_number; j++) {
                printf("%.6f ", layer->weights[j]);
            }
            printf("\nbias%i%i : %.6f\n", k, i, layer->neurons[i]);
            printf("neuron%i%i : %.6f\n", k, i, layer->neurons[i]);
        }
        printf("\n\n");
        layer = layer->next;
        k++;
    }
}
