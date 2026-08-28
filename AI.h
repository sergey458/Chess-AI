
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

#define WEIGHTS_NAME_IN_JSON "weights" // max 64 characters
#define WEIGHTS_GRADIENTS_NAME_IN_JSON "weights_gradients" // max 64 characters
#define BIASES_NAME_IN_JSON "biases" // max 64 characters
#define BIASES_GRADIENTS_NAME_IN_JSON "biases_gradients" // max 64 characters

typedef struct layer_t {
    float *weights;
    float *weights_gradients;
    float *biases;
    float *biases_gradients;
    int weights_number;
    int weights_gradients_number;
    int biases_number;
    int biases_gradients_number;
    struct layer_t *next;
} layer_t;

typedef enum ArrayType_t {
    WEIGHTS,
    WEIGHTS_GRADIENTS,
    BIASES,
    BIASES_GRADIENTS
} ArrayType_t;

int create_ai_json();
layer_t *convert_text_to_struct(char *text, layer_t *layer);
int write_in_file(char *file_name, char *text);
int read_file(char *file_name, char **text);
int print_array_of_floats(float *array, int arraySize);

#endif
