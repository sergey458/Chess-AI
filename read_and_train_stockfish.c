#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "AI.h"

int is_a_chess_piece(char letter) {
    char *chess_pieces = "prnbqkPRNBQK";
    if (strchr(chess_pieces, letter) != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int convert_letter_to_code(char letter, int inputs[INPUT_SIZE], int p) {
    if (letter == 'p') {
        inputs[p * 12 + BLACK_PAWN_CODE] = 1;
    } else if (letter == 'r') {
        inputs[p * 12 + BLACK_ROOK_CODE] = 1;
    } else if (letter == 'n') {
        inputs[p * 12 + BLACK_KNIGHT_CODE] = 1;
    } else if (letter == 'b') {
        inputs[p * 12 + BLACK_BISHOP_CODE] = 1;
    } else if (letter == 'q') {
        inputs[p * 12 + BLACK_QUEEN_CODE] = 1;
    } else if (letter == 'k') {
        inputs[p * 12 + BLACK_KING_CODE] = 1;
    } else if (letter == 'P') {
        inputs[p * 12 + WHITE_PAWN_CODE] = 1;
    } else if (letter == 'R') {
        inputs[p * 12 + WHITE_ROOK_CODE] = 1;
    } else if (letter == 'N') {
        inputs[p * 12 + WHITE_KNIGHT_CODE] = 1;
    } else if (letter == 'B') {
        inputs[p * 12 + WHITE_BISHOP_CODE] = 1;
    } else if (letter == 'Q') {
        inputs[p * 12 + WHITE_QUEEN_CODE] = 1;
    } else if (letter == 'K') {
        inputs[p * 12 + WHITE_KING_CODE] = 1;
    }
}

int convert_board_to_binary(char *fen, int inputs[INPUT_SIZE]) {
    int board_pos = 0;
    int i = 0;

    while (fen[i] != ' ' && board_pos < 64) {
        if (isdigit(fen[i]) > 0) {
            board_pos = board_pos + fen[i] - '0';
            printf("empty : %i\n", board_pos);
        } else if (is_a_chess_piece(fen[i])) {
            printf("figure : %c\n", fen[i]);
            convert_letter_to_code(fen[i], inputs, board_pos);
            board_pos = board_pos + 1;
        }
        i++;
    }
    return 0;
}

int convert_fen_to_binary(char *fen, int inputs[INPUT_SIZE]) {
    char *space1 = strchr(fen, ' ');
    int space1_i = space1 - fen;
    char *fen1 = NULL;

    if (fen[space1_i + 1] == 'b') {
        fen1 = malloc_and_strncpy(fen, space1_i);
        my_strrev(fen1);
    }
    convert_board_to_binary(fen1, inputs);
    free(fen1);
    return 0;
}

int read_and_train_stockfish(layer_t *layer) {
    FILE* fp = fopen(DATASET_FILE_PATH, "r");
    int inputs[INPUT_SIZE] = {0};
    char buffer[256];
    char *value = NULL;
    int column = 0;
    int i = 0;

    while (fgets(buffer, 256, fp) && i < 2) {
        if (i == 0) {
            i++;
            continue;
        }
        value = strtok(buffer, ",");
        while (value) {
            if (column == 0) {
                printf("fen : ");
                printf("%s\n", value);
                convert_fen_to_binary(value, inputs);
            } else if (column == 1) {
                printf("move 1 : ");
                printf("%s\n", value);
            } else if (column == 2) {
                printf("move 2 : ");
                printf("%s\n", value);
            } else if (column == 3) {
                printf("move 3 : ");
                printf("%s\n", value);
            } else if (column == 4) {
                printf("move 4 : ");
                printf("%s\n", value);
            } else if (column == 5) {
                printf("move 5 : ");
                printf("%s\n", value);
            } else if (column == 6) {
                printf("evaluation : ");
                printf("%s\n", value);
            }
            printf("\n");
            value = strtok(NULL, ",");
            column++;
        }
        column = 0;
        i++;
    }
    print_array_of_ints(inputs, INPUT_SIZE);
    fclose(fp);
    return 0;
}
