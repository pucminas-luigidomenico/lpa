#include <iostream>
#include "DisjointSet.h"

using namespace std;

int main()  {
    //freopen("input.in", "r", stdin);
    //freopen("output.out", "w", stdout);

    unsigned short numTests = 0;

    cin >> numTests;
    for (unsigned short i = 0; i < numTests; i++) {
        unsigned short numCitizens = 0;
        unsigned short numPairs = 0;
        unsigned short maxGroup = 1;

        cin >> numCitizens;
        cin >> numPairs;

        DisjointSet set(numCitizens);

        for (unsigned short j = 0; j < numPairs; j++) {
            auto firstPerson = static_cast<unsigned short>(-1);
            auto secondPerson = static_cast<unsigned short>(-1);

            cin >> firstPerson;
            cin >> secondPerson;

            firstPerson--;
            secondPerson--;

            unsigned short sizeGroup = set.merge(firstPerson, secondPerson);
            maxGroup = max(maxGroup, sizeGroup);
        }

        cout << maxGroup << endl;
    }

    return 0;
}