
#ifndef AI_H
#define AI_H

#define AI_FILE_PATH "Chess-AI.json"
#define DATASET_FILE_PATH "datasets/stockfish_position_evaluations.csv"
#define DATASET_PARSING_FUNCTION read_and_train_stockfish(layer)
#define MIN_DATASET_EVALUATION -1731
#define MAX_DATASET_EVALUATION 1761

#define INPUT_SIZE 772
#define NUMBER_OF_LAYERS 3 // including output
#define SIZE_OF_WEIGHTS {INPUT_SIZE * 128, 128 * 64, 64 * 1} // the last are outputs
#define SIZE_OF_BIASES {128, 64, 1} // the last are outputs

#define INITIAL_WEIGHT_VALUE_LIMIT 0.2f

#define INITIAL_WEIGHTS_VALUE generate_random_small_weight()
#define INITIAL_WEIGHTS_GRADIENTS_VALUE 0.0f
#define INITIAL_BIASES_VALUE 0.0f
#define INITIAL_BIASES_GRADIENTS_VALUE 0.0f

#define WEIGHTS_NAME_IN_JSON "weights" // max 64 characters
#define WEIGHTS_GRADIENTS_NAME_IN_JSON "weights_gradients" // max 64 characters
#define BIASES_NAME_IN_JSON "biases" // max 64 characters
#define BIASES_GRADIENTS_NAME_IN_JSON "biases_gradients" // max 64 characters

#define BLACK_PAWN_CODE 0
#define BLACK_ROOK_CODE 1
#define BLACK_KNIGHT_CODE 2
#define BLACK_BISHOP_CODE 3
#define BLACK_QUEEN_CODE 4
#define BLACK_KING_CODE 5

#define WHITE_PAWN_CODE 6
#define WHITE_ROOK_CODE 7
#define WHITE_KNIGHT_CODE 8
#define WHITE_BISHOP_CODE 9
#define WHITE_QUEEN_CODE 10
#define WHITE_KING_CODE 11


typedef struct layer_t { // layer 1
    float *weights; // 772 * 128
    float *weights_gradients; // 772 * 128
    float *biases; // 128
    float *biases_gradients; // 128
    float *neurons; // 128

    int weights_number;
    int weights_gradients_number;
    int biases_number;
    int biases_gradients_number;
    int neurons_number;
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
int convert_fen_to_binary(char *fen, int inputs[INPUT_SIZE]);

int initialize_array_of_floats(float *array, int arraySize);
char *malloc_and_strncpy(char *src, int n);
int my_strrev(char *str);
int print_array_of_floats(float *array, int arraySize);
int print_array_of_ints(int *array, int arraySize);
int read_file(char *file_name, char **text);
int write_in_file(char *file_name, char *text);
layer_t *reverse_struct_list(layer_t *layer);

int read_and_train_stockfish(layer_t *layer);

#endif
