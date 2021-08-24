#pragma once

typedef int ElemT;

// Simple macro for swapping values
#define swap(type, rhs, lhs) do {       \
    type tmp = rhs;                     \
    rhs = lhs;                          \
    lhs = tmp;                          \
} while (0)                             \

// Sort the given array using bubble sort algorithm
void bubbleSort(ElemT* arr, int size);