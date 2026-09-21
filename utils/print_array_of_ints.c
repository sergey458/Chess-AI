#include <stdio.h>

int print_array_of_ints(int *array, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        printf("%i ", array[i]);
    }
    printf("\n");
    return 0;
}
