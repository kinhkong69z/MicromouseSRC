/*
 * function_c.c
 *
 *  Created on: Oct 24, 2025
 *      Author: kinhz
 */

#include "function_c.h"

Vector mouse_state;

void initVector(Vector *vec, size_t initialCapacity) {
    vec->data = (int *)malloc(initialCapacity * sizeof(int));
    vec->size = 0;
    vec->capacity = initialCapacity;
    vec->index = 0;
}

void resizeVector(Vector *vec) {
    vec->capacity *= 2;
    vec->data = (int *)realloc(vec->data, vec->capacity * sizeof(int));
}

void pushBack(Vector *vec, int value) {
    if (vec->size == vec->capacity) {
        resizeVector(vec);
    }
    vec->data[vec->size++] = value;
}

int get(Vector *vec, size_t index) {
    if (index < vec->size) {
        return vec->data[index];
    }
    exit(EXIT_FAILURE);
}

void freeVector(Vector *vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}
