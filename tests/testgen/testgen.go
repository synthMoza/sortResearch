package testgen

import (
	"encoding/json"
	"math/rand"
	"os"
)

const TestFilePath string = "test.json"
const BenchFilePath string = "bench.json"

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

func GenerateTests() {
	sizeCases := []int{10, 25, 50, 100, 250, 1000, 5000}
	sortTestData := &SortTestData{
		Cases:   make([][]int, 0, len(sizeCases)),
		Answers: make([][]int, 0, len(sizeCases)),
	}

	for _, size := range sizeCases {
		// Generate answer slice
		answer := make([]int, size)
		data := make([]int, size)

		for i := 0; i < size; i++ {
			answer[i] = i
		}

		copy(data, answer)

		// Shuffle answer and geenrate case
		rand.Shuffle(size, func(i, j int) { data[i], data[j] = data[j], data[i] })
		sortTestData.Cases = append(sortTestData.Cases, data)
		sortTestData.Answers = append(sortTestData.Answers, answer)
	}

	// Marchall all tests into json file
	testsRaw, err := json.Marshal(sortTestData)
	if err != nil {
		panic(err)
	}

	outputFile, err := os.Create(TestFilePath)
	if err != nil {
		panic(err)
	}

	outputFile.Write(testsRaw)
}

func GenerateBenchmarks() {
	sizeCases := []int{10000, 25000, 50000, 100000, 150000, 300000, 500000}
	sortBenchData := &SortBenchData{
		Cases:   make([][]int, 0, len(sizeCases)),
		Answers: make([][]int, 0, len(sizeCases)),
	}

	for _, size := range sizeCases {
		// Generate answer slice
		answer := make([]int, size)
		data := make([]int, size)

		for i := 0; i < size; i++ {
			answer[i] = i
		}

		copy(data, answer)

		// Shuffle answer and geenrate case
		rand.Shuffle(size, func(i, j int) { data[i], data[j] = data[j], data[i] })
		sortBenchData.Cases = append(sortBenchData.Cases, data)
		sortBenchData.Answers = append(sortBenchData.Answers, answer)
	}

	// Marchall all tests into json file
	benchRaw, err := json.Marshal(sortBenchData)
	if err != nil {
		panic(err)
	}

	outputFile, err := os.Create(BenchFilePath)
	if err != nil {
		panic(err)
	}

	outputFile.Write(benchRaw)
}
