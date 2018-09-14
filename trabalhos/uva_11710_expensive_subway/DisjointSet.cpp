#include "DisjointSet.hpp"

namespace disjointSet {
    DisjointSet::DisjointSet(std::size_t maxNumber)
        : subsets(maxNumber) { 
    
        for (std::size_t i = 0; i < maxNumber; i++) {
            subsets[i].parent = i;
            subsets[i].rank = 0;
        }
    }
        
    int DisjointSet::find(int x) {
        if (subsets[x].parent != x) {
            subsets[x].parent = find(subsets[x].parent);
        }
        
        return subsets[x].parent;
    }
    
    void DisjointSet::merge(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);
        
        if (xRoot == yRoot) {
            return;
        }
        
        if (subsets[xRoot].rank < subsets[yRoot].rank) {
            subsets[xRoot].parent = yRoot;
        } else if (subsets[xRoot].rank > subsets[yRoot].rank) {
            subsets[yRoot].parent = xRoot;
        } else {
            subsets[xRoot].parent = yRoot;
            subsets[yRoot].rank++;
        }
    }
}