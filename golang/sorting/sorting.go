// Implementation of several sorting algorithms in Go.
package sorting

import (
	"sync"
)

// Sorts the given slice of integer using bubble sort algorithm.
func BubbleSort(sl []int) {
	sliceLength := len(sl)

	for i := 0; i < sliceLength-1; i++ {
		for j := 0; j < sliceLength-i-1; j++ {
			if sl[j] > sl[j+1] {
				sl[j], sl[j+1] = sl[j+1], sl[j]
			}
		}
	}
}

// Sorts the given slice of integer using selection algorithm.
func SelectionSort(sl []int) {
	sliceLength := len(sl)

	for i := 0; i < sliceLength; i++ {
		// Find minimum element in slice [i+1:sliceLength]
		minimumIdx := i
		for j := i + 1; j < sliceLength; j++ {
			if sl[j] < sl[minimumIdx] {
				minimumIdx = j
			}
		}

		// Swap these elements
		sl[i], sl[minimumIdx] = sl[minimumIdx], sl[i]
	}
}

// Sorts the given slice of integer using insertion algorithm.
func InsertionSort(sl []int) {
	sliceLength := len(sl)

	for i := 1; i < sliceLength; i++ {
		for j := i - 1; j >= 0; j-- {
			if sl[j] > sl[j+1] {
				sl[j], sl[j+1] = sl[j+1], sl[j]
			} else {
				break
			}
		}
	}
}

// Helper for function for merge sort
func merge(firstHalf []int, secondHalf []int) []int {
	firstHalfLength := len(firstHalf)
	secondHalfLength := len(secondHalf)
	result := make([]int, 0, firstHalfLength+secondHalfLength)

	firstHalfIdx, secondHalfIdx := 0, 0

	// Iterate through both and put smaller value
	for firstHalfIdx < firstHalfLength && secondHalfIdx < secondHalfLength {
		if firstHalf[firstHalfIdx] < secondHalf[secondHalfIdx] {
			result = append(result, firstHalf[firstHalfIdx])
			firstHalfIdx++
		} else {
			result = append(result, secondHalf[secondHalfIdx])
			secondHalfIdx++
		}
	}

	// Pick from first, if left
	for firstHalfIdx < firstHalfLength {
		result = append(result, firstHalf[firstHalfIdx])
		firstHalfIdx++
	}

	// Pick from second, if left
	for secondHalfIdx < secondHalfLength {
		result = append(result, secondHalf[secondHalfIdx])
		secondHalfIdx++
	}

	return result
}

// Sorts the given slice of integer using merge algorithm.
func MergeSort(sl []int) {
	sliceLength := len(sl)
	if sliceLength == 1 {
		return
	}

	var middle int = (sliceLength - 1) / 2

	firstHalf := sl[0 : middle+1]
	secondHalf := sl[middle+1 : sliceLength]

	MergeSort(firstHalf)
	MergeSort(secondHalf)

	copy(sl, merge(firstHalf, secondHalf))
}

// Sorts the given slice of integer using simple parallel merge algorithm.
func MergeSortParallel(sl []int) {
	wg := &sync.WaitGroup{}
	sliceLength := len(sl)
	if sliceLength == 1 {
		return
	}

	var middle int = (sliceLength - 1) / 2

	firstHalf := sl[0 : middle+1]
	secondHalf := sl[middle+1 : sliceLength]

	wg.Add(1)
	go func() {
		defer wg.Done()
		MergeSort(firstHalf)
	}()
	wg.Add(1)
	go func() {
		defer wg.Done()
		MergeSort(secondHalf)
	}()

	wg.Wait()
	copy(sl, merge(firstHalf, secondHalf))
}
