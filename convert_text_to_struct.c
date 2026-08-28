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
        } else if (WEIGHTS_GRADIENTS) {
            layer->biases_gradients[i] = f;
        } else if (BIASES) {
            layer->biases[i] = f;
        } else if (BIASES_GRADIENTS) {
            layer->biases_gradients[i] = f;
        }
    }
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

    // printf("%i\n", cJSON_IsArray((const char *)strcat(weights_name, number)));
    while (1) {
        weightsJSON = cJSON_GetObjectItem(json, strcat(weights_name, number));
        weights_gradientsJSON = cJSON_GetObjectItem(json, strcat(weights_gradients_name, number));
        biasesJSON = cJSON_GetObjectItem(json, strcat(biases_name, number));
        biases_gradientsJSON = cJSON_GetObjectItem(json, strcat(biases_gradients_name, number));
        if (!cJSON_IsArray(weightsJSON) || !cJSON_IsArray(weights_gradientsJSON) || !cJSON_IsArray(biasesJSON) || !cJSON_IsArray(biases_gradientsJSON)) {
            break;
        } else {
            int weightsSize = cJSON_GetArraySize(weightsJSON);
            int weights_gradientsSize = cJSON_GetArraySize(weights_gradientsJSON);
            int biasesSize = cJSON_GetArraySize(biasesJSON);
            int biases_gradientsSize = cJSON_GetArraySize(biases_gradientsJSON);
            layer->weights = malloc(weightsSize * sizeof(float));
            layer->weights_gradients = malloc(weights_gradientsSize * sizeof(float));
            layer->biases = malloc(biasesSize * sizeof(float));
            layer->biases_gradients = malloc(biases_gradientsSize * sizeof(float));
            layer->weights_number = weightsSize;
            layer->weights_gradients_number = weights_gradientsSize;
            layer->biases_number = biasesSize;
            layer->biases_gradients_number = biases_gradientsSize;
            convert_json_to_array(weightsSize, weightsJSON, layer, WEIGHTS);
            convert_json_to_array(weights_gradientsSize, weights_gradientsJSON, layer, WEIGHTS_GRADIENTS);
            convert_json_to_array(biasesSize, biasesJSON, layer, BIASES);
            convert_json_to_array(biases_gradientsSize, biases_gradientsJSON, layer, BIASES_GRADIENTS);
            layer_t *prev = layer;
            layer = malloc(sizeof(layer_t));
            layer->next = prev;
        }
        strcpy(weights_name, WEIGHTS_NAME_IN_JSON);
        strcpy(weights_gradients_name, WEIGHTS_GRADIENTS_NAME_IN_JSON);
        strcpy(biases_name, BIASES_NAME_IN_JSON);
        strcpy(biases_gradients_name, BIASES_GRADIENTS_NAME_IN_JSON);
        snprintf(number, sizeof(number), "%d", atoi(number) + 1);
    }
    return layer;
}
