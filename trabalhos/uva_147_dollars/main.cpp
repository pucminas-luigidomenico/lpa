#include <cmath>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unsigned long long countWays(short amount, vector<short>::size_type index,
                        vector<short> coins, unordered_map<short, unsigned long long[11]> *ways) {
    unsigned long long result;

    if (amount == 0) {
        result = 1;
    } else if (index >= coins.size() || amount < 0) {
        result = 0;
    } else if ((*ways)[amount][index] != 0) {
        result = (*ways)[amount][index];
    } else {
        result = countWays(amount - coins[index], index, coins, ways);
        result += countWays(amount, index + 1, coins, ways);
    }

    if (amount > 0 && result > (*ways)[amount][index]) {
        (*ways)[amount][index] = result;
    }

    return result;
}

int main() {
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);

    const vector<short> COINS({10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5});

    // Create a hashmap/unordered_map to store amounts and their ways of being built.
    unordered_map<short, unsigned long long[11]> ways;

    float amount;
    cin >> amount;

    while (amount != 0) {
        unsigned long long count = countWays((short) round(amount * 100), 0, COINS, &ways);
        cout << fixed << setprecision(2) << setw(6) << amount;
        cout << setw(17) << count << endl;

        cin >> amount;
    }

    return 0;
}