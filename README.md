# Content
- [Content](#content)
- [Brief Description](#brief-description)
- [Project purpose](#project-purpose)
- [Languages](#languages)
- [Implementation Details](#implementation-details)
  - [Algorithms](#algorithms)
    - [Bubble Sort](#bubble-sort)
    - [Selection Sort](#selection-sort)
  - [Data Structures](#data-structures)
    - [Go](#go)
- [Benchmarks](#benchmarks)
  - [Go](#go-1)
- [Progress](#progress)
# Brief Description
Sort Research project is a collection of sorting algorithms written in different programming languages and their benchmark results.
# Project purpose
The main purpose of this project is to write most of popular sorting algorithms to study them, and find out their difference when being implemented on different languages and additionally collect benchmark results and put them into one table, so it will be easy to compare them. For simplicity (maybe in future it will be changed) only integers are sorted. The list of used languages for now you can find in section [Languages](#languages). Obviously, it is important to use exactly same algorithms and most alike data structures in code, so it is closely discussed in section [Implementation Details](#implementation-details).
# Languages
Here is the list of already implemented/being implemented languages and also planned ones.

- [x] Go
- [ ] C
- [ ] C++
- [ ] Python
- [ ] Java
# Implementation Details
Benchmarks require algorithms to be implemented in the same way and with similiar data structures to be more accurate. For convenience, here are all algorithms (brief description, complexity, pseudo-code) and data structures used in the project.
## Algorithms
### **Bubble Sort**

*Time complexity: O(N^2)*

*Space complexity: O(1)*

Iterate through array and swap adjacent elements if they are not on their place.
```
for i from 0 to N {
    for j from i + 1 to N {
        if a[i] < a[j]
            swap(a[i], a[j])
    }
}
``` 
### **Selection Sort**

*Time complexity: O(N^2)*

*Space complexity: O(1)*

Iterate through array, repeatedly find minimum element and put it into the beggining of the array
```
for i from 0 to N {
    min = a[i]
    for j from i + 1 to N {
        find min
        swap(a[i], min)
    }
}
```
## Data Structures
### Go
Slices are used for storing array. Benchmarking and testing is done with built-in tools (*testing* package).
# Benchmarks
Test data for benchmarking is generated with *Go* and stored in JSON files: arrays of 50000, 200000 and 500000 elements generated with *rand* package. All benchmarks are done on AMD Ryzen 5 4600H CPU on Windows 10.
## Go
```
goos: windows
goarch: amd64
pkg: sorting
cpu: AMD Ryzen 5 4600H with Radeon Graphics
BenchmarkSort/stdSort/size=50000-12                   98          12374681 ns/op         1201499 B/op     100004 allocs/op
BenchmarkSort/stdSort/size=200000-12                  20          53812840 ns/op         4805788 B/op     400004 allocs/op
BenchmarkSort/stdSort/size=500000-12                   8         140061350 ns/op        12005969 B/op    1000004 allocs/op
BenchmarkSort/bubbleSort/size=50000-12                 1        3483853100 ns/op         1201456 B/op     100003 allocs/op
BenchmarkSort/bubbleSort/size=200000-12                1        58524585100 ns/op        4805680 B/op     400003 allocs/op
BenchmarkSort/bubbleSort/size=500000-12                1        367494278300 ns/op      12005936 B/op    1000003 allocs/op
BenchmarkSort/selectionSort/size=50000-12              2         959697300 ns/op         1201460 B/op     100003 allocs/op
BenchmarkSort/selectionSort/size=200000-12             1        15385728800 ns/op        4805680 B/op     400003 allocs/op
BenchmarkSort/selectionSort/size=500000-12             1        96640515300 ns/op       12005944 B/op    1000004 allocs/op
PASS
ok      sorting 550.166s
```
# Progress
Project is in early development.
