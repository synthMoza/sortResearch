// Implementation of several sorting algorithms in Go.
package sorting

// Sorts the given slice of integer using bubble sort algorithm.
// Brief description: traverse slcie and swap adjacent elements if they are on wrong positions.
func BubbleSort(sl []int) {
	sliceLength := len(sl)

	for i := 0; i < sliceLength; i++ {
		for j := i + 1; j < sliceLength; j++ {
			if sl[j] < sl[i] {
				sl[i], sl[j] = sl[j], sl[i]
			}
		}
	}
}
