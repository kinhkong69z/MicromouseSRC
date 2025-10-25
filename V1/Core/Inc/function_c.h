/*
 * function_c.h
 *
 *  Created on: Oct 24, 2025
 *      Author: kinhz
 */

#ifndef INC_FUNCTION_C_H_
#define INC_FUNCTION_C_H_


#include "main.h"

typedef struct {
    int *data;       // Pointer to the array
    size_t size;     // Current number of elements
    size_t capacity; // Maximum capacity
    size_t index;
} Vector;

void initVector(Vector *vec, size_t initialCapacity);
void resizeVector(Vector *vec);
void pushBack(Vector *vec, int value);
int get(Vector *vec, size_t index);
void freeVector(Vector *vec);

extern Vector mouse_state;

#endif /* INC_FUNCTION_C_H_ */
