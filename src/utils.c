#include "../headers/utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *safe_malloc(size_t size) {
    void *ptr = malloc(size);

    if (ptr == NULL) {
        fprintf(stderr, "Error allocating %zu bytes\n", size); 
        exit(EXIT_FAILURE);
    }
    return ptr;
}
