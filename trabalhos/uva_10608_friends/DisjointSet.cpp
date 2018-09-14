//
// Created by luigi on 26/02/2018.
//

#include "DisjointSet.h"

DisjointSet::DisjointSet(unsigned short size)
        : parents(size, 0),
          rank(size, 0),
          setSizes(size, 1) {
    for (unsigned short i = 0; i < size; i++) {
        parents[i] = i;
    }
}

unsigned short DisjointSet::find(unsigned short i) {
    if (parents[i] != i) {
        parents[i] = find(parents[i]);
    }

    return parents[i];
}

unsigned short DisjointSet::merge(unsigned short i, unsigned short j) {
    unsigned short iRoot = find(i);
    unsigned short jRoot = find(j);

    if (iRoot == jRoot) {
        return setSizes[iRoot];
    }

    unsigned short iRank = rank[iRoot];
    unsigned short jRank = rank[jRoot];
    unsigned short size = 0;

    if (iRank < jRank) {
        parents[iRoot] = jRoot;
        setSizes[jRoot] += setSizes[iRoot];
        size = setSizes[jRoot];
    } else if (iRank > jRank) {
        parents[jRoot] = iRoot;
        setSizes[iRoot] += setSizes[jRoot];
        size = setSizes[iRoot];
    } else {
        parents[iRoot] = jRoot;
        setSizes[jRoot] += setSizes[iRoot];
        size = setSizes[jRoot];
        rank[jRoot]++;
    }

    return size;
}

