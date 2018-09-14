package main

import "fmt"

type DisjointSet struct {
	parents []int
	ranks   []int
	count   []int
}

func (set *DisjointSet) MakeSet(x int) {
	set.parents = append(set.parents, x)
	set.ranks = append(set.ranks, 0)
	set.count = append(set.count, 1)
}

func (set *DisjointSet) Find(x int) int {
	if set.parents[x] != x {
		set.parents[x] = set.Find(set.parents[x])
	}

	return set.parents[x]
}

func (set *DisjointSet) Union(x, y int) int {
	xRoot := set.Find(x)
	yRoot := set.Find(y)

	if xRoot == yRoot {
		return set.count[xRoot]
	}

	count := 1
	if set.ranks[xRoot] < set.ranks[yRoot] {
		set.parents[xRoot] = yRoot
		set.count[yRoot] += set.count[xRoot]
		count = set.count[yRoot]
	} else if set.ranks[yRoot] < set.ranks[xRoot] {
		set.parents[yRoot] = xRoot
		set.count[xRoot] += set.count[yRoot]
		count = set.count[xRoot]
	} else {
		set.parents[xRoot] = yRoot
		set.count[yRoot] += set.count[xRoot]
		set.ranks[yRoot]++
		count = set.count[yRoot]
	}

	return count
}

func main() {
	var numTests int
	fmt.Scanf("%d\n", &numTests)

	for i := 0; i < numTests; i++ {
		var numCitizens int
		var numPairs int
		fmt.Scanf("%d %d\n", &numCitizens, &numPairs)

		disjointSet := DisjointSet{}
		for i := 0; i < numCitizens; i++ {
			disjointSet.MakeSet(i)
		}

		max := 1

		for j := 0; j < numPairs; j++ {
			var x int
			var y int
			fmt.Scanf("%d %d\n", &x, &y)

			x--
			y--

			count := disjointSet.Union(x, y)

			if count > max {
				max = count
			}
		}

		fmt.Println(max)
	}
}
