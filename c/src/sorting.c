#include "sorting.h"

void bubbleSort(ElemT* arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j])
                swap(ElemT, arr[i], arr[j]);
        }
    }
}