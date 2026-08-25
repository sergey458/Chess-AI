
#ifndef CHESS_AI_H
#define CHESS_AI_h

#define AI_FILE_NAME "Chess-AI.json"

#define INPUT_SIZE 768
#define NUMBER_OF_LAYERS 3 // including output
#define SIZE_OF_LAYERS {128, 64, 1} // the last are outputs

#define INITIAL_WEIGHT_VALUE_LIMIT 0.2f

int initialize_network();
int write_in_file(char *json_str);

#endif
