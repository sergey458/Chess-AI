#include "cJSON/cJSON.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "AI.h"

float generate_random_small_weight() {
    float weight = 0.0f;

    weight = (((float)rand() / RAND_MAX) * 2 - 1) * INITIAL_WEIGHT_VALUE_LIMIT;
    return weight;
}

int initialize_layers(cJSON *json) {
    int size_of_layers[NUMBER_OF_LAYERS] = SIZE_OF_LAYERS;
    char weights_name[64] = WEIGHTS_NAME_IN_JSON;
    char weights_gradients_name[64] = WEIGHTS_GRADIENTS_NAME_IN_JSON;
    char biases_name[64] = BIASES_NAME_IN_JSON;
    char biases_gradients_name[64] = BIASES_GRADIENTS_NAME_IN_JSON;
    char number[16];

    for (int i = 0; i < NUMBER_OF_LAYERS; i++) {
        cJSON *weights = cJSON_CreateArray();
        cJSON *weights_gradients = cJSON_CreateArray();
        cJSON *biases = cJSON_CreateArray();
        cJSON *biases_gradients = cJSON_CreateArray();
        for (int j = 0; j < size_of_layers[i]; j++) {
            cJSON_AddItemToArray(weights, cJSON_CreateNumber(INITIAL_WEIGHTS_VALUE));
            cJSON_AddItemToArray(weights_gradients, cJSON_CreateNumber(INITIAL_WEIGHTS_GRADIENTS_VALUE));
            cJSON_AddItemToArray(biases, cJSON_CreateNumber(INITIAL_BIASES_VALUE));
            cJSON_AddItemToArray(biases_gradients, cJSON_CreateNumber(INITIAL_BIASES_GRADIENTS_VALUE));
        }
        snprintf(number, sizeof(number), "%d", i);
        cJSON_AddItemToObject(json, strcat(weights_name, number), weights);
        cJSON_AddItemToObject(json, strcat(weights_gradients_name, number), weights_gradients);
        cJSON_AddItemToObject(json, strcat(biases_name, number), biases);
        cJSON_AddItemToObject(json, strcat(biases_gradients_name, number), biases_gradients);
        strcpy(weights_name, WEIGHTS_NAME_IN_JSON);
        strcpy(weights_gradients_name, WEIGHTS_GRADIENTS_NAME_IN_JSON);
        strcpy(biases_name, BIASES_NAME_IN_JSON);
        strcpy(biases_gradients_name, BIASES_GRADIENTS_NAME_IN_JSON);
    }
}

int create_ai_json() {
    // create a cJSON object
    cJSON *json = cJSON_CreateObject();

    srand(time(NULL));
    initialize_layers(json);

    // convert the cJSON object to a JSON string
    char *json_str = cJSON_Print(json);

    write_in_file(AI_FILE_NAME, json_str);

    // free the JSON string and cJSON object
    cJSON_free(json_str);
    cJSON_Delete(json);
    return 0;
}
