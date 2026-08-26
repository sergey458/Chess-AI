
#ifndef AI_H
#define AI_H

#define AI_FILE_NAME "Chess-AI.json"

#define INPUT_SIZE 768
#define NUMBER_OF_LAYERS 3 // including output
#define SIZE_OF_LAYERS {128, 64, 1} // the last are outputs

#define INITIAL_WEIGHT_VALUE_LIMIT 0.2f

#define INITIAL_WEIGHTS_VALUE generate_random_small_weight()
#define INITIAL_WEIGHTS_GRADIENTS_VALUE 0.0f
#define INITIAL_BIASES_VALUE 0.0f
#define INITIAL_BIASES_GRADIENTS_VALUE 0.0f

typedef struct layer_t {
    float *weights;
    float *weights_gradients;
    float *biases;
    float *biases_gradients;
} layer_t;

int create_ai_json();
int read_ai_json(layer_t *layer);
int write_in_file(char *file_name, char *text);
int read_file(char *file_name, char **text);

#endif
