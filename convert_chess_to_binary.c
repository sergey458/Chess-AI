#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
        } else if (is_a_chess_piece(fen[i])) {
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
