package sorting

import (
	"encoding/json"
	"os"
	"reflect"
	"sort"
	"strconv"
	"testing"
)

const TestFilePath string = "../../tests/test.json"
const BenchFilePath string = "../../tests/bench.json"

// Clone method for test data
func clone(src []int) []int {
	dst := make([]int, len(src))
	copy(dst, src)
	return dst
}

// Struct for parsing test data from JSON
type SortTestData struct {
	Cases   [][]int `json:"sort_test_cases"`
	Answers [][]int `json:"sort_test_answers"`
}

// Struct for parsing bench data from JSON
type SortBenchData struct {
	Cases   [][]int `json:"sort_bench_data"`
	Answers [][]int `json:"sort_bench_ans"`
}

// Sorting function type for testing
type sortFunc func([]int)

// Read test data from given JSON file
func readTestData(t *testing.T) ([][]int, [][]int) {
	sortTestData := &SortTestData{}
	sortTestDataRaw, err := os.ReadFile(TestFilePath)
	if err != nil {
		t.Error("can't read", TestFilePath)
	}

	err = json.Unmarshal(sortTestDataRaw, sortTestData)
	if err != nil {
		t.Error(err)
	}

	return sortTestData.Cases, sortTestData.Answers
}

// Read benchmark data from the given JSON file
func readBenchData(b *testing.B) ([][]int, [][]int) {
	sortBenchData := &SortBenchData{}
	sortBenchDataRaw, err := os.ReadFile(BenchFilePath)
	if err != nil {
		b.Error("can't read", BenchFilePath)
	}

	err = json.Unmarshal(sortBenchDataRaw, sortBenchData)
	if err != nil {
		b.Error(err)
	}

	return sortBenchData.Cases, sortBenchData.Answers
}

func testSortFunc(s sortFunc, t *testing.T) {
	sortCases, sortAnswers := readTestData(t)

	for idx := range sortCases {
		s(sortCases[idx])
		if !reflect.DeepEqual(sortCases[idx], sortAnswers[idx]) {
			t.Errorf("wrong answer on test %d\n got: %v\n expected: %v", idx, sortCases[idx], sortAnswers[idx])
		}
	}
}

func TestSort(t *testing.T) {
	t.Run("bubbleSort", func(t *testing.T) {
		testSortFunc(BubbleSort, t)
	})
	t.Run("selectionSort", func(t *testing.T) {
		testSortFunc(SelectionSort, t)
	})
}

func benchmarkSortFunc(s sortFunc, b *testing.B) {
	sortCases, sortAnswers := readBenchData(b)

	// Launch all bench cases
	b.ResetTimer()
	for idx := range sortCases {
		b.Run("size="+strconv.Itoa(len(sortCases[idx])), func(bb *testing.B) {
			for j := 0; j < bb.N; j++ {
				sortCasesClone := clone(sortCases[idx])

				s(sortCasesClone)
				if !reflect.DeepEqual(sortCasesClone, sortAnswers[idx]) {
					b.Error("wrong answer on benchmark", idx)
				}
			}
		})
	}
}

func BenchmarkSort(b *testing.B) {
	b.Run("stdSort", func(b *testing.B) {
		benchmarkSortFunc(sort.Ints, b)
	})
	b.Run("bubbleSort", func(b *testing.B) {
		benchmarkSortFunc(BubbleSort, b)
	})
	b.Run("selectionSort", func(b *testing.B) {
		benchmarkSortFunc(SelectionSort, b)
	})
}
