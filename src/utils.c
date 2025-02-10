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

void rand_arr(char *arr, uint8 n) {
    for (int i = 0; i < n; i++) {
        uint8 rand_n = rand() % n;
        int tmp = arr[rand_n];
        arr[rand_n] = arr[i]; 
        arr[i] = tmp;
    }
}

void set_arr(int val, int *arr, uint8 n) {
    for (int i = 0; i < n; i++) {
        arr[i] = val;
    }
}

int in_arr(int val, int *arr, uint8 n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == val) {
            return 1;
        }
    }
    return 0;
}
