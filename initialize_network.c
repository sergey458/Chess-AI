#include "cJSON/cJSON.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "Chess-AI.h"

float generate_random_small_weight() {
    float weight = 0.0f;

    weight = (((float)rand() / RAND_MAX) * 2 - 1) * INITIAL_WEIGHT_VALUE_LIMIT;
    printf("%.4f ", weight);
    return weight;
}

int initialize_layers(cJSON *json) {
    int size_of_layers[NUMBER_OF_LAYERS] = SIZE_OF_LAYERS;
    char weights_name[64] = "weights";
    char weights_gradients_name[64] = "weights_gradients";
    char biases_name[64] = "biases";
    char biases_gradients_name[64] = "biases_gradients";
    char number[16];

    for (int i = 0; i < NUMBER_OF_LAYERS; i++) {
        cJSON *weights = cJSON_CreateArray();
        cJSON *weights_gradients = cJSON_CreateArray();
        cJSON *biases = cJSON_CreateArray();
        cJSON *biases_gradients = cJSON_CreateArray();
        for (int j = 0; j < size_of_layers[i]; j++) {
            cJSON_AddItemToArray(weights, cJSON_CreateNumber(generate_random_small_weight()));
            cJSON_AddItemToArray(weights_gradients, cJSON_CreateNumber(0.0f));
            cJSON_AddItemToArray(biases, cJSON_CreateNumber(0.0f));
            cJSON_AddItemToArray(biases_gradients, cJSON_CreateNumber(0.0f));
        }
        snprintf(number, sizeof(number), "%d", i);
        cJSON_AddItemToObject(json, strcat(weights_name, number), weights);
        cJSON_AddItemToObject(json, strcat(weights_gradients_name, number), weights_gradients);
        cJSON_AddItemToObject(json, strcat(biases_name, number), biases);
        cJSON_AddItemToObject(json, strcat(biases_gradients_name, number), biases_gradients);
        strcpy(weights_name, "weights");
        strcpy(weights_gradients_name, "weights_gradients");
        strcpy(biases_name, "biases");
        strcpy(biases_gradients_name, "biases_gradients");
    }
}

int initialize_network() {
    // create a cJSON object
    cJSON *json = cJSON_CreateObject();
    //    cJSON_AddStringToObject(json, "layer1", "John Doe");
    //    cJSON_AddNumberToObject(json, "age", 30);
    //    cJSON_AddStringToObject(json, "email", "john.doe@example.com");

    srand(time(NULL));
    initialize_layers(json);

    // convert the cJSON object to a JSON string
    char *json_str = cJSON_Print(json);

    write_in_file(json_str);


    // free the JSON string and cJSON object
    cJSON_free(json_str);
    cJSON_Delete(json);
    return 0;
}
