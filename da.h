#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DA


#define da(type) type *

#define da_size(arr) (*(size_t*)((void*)(arr) - sizeof(size_t)))

#define __da_head(arr) ((void *)(arr) - sizeof(size_t))

#define __init_da(arr) \
if ((arr) == NULL) { \
    (arr) = malloc(sizeof(size_t)) + sizeof(size_t); \
    da_size(arr) = 0; \
}

#define da_append(arr, item) \
do { \
    __init_da(arr); \
    (arr) = realloc(__da_head(arr), sizeof((arr)[0]) * ++da_size(arr) + sizeof(size_t)) + sizeof(size_t); \
    (arr)[da_size(arr) - 1] = (item); \
} while (0);

#define da_remove(arr, index) \
do { \
    memmove(&(arr)[index], &(arr)[(index) + 1], (da_size(arr) - (index) - 1) * sizeof((arr)[0])); \
    (arr) = realloc(__da_head(arr), sizeof((arr)[0]) * --da_size(arr) + sizeof(size_t)) + sizeof(size_t); \
} while (0);

#define da_last(arr) ((arr)[da_size(arr) - 1])

#define DA
#endif /* ifndef DA */
