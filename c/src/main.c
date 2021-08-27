#include "testing.h"

// Path to test and benchmark JSON files
const char* sortTestPath = "../../tests/test.json";
const char* sortBenchPath = "../../tests/bench.json";

// Launch all tests on sorting functions
void launchSortTests() {
    cJSON* json = openJSON(sortTestPath);

    testCases* sortTestCases = loadData(json, "sort_test_cases");
    testCases* sortTestAnswers = loadData(json, "sort_test_answers");

    testSortFunc(bubbleSort, "Bubble Sort", sortTestCases, sortTestAnswers);
    testSortFunc(selectionSort, "Selection Sort", sortTestCases, sortTestAnswers);
    testSortFunc(insertionSort, "Insertion Sort", sortTestCases, sortTestAnswers);
    testSortFunc(mergeSort, "Merge Sort", sortTestCases, sortTestAnswers);
    testSortFunc(quickSort, "Quick Sort", sortTestCases, sortTestAnswers);
    
    freeTestData(sortTestCases);
    freeTestData(sortTestAnswers);

    freeJSON(json);
}

void launchSortBenchmarks() {
    cJSON* json = openJSON(sortBenchPath);

    testCases* sortBenchCases = loadData(json, "sort_bench_data");
    testCases* sortBenchAnswers = loadData(json, "sort_bench_ans");

    benchSortFunc(bubbleSort, "Bubble Sort", sortBenchCases, sortBenchAnswers);
    benchSortFunc(selectionSort, "Selection Sort", sortBenchCases, sortBenchAnswers);
    benchSortFunc(insertionSort, "InsertionSort", sortBenchCases, sortBenchAnswers);
    benchSortFunc(mergeSort, "Merge Sort", sortBenchCases, sortBenchAnswers);
    benchSortFunc(quickSort, "Quick Sort", sortBenchCases, sortBenchAnswers);

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