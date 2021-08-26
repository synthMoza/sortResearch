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

// Global test cases to copy from
testCases* sortTestCases = NULL;
testCases* sortTestAnswers = NULL;

testCases* sortBenchCases = NULL;
testCases* sortBenchAnswers = NULL;

// Path to test and benchmark JSON files
const char* sortTestPath = "../../tests/test.json";
const char* sortBenchPath = "../../tests/bench.json";

#define checkNull(p, str) do {          \
    if (p == NULL) {                    \
        printf(str);                    \
        exit(EXIT_FAILURE);             \
    }                                   \
} while(0)                              \

char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        return NULL;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);

    char* result = (char*) calloc(size + 1, sizeof(char));
    checkNull(result, "Calloc error!");
    fread(result, sizeof(char), size, file);
    result[size] = '\0';
    
    fclose(file);
    return result;
}


// Clone the given case
testCase* cloneCase(testCase* input) {
    testCase* result = (testCase*)calloc(1, sizeof(testCase));
    checkNull(result, "Calloc error!");

    result->size = input->size;
    result->array = (ElemT*)calloc(result->size, sizeof(ElemT));
    checkNull(result->array, "Calloc error!");

    for (int i = 0; i < result->size; ++i) {
        result->array[i] = input->array[i];
    }

    return result;
}

void freeClone(testCase* input) {
    free(input->array);
    free(input);
}

cJSON* openJSON(const char* path) {
    // Read JSON file into const char*
    char* string = readFile(path);
    if (string == NULL) {
        printf("Error with JSON file!");
        exit(EXIT_FAILURE);
    }


    // Parse JSON file
    cJSON* json = cJSON_Parse(string);
    free(string);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }

        exit(EXIT_FAILURE);
    }

    return json;
}

void freeJSON(cJSON* json) {
    cJSON_Delete(json);
}

// Load test data to sortTestCases and sortTestAnswers
testCases* loadData(cJSON* json, const char* field) {
    // Allocate structure
    testCases* sortCases = (testCases*) calloc(1, sizeof(testCases));
    checkNull(sortCases, "Calloc error!");

    cJSON* test_cases = NULL;
    cJSON* test_answers = NULL;

    // Get all test cases
    test_cases = cJSON_GetObjectItemCaseSensitive(json, field);
    checkNull(test_cases, "Error while getting field!");
    
    // Allocate array of test cases
    int casesNumber = cJSON_GetArraySize(test_cases);
    sortCases->size = casesNumber;
    sortCases->cases = (testCase*) calloc(casesNumber, sizeof(testCase));
    checkNull(sortCases->cases, "Calloc error!");

    // Iterate each case
    cJSON* sort_test_case = NULL;
    for (int i = 0; i < casesNumber; ++i) {
        sort_test_case = cJSON_GetArrayItem(test_cases, i);
        
        // Allocate case array
        int caseNumber = cJSON_GetArraySize(sort_test_case);
        sortCases->cases[i].array = (ElemT*) calloc(caseNumber, sizeof(ElemT));
        sortCases->cases[i].size = caseNumber;
        checkNull(sortCases->cases[i].array, "Calloc error!");

        // Iterate case and fill array
        int j = 0;
        cJSON* jchild = NULL;
        for (jchild = sort_test_case->child, j = 0; jchild; jchild = jchild->next, ++j) {
            if (!cJSON_IsNumber(jchild)) {
                printf("Item is not a number");
                exit(EXIT_FAILURE);
            }

            sortCases->cases[i].array[j] = jchild->valueint;
        }
    }

    return sortCases;
}

void freeTestData(testCases* cases) {
    for (int i = 0; i < cases->size; ++i)
        free(cases->cases[i].array);

    free(cases->cases);
    free(cases);
}

