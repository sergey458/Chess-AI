#include <string.h>

int my_strrev(char *str) {
    int i = 0;
    int j = strlen(str) - 1;
    char tmp = 'a';

    while (i < j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}
