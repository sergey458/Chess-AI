#include <stdlib.h>
#include <stdio.h>
#include "../AI.h"

layer_t *reverse_struct_list(layer_t *layer) {
    layer_t *tmp_next = layer->next;
    layer_t *tmp_layer = layer;

    layer->next = NULL;
    while (tmp_next != NULL) {
        layer = tmp_next;
        tmp_next = layer->next;
        layer->next = tmp_layer;
        tmp_layer = layer;
    }
    return layer;
}
