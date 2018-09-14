#include <iostream>
#include <queue>
#include <tr1/unordered_map>
#include <sstream>

using namespace std;

class Board {
private:
    int emptyX;
    int emptyY;
    vector<int> moveX;
    vector<int> moveY;
    vector<string> state;

public:
    Board();
    Board(const vector<string> &state, const int &emptyX, const int &emptyY,
          const vector<int> &moveX, const vector<int> &moveY);
    string getKey();
    vector<Board> getAdjacents();
};

Board::Board() : state(), moveX(), moveY() {
    this->emptyX = 0, this->emptyY = 0;
}

Board::Board(const vector<string> &state, const int &emptyX, const int &emptyY,
             const vector<int> &moveX, const vector<int> &moveY) {
    this->state = state;
    this->moveX = moveX;
    this->moveY = moveY;
    this->emptyX = emptyX;
    this->emptyY = emptyY;
}

string Board::getKey() {
    string key = state[0];
    for (size_t i = 1; i < state.size(); i++) {
        key += state[i];
    }

    return key;
}

vector<Board> Board::getAdjacents() {
    vector<Board> adjacents;

    for (size_t i = 0; i < this->moveX.size(); i++) {
        int newEmptyX = this->emptyX + this->moveX[i];
        int newEmptyY = this->emptyY + this->moveY[i];

        if (newEmptyX >= 0 && newEmptyX < this->state.size() && newEmptyY >= 0 && newEmptyY < this->state.size()) {
            Board tmp = Board(this->state, newEmptyX, newEmptyY, this->moveX, this->moveY);
            tmp.state[this->emptyX][this->emptyY] = this->state[newEmptyX][newEmptyY];
            tmp.state[newEmptyX][newEmptyY] = this->state[this->emptyX][this->emptyY];
            adjacents.push_back(tmp);
        }
    }

    return adjacents;
}

int main() {
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);

    string tmp[] = {"11111", "01111", "00 11", "00001", "00000"};
    vector<string> finalState(tmp, tmp + sizeof(tmp) / sizeof(string));

    int tmpX[] = {-1, -1, 1, 1, -2, -2, 2, 2};
    int tmpY[] = {-2, 2, -2, 2, -1, 1, -1, 1};
    vector<int> moveX(tmpX, tmpX + sizeof(tmpX) / sizeof(int));
    vector<int> moveY(tmpY, tmpY + sizeof(tmpY) / sizeof(int));

    Board board = Board(finalState, 2, 2, moveX, moveY);

    tr1::unordered_map<string, int> depths;
    queue<Board> states;

    states.push(board);
    depths[board.getKey()] = 1;

    while (!states.empty()) {
        board = states.front();
        states.pop();

        int currentDepth = depths[board.getKey()];

        // depth - 1 is a workaround for default value of unordered_map, which is 0
        if (currentDepth - 1 < 11) {
            vector<Board> adjacents = board.getAdjacents();
            for (size_t i = 0; i < adjacents.size(); i++) {
                if (depths.find(adjacents[i].getKey()) == depths.end()) {
                    states.push(adjacents[i]);
                    depths[adjacents[i].getKey()] = currentDepth + 1;
                }
            }
        }
    }

    string row;
    getline(cin, row);

    int numSets = 0;
    istringstream buffer(row);
    buffer >> numSets;

    for (int i = 0; i < numSets; i++) {
        vector<string> state;

        for (int j = 0; j < 5; j++) {
            // Read entire line and ignore extra whitespaces
            getline(cin, row);
            row = row.substr(0, 5);

            // Fill board state with rows
            state.push_back(row);
        }

        // Create a new Board just to get the key.
        board = Board(state, -1, -1, moveX, moveY);
        string key = board.getKey();
        int depth = depths[key] - 1;

        if (depth < 0 || depth >= 11) {
            cout << "Unsolvable in less than 11 move(s)." << endl;
        } else {
            cout << "Solvable in " << depth << " move(s)." << endl;
        }
    }

    return 0;
}
