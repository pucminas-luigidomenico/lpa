package main

import (
	"fmt"
)

type IntMatrix [][]int64
type IntArray []int64

func Max(x, y int64) int64 {
	sub := x - y
	signal := sub >> 31
	max := x - (sub & signal)
	return max
}

func (a IntArray) MaxSum() int64 {
	currSum := a[0]
	maxSum := a[0]

	for i := 1; i < len(a); i++ {
		currSum += a[i]
		currSum = Max(a[i], currSum)
		maxSum = Max(maxSum, currSum)
	}

	return maxSum
}

func (m IntMatrix) MaxSum() int64 {
	mLen := len(m)
	maxSum := m[0][0]

	for i := 0; i < mLen; i++ {
		array := make(IntArray, mLen, mLen)

		for j := i; j < mLen; j++ {
			for k := 0; k < mLen; k++ {
				array[k] += m[j][k]
			}

			sumArray := array.MaxSum()
			maxSum = Max(maxSum, sumArray)
		}
	}

	return maxSum
}

func main() {
	matrix := IntMatrix {{-100, 2, -4}, {-126, -11, -14}, {-88, -76, -13}}
	fmt.Println(matrix.MaxSum())
}