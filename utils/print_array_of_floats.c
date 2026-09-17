#include <stdio.h>

int print_array_of_floats(float *array, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        printf("%.6f ", array[i]);
    }
    return 0;
}

int initialize_array_of_floats(float *array, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        array[i] = 0.0f;
    }
    return 0;
}
