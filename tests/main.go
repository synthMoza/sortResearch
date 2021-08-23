package main

import (
	"tests/testgen"
)

func main() {
	testgen.GenerateTests()
	testgen.GenerateBenchmarks()
}
