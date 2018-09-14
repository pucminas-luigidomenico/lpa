//
// Created by luigi on 26/02/2018.
//

#ifndef UVA_10608_FRIENDS_DISJOINTSET_H
#define UVA_10608_FRIENDS_DISJOINTSET_H

#include <vector>

class DisjointSet {
private:
    std::vector<unsigned short> parents;
    std::vector<unsigned short> rank;
    std::vector<unsigned short> setSizes;

public:
    explicit DisjointSet(unsigned short size);
    unsigned short find(unsigned short i);
    unsigned short merge(unsigned short i, unsigned short j);

};

#endif //UVA_10608_FRIENDS_DISJOINTSET_H
