#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cJSON/cJSON.h"
#include "AI.h"

int convert_json_to_array(int arraySize, cJSON *JSONarray, layer_t *layer, ArrayType_t ArrayType) {
    cJSON *itemFloat = NULL;
    float f;

    for (int i = 0; i < arraySize; i++) {
        itemFloat = cJSON_GetArrayItem(JSONarray, i);
        f = itemFloat->valuedouble;
        if (ArrayType == WEIGHTS) {
            layer->weights[i] = f;
            // printf("%.6f, ", f);
        } else if (WEIGHTS_GRADIENTS) {
            layer->weights_gradients[i] = f;
            // printf("%.6f, ", f);
        } else if (BIASES) {
            layer->biases[i] = f;
            // printf("%.6f, ", f);
        } else if (BIASES_GRADIENTS) {
            layer->biases_gradients[i] = f;
            // printf("%.6f, ", f);
        }
    }
    // printf("\n\n");
    return 0;
}

layer_t *convert_text_to_struct(char *text, layer_t *layer) {
    cJSON *json = cJSON_Parse(text);
    cJSON *weightsJSON;
    cJSON *weights_gradientsJSON;
    cJSON *biasesJSON;
    cJSON *biases_gradientsJSON;
    char weights_name[64] = WEIGHTS_NAME_IN_JSON;
    char weights_gradients_name[64] = WEIGHTS_GRADIENTS_NAME_IN_JSON;
    char biases_name[64] = BIASES_NAME_IN_JSON;
    char biases_gradients_name[64] = BIASES_GRADIENTS_NAME_IN_JSON;
    char number[16] = "0";
    layer_t *prev = NULL;

    while (1) {
        // printf("%s\n", strcat(weights_name, number));
        // printf("%s\n", strcat(weights_gradients_name, number));
        // printf("%s\n", strcat(biases_name, number));
        // printf("%s\n", strcat(biases_gradients_name, number));
        // printf("%s\n", number);
        weightsJSON = cJSON_GetObjectItem(json, strcat(weights_name, number));
        weights_gradientsJSON = cJSON_GetObjectItem(json, strcat(weights_gradients_name, number));
        biasesJSON = cJSON_GetObjectItem(json, strcat(biases_name, number));
        biases_gradientsJSON = cJSON_GetObjectItem(json, strcat(biases_gradients_name, number));
        if (!cJSON_IsArray(weightsJSON) || !cJSON_IsArray(weights_gradientsJSON) || !cJSON_IsArray(biasesJSON) || !cJSON_IsArray(biases_gradientsJSON)) {
            break;
        }

        layer = malloc(sizeof(layer_t));
        layer->next = prev;
        prev = layer;
        int weightsSize = cJSON_GetArraySize(weightsJSON);
        int weights_gradientsSize = cJSON_GetArraySize(weights_gradientsJSON);
        int biasesSize = cJSON_GetArraySize(biasesJSON);
        int biases_gradientsSize = cJSON_GetArraySize(biases_gradientsJSON);
        // printf("weightsSize : %i\n", weightsSize);
        // printf("weights_gradientsSize : %i\n", weights_gradientsSize);
        // printf("biasesSize : %i\n", biasesSize);
        // printf("biases_gradientsSize : %i\n", biases_gradientsSize);

        // printf("weights : %s\n", weightsJSON);
        // printf("weights_gradients : %s\n", weights_gradientsSize);
        // printf("biases : %s\n", biasesSize);
        // printf("biases_gradients : %s\n", biases_gradientsSize);
        layer->weights = malloc(weightsSize * sizeof(float));
        layer->weights_gradients = malloc(weights_gradientsSize * sizeof(float));
        layer->biases = malloc(biasesSize * sizeof(float));
        layer->biases_gradients = malloc(biases_gradientsSize * sizeof(float));
        layer->neurons = malloc(biasesSize * sizeof(float));
        layer->weights_number = weightsSize;
        layer->weights_gradients_number = weights_gradientsSize;
        layer->biases_number = biasesSize;
        layer->biases_gradients_number = biases_gradientsSize;
        layer->neurons_number = biasesSize;
        convert_json_to_array(weightsSize, weightsJSON, layer, WEIGHTS);
        convert_json_to_array(weights_gradientsSize, weights_gradientsJSON, layer, WEIGHTS_GRADIENTS);
        convert_json_to_array(biasesSize, biasesJSON, layer, BIASES);
        convert_json_to_array(biases_gradientsSize, biases_gradientsJSON, layer, BIASES_GRADIENTS);
        initialize_array_of_floats(layer->neurons, layer->neurons_number);
        strcpy(weights_name, WEIGHTS_NAME_IN_JSON);
        strcpy(weights_gradients_name, WEIGHTS_GRADIENTS_NAME_IN_JSON);
        strcpy(biases_name, BIASES_NAME_IN_JSON);
        strcpy(biases_gradients_name, BIASES_GRADIENTS_NAME_IN_JSON);
        snprintf(number, sizeof(number), "%d", atoi(number) + 1);
    }
    cJSON_Delete(json);
    return layer;
}