// Log test results in console
// Format: [Test <testNumber> - "<testName>:<testSubname>"]: <testResult>
static void logTest(const char* testName, const char* testSubname, bool result) {
    static int testNumber = 0;
    
    printf("[Test %d - \"%s:%s\"]: ", testNumber++, testName, testSubname);
    if (result) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

// Test sorting functions
bool testSortFunc(sortFunc f, const char* testName) {
    for (int i = 0; i < sortTestCases->size; ++i) {
        bool result = true;
        testCase* clone = cloneCase(&sortTestCases->cases[i]);
        f(clone->array, clone->size);

        // Compare with the answer
        for (int j = 0; j < clone->size; ++j) {
            if (clone->array[j] != sortTestAnswers->cases[i].array[j]) {
                result = false;
                break;
            }
        }
           
        char testSubname[64]; // buf size is enough
        sprintf(testSubname, "(size=%d)", clone->size);
        logTest(testName, testSubname, result);
        // If test failed, print result and expected answer
        if (!result) {
            // Sorting result
            printf("Got: [ ");
            for (int j = 0; j < clone->size; ++j) {
                printf("%d ", clone->array[j]);
            }
            printf("]\n");

            // Expected answer
            printf("Expected: [ ");
            for (int j = 0; j < sortTestAnswers->cases[i].size; ++j) {
                printf("%d ", sortTestAnswers->cases[i].array[j]);
            }
            printf("]\n");
        }
        
        // Free resources
        freeClone(clone);
    }
}

// Launch all tests on sorting functions
void launchSortTests() {
    cJSON* json = openJSON(sortTestPath);

    sortTestCases = loadData(json, "sort_test_cases");
    sortTestAnswers = loadData(json, "sort_test_answers");

    testSortFunc(bubbleSort, "Bubble Sort");
    testSortFunc(selectionSort, "Selection Sort");
    testSortFunc(insertionSort, "Insertion Sort");
    testSortFunc(mergeSort, "Merge Sort");
    testSortFunc(quickSort, "Quick Sort");
    
    freeTestData(sortTestCases);
    freeTestData(sortTestAnswers);

    freeJSON(json);
}

static void logBench(const char* benchName, const char* benchSubname, double ms) {
    static int benchNumber = 0;

    printf("[Bench %d - \"%s:%s\"]: time = %gms\n", benchNumber++, benchName, benchSubname, ms);
}

// Benchmark sorting fucntions
bool benchSortFunc(sortFunc f, const char* benchName) {
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    LARGE_INTEGER frequency;
    double interval = 0; // milliseconds
    
    for (int i = 0; i < sortBenchCases->size; ++i) {
        bool result = true;
        testCase* clone = cloneCase(&sortBenchCases->cases[i]);
        
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        f(clone->array, clone->size);
        QueryPerformanceCounter(&end);
        interval = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1e3;

        // Compare with the answer
        for (int j = 0; j < clone->size; ++j) {
            if (clone->array[j] != sortBenchAnswers->cases[i].array[j]) {
                result = false;
                break;
            }
        }

        char benchSubname[64]; // buf size is enough
        sprintf(benchSubname, "(size=%d)", clone->size);
        logBench(benchName, benchSubname, interval);
        // If test failed, print result and expected answer
        if (!result) {
            // Sorting result
            printf("Got: [ ");
            for (int j = 0; j < clone->size; ++j) {
                printf("%d ", clone->array[j]);
            }
            printf("]\n");

            // Expected answer
            printf("Expected: [ ");
            for (int j = 0; j < sortTestAnswers->cases[i].size; ++j) {
                printf("%d ", sortTestAnswers->cases[i].array[j]);
            }
            printf("]\n");
        }

        // Free resources
        freeClone(clone);
    }
}

void launchSortBenchmarks() {
    cJSON* json = openJSON(sortBenchPath);

    sortBenchCases = loadData(json, "sort_bench_data");
    sortBenchAnswers = loadData(json, "sort_bench_ans");

    benchSortFunc(bubbleSort, "Bubble Sort");
    benchSortFunc(selectionSort, "Selection Sort");
    benchSortFunc(insertionSort, "InsertionSort");
    benchSortFunc(mergeSort, "Merge Sort");
    benchSortFunc(quickSort, "Quick Sort");

    freeTestData(sortBenchCases);
    freeTestData(sortBenchAnswers);

    freeJSON(json);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./sortResearch <flags>\n");
        printf("\t-t - run all tests\n");
        printf("\t-b - run all benchmarks\n");

        exit(EXIT_FAILURE);
    }

    bool launchTests = false;
    bool launchBenchmarks = false;

    for (int i = 1; i < argc; ++i) {
        // Check if it is the flag
        if (argv[i][0] != '-') {
            printf("Unknown argument %s", argv[i]);
            exit(EXIT_FAILURE);
        }

        // Check if it is one symbol flag
        if (strlen(argv[i]) > 2) {
            printf("Unknown flag %s", argv[i]);
            exit(EXIT_FAILURE);
        }

        char flag = argv[i][1];
        switch (flag) {
        case 't':
            launchTests = true;
            break;
        case 'b':
            launchBenchmarks = true;
            break;
        default:
            printf("Unknown flag %c", flag);
            exit(EXIT_FAILURE);
        }
    }

    if (launchTests)
        launchSortTests();

    if (launchBenchmarks)
        launchSortBenchmarks();
}