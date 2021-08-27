#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "sorting.h"
#include "cJSON.h"

// Sorting function type
typedef void(*sortFunc)(int*, int);

// Test case including data and size
typedef struct testCase {
    ElemT* array;
    int size;
} testCase;

// Test cases including all cases and size
typedef struct testCases {
    testCase* cases;
    int size;
} testCases;

#define checkNull(p, str) do {          \
    if (p == NULL) {                    \
        printf(str);                    \
        exit(EXIT_FAILURE);             \
    }                                   \
} while(0)                              \


// Test sorting function - compares results with the answer, logs test results into console
void testSortFunc(sortFunc f, const char* testName, testCases* sortTestCases, testCases* sortTestAnswers);
// Benchmark sorting fucntions - measure execution time on big arrays, log results into console
void benchSortFunc(sortFunc f, const char* benchName, testCases* sortBenchCases, testCases* sortBenchAnswers);
// Free all test cases
void freeTestData(testCases* cases);
// Load test data to sortTestCases and sortTestAnswers
testCases* loadData(cJSON* json, const char* field);
// Free cJSON pointer
void freeJSON(cJSON* json);
// Parse the JSON file, return pointer to cJSON struct
cJSON* openJSON(const char* path);
