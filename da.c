#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define da(type) type *

#define da_size(arr) (*(size_t*)((arr) - sizeof(size_t)))

#define __da_head(arr) ((void *)(arr) - sizeof(size_t))

#define __init_da(arr) \
if ((arr) == NULL) { \
    (arr) = malloc(sizeof(size_t)) + sizeof(size_t); \
    da_size(arr) = 0; \
}

#define da_append(arr, item) \
do { \
    __init_da(arr); \
    (arr) = realloc(__da_head(arr), sizeof(arr[0]) * ++da_size(arr) + sizeof(size_t)) + sizeof(size_t); \
    arr[da_size(arr) - 1] = item; \
} while (0);

#define da_remove(arr, index) \
do { \
    memmove(&(arr)[index], &(arr)[index + 1], (da_size(arr) - index - 1) * sizeof(arr[0])); \
    (arr) = realloc(__da_head(arr), sizeof(arr[0]) * --da_size(arr) + sizeof(size_t)) + sizeof(size_t); \
} while (0);

int main (int argc, char *argv[]) {
    da(int) numbers = {0};
    da_append(numbers, 1);
    da_append(numbers, 2);
    da_append(numbers, 3);
    da_append(numbers, 4);

    for (size_t i = 0; i < da_size(numbers); i++) {
        printf("%d\n", numbers[i]);
    }

    da_remove(numbers, 1);

    for (size_t i = 0; i < da_size(numbers); i++) {
        printf("%d\n", numbers[i]);
    }

    return 0;
}
