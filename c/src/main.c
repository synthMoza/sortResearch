#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sorting.h"
#include "cJSON.h"

// Sorting function type
typedef void(*sortFunc)(int*, int);

// Bench sorting functions
void benchSortFunc(sortFunc f) {

}

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

// Path to test and benchmark JSON files
const char* sortTestPath = "../../tests/test.json";
// const char* sortBenchPath = "../../../tests/bench.json";

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

// Load test data to sortTestCases and sortTestAnswers
void loadTestData() {
    // Allocate structure
    sortTestCases = (testCases*) calloc(1, sizeof(testCases));
    checkNull(sortTestCases, "Calloc error!");
    sortTestAnswers = (testCases*) calloc(1, sizeof(testCases));
    checkNull(sortTestAnswers, "Calloc error!");

    // Read JSON file into const char*
    char* sortTestString = readFile(sortTestPath);
    if (sortTestString == NULL) {
        printf("Error with JSON file!");
        exit(EXIT_FAILURE);
    }


    // Parse JSON file
    cJSON* json = cJSON_Parse(sortTestString);
    free(sortTestString);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }

        exit(EXIT_FAILURE);
    }

    cJSON* sort_test_cases = NULL;
    cJSON* sort_test_answers = NULL;

    // Get all test cases
    sort_test_cases = cJSON_GetObjectItemCaseSensitive(json, "sort_test_cases");
    checkNull(sort_test_cases, "Error while getting sort test cases!");
    
    // Allocate array of test cases
    int casesNumber = cJSON_GetArraySize(sort_test_cases);
    sortTestCases->size = casesNumber;
    sortTestCases->cases = (testCase*) calloc(casesNumber, sizeof(testCase));
    checkNull(sortTestCases->cases, "Calloc error!");

    // Iterate each case
    cJSON* sort_test_case = NULL;
    for (int i = 0; i < casesNumber; ++i) {
        sort_test_case = cJSON_GetArrayItem(sort_test_cases, i);
        
        // Allocate case array
        int caseNumber = cJSON_GetArraySize(sort_test_case);
        sortTestCases->cases[i].array = (ElemT*) calloc(caseNumber, sizeof(ElemT));
        sortTestCases->cases[i].size = caseNumber;
        checkNull(sortTestCases->cases[i].array, "Calloc error!");

        // Iterate case and fill array
        for (int j = 0; j < caseNumber; ++j) {
            cJSON* item = cJSON_GetArrayItem(sort_test_case, j);
            checkNull(item, "Error while getting item!");

            if (!cJSON_IsNumber(item)) {
                printf("Item is not a number");
                exit(EXIT_FAILURE);
            }

            sortTestCases->cases[i].array[j] = item->valueint;
        }
    }   

    sort_test_answers = cJSON_GetObjectItemCaseSensitive(json, "sort_test_answers");
    checkNull(sort_test_answers, "Error while getting sort test answers!");

    // Allocate array of test cases
    int answersNumber = cJSON_GetArraySize(sort_test_answers);
    sortTestAnswers->size = answersNumber;
    sortTestAnswers->cases = (testCase*) calloc(answersNumber, sizeof(testCase));
    checkNull(sortTestAnswers->cases, "Calloc error!");

    // Iterate each case
    cJSON* sort_test_answer = NULL;
    for (int i = 0; i < answersNumber; ++i) {
        sort_test_answer = cJSON_GetArrayItem(sort_test_answers, i);
        
        // Allocate case array
        int answerNumber = cJSON_GetArraySize(sort_test_answer);
        sortTestAnswers->cases[i].array = (ElemT*) calloc(answerNumber, sizeof(ElemT));
        sortTestAnswers->cases[i].size = answerNumber;
        checkNull(sortTestAnswers->cases[i].array, "Calloc error!");

        // Iterate case and fill array
        for (int j = 0; j < answerNumber; ++j) {
            cJSON* item = cJSON_GetArrayItem(sort_test_answer, j);
            checkNull(item, "Error while getting item!");

            if (!cJSON_IsNumber(item)) {
                printf("Item is not a number");
                exit(EXIT_FAILURE);
            }

            sortTestAnswers->cases[i].array[j] = item->valueint;
        }
    }   

    cJSON_Delete(json);
}

void freeTestData() {
    for (int i = 0; i < sortTestCases->size; ++i) {
        free(sortTestCases->cases[i].array);
    }

    free(sortTestCases->cases);
    free(sortTestCases);

    for (int i = 0; i < sortTestAnswers->size; ++i) {
        free(sortTestAnswers->cases[i].array);
    }

    free(sortTestAnswers->cases);
    free(sortTestAnswers);
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
        
        // Free resources
        freeClone(clone);
    }
}

// Launch all tests on sorting functions
void launchSortTests() {
    loadTestData();
   
    testSortFunc(bubbleSort, "Bubble Sort");
    
    freeTestData();
}

int main() {
    launchSortTests();
}