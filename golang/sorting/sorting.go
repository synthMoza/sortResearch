// Implementation of several sorting algorithms in Go.
package sorting

// Sorts the given slice of integer using bubble sort algorithm.
// Brief description: traverse slcie and swap adjacent elements if they are on wrong positions.
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
// Brief description: repeatedly look for the minimum element and put it at the start of array
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
