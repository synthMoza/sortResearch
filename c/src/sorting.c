#include <stdlib.h>

#include "sorting.h"
#include "string.h"

// Simple macro for swapping values
#define swap(type, rhs, lhs) do {       \
    type tmp = rhs;                     \
    rhs = lhs;                          \
    lhs = tmp;                          \
} while (0)                             \

void bubbleSort(ElemT* arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j])
                swap(ElemT, arr[i], arr[j]);
        }
    }
}

void selectionSort(ElemT* arr, int size) {
    int minIdx = 0;
    for (int i = 0; i < size; ++i) {
        minIdx = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }

        swap(ElemT, arr[i], arr[minIdx]);
    }
}

void insertionSort(ElemT* arr, int size) {
    for (int i = 1; i < size; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (arr[j] > arr[j + 1])
                swap(ElemT, arr[j], arr[j + 1]);
            else
                break;
        }
    }
}

// Merge two parts into one array, size of the result is the sum of given two
static ElemT* merge(ElemT* lhs, int lsize, ElemT* rhs, int rsize) {
    ElemT* result = (ElemT*) calloc(lsize + rsize, sizeof(ElemT));
    int resultIdx = 0;
    if (result == NULL) {
        printf("merge(): calloc error\n");
        return NULL;
    }

    // Iterate both parts
    int ldx = 0, rdx = 0;
    while (ldx < lsize && rdx < rsize) {
        if (lhs[ldx] > rhs[rdx]) {
            result[resultIdx++] = rhs[rdx++];
        } else {
            result[resultIdx++] = lhs[ldx++];
        }
    }

    // Collect from the rest
    while (ldx < lsize) {
        result[resultIdx++] = lhs[ldx++];
    }

    while (rdx < rsize) {
        result[resultIdx++] = rhs[rdx++];
    }

    return result;
}

// [start;end) 
static void recursiveMergeSort(ElemT* arr, int start, int end) {
    if (end - start <= 0) {
        printf("recursiveMergeSort(): end - start <= 0\n");
        return ;
    }

    if (end - start == 1)
        return ;

    int middle = (end - start - 1) / 2 + 1;

    // Sort recursively two parts
    recursiveMergeSort(arr, start, start + middle);
    recursiveMergeSort(arr, start + middle, end);

    // Merge results
    ElemT* sorted = merge(arr + start, middle, arr + start + middle, end - start - middle);
    // Copy result to the input array
    memcpy(arr + start, sorted, (end - start) * sizeof(ElemT));
}

void mergeSort(ElemT* arr, int size) {
    recursiveMergeSort(arr, 0, size);
}

int doPivot(ElemT* arr, int start, int end) {
    int pivotIdx = end - 1;
    int swapIdx = start;

    for (int i = start; i < end - 1; ++i)
        if (arr[i] < arr[pivotIdx]) {
            swap(ElemT, arr[i], arr[swapIdx]);
            ++swapIdx;
        }

    swap(ElemT, arr[swapIdx], arr[pivotIdx]);
    return swapIdx;
}

void recursiveQuickSort(ElemT* arr, int start, int end) {
    if (start < end - 1) {
        int pivotIdx = doPivot(arr, start, end);
        recursiveQuickSort(arr, start, pivotIdx);
        recursiveQuickSort(arr, pivotIdx, end);
    }
}

void quickSort(ElemT* arr, int size) {
    recursiveQuickSort(arr, 0, size);
}