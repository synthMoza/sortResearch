#pragma once

// Element type to sort
typedef int ElemT;

// Sort the given array using bubble sort algorithm
void bubbleSort(ElemT* arr, int size);
// Sort the given array using selection sort algorithm
void selectionSort(ElemT* arr, int size);
// Sort the given array using insertion sort algorithm
void insertionSort(ElemT* arr, int size);
// Sort the given array using merge sort algorithm
void mergeSort(ElemT* arr, int size);
// Sort the given array using quick sort algorithm
// Pivot element is the last one
void quickSort(ElemT* arr, int size);