#ifndef DISJOINT_SET_HPP_
#define DISJOINT_SET_HPP_

#include <vector>

namespace disjointSet {
    /** 
     * A structure to represent a subset for union-find.
     */
    struct Subset {
        int parent;
        int rank;
    };
    
    class DisjointSet {
    public:
        /**
         * Constructor with single parameter that initializes
         * the subset vector according with the maximum number
         * of subsets.
         * 
         * @param std::size_t The maximum number of subsets
         */
        DisjointSet(std::size_t maxNumber);
    
         /**
         * Finds the representive member of the set to which
         * element x belongs, and may be x itself.
         * 
         * Uses path compression as an optimization.
         * 
         * @param int the element we are looking for
         * @return int The representive member of the set to which
         * element x belongs.
         */
        int find(int x);
        
        /**
         * Union function that uses find to determine the roots of
         * the trees x and y belong to. If the roots are distinct,
         * the trees are combined by attaching the root of one to  
         * the root of the other.
         * 
         * Uses union by rank as an optimization.
         *
         * @param int one of the elements that gonna has its subset
         * merged.
         * @param int the other element that gonna has its subset
         * merged.
         */
        void merge(int x, int y);
        
    private:
        std::vector<Subset> subsets;
    };
}

#endif