#include <stdlib.h>
#include <string.h>

char *malloc_and_strncpy(char *src, int n) {
    char *dest = NULL;

    dest = malloc(n + 1);
    strncpy(dest, src, n);
    dest[n] = '\0';
    return dest;
}
