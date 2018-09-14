#include <climits>
#include <iostream>
#include <queue>
#include <vector>

enum SquareValue {
    EMPTY,
    LIT,
    LAMP,
    BLOCKED
};

enum BarrierValue {
    ANY = -1,
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR
};

struct Square {
    bool isBarrier;
    union {
        int square;
        int barrier;
    };
};

class Board {
public:
    Board(int numRows, int numCols);
    bool isFullyLit() const;
    bool isValidBarrier(int row, int col) const;
    bool isAllBarriersValid() const;
    bool isWinningConfig() const;
    bool blockAround(int row, int col);
    bool insertLamp(int row, int col);
    std::vector<Board> lightUpBarrierOne(int row, int col) const;
    std::vector<Board> lightUpBarrierTwo(int row, int col) const;
    std::vector<Board> lightUpBarrierThree(int row, int col) const;
    std::vector<Board> lightUpBarrierFour(int row, int col) const;
    void show() const;
    
    const int getNumLamps() const {
        return numLamps;
    }
    
    std::vector<std::vector<Square> > getBoard() const {
        return board;
    }
    
    std::vector<Square> operator [](int row) const {
        return board[row];
    }
    
    std::vector<Square> &operator [](int row) {
        return board[row];
    }
    
    
private:
    std::vector<std::vector<Square> > board;
    int numLamps;
};

Board::Board(int numRows, int numCols) :
        board(numRows, std::vector<Square>(numCols)) {
 
    numLamps = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            board[i][j].isBarrier = false;
            board[i][j].square = EMPTY;
        }
    }
}

bool Board::isFullyLit() const {
    bool isFullyLit = true;
    
    for (int i = 0; i < board.size() && isFullyLit; i++) {
        for (int j = 0; j < board[i].size() && isFullyLit; j++) {
            if (!board[i][j].isBarrier) {
                isFullyLit = board[i][j].square == LIT;
                isFullyLit = isFullyLit || board[i][j].square == LAMP;
            }
        }
    }
    
    return isFullyLit;
}

bool Board::isValidBarrier(int row, int col) const {
    if (row < 0 
            || row >= board.size() 
            || col < 0
            || col >= board[row].size()
            || !board[row][col].isBarrier) {
                
        return false;
    }
    
    // If it is a barrier of type ANY, return true
    if (board[row][col].barrier == ANY) {
        return true;
    }
    
    int lampsAround = 0;
    // At top
    if (row - 1 >= 0 
            && !board[row - 1][col].isBarrier
            && board[row - 1][col].square == LAMP) {
        lampsAround++;
    }
    
    // At right
    if (col + 1 < board[row].size() && !board[row][col + 1].isBarrier 
            && board[row][col + 1].square == LAMP) {
        lampsAround++;
    }
    
    // At bottom
    if (row + 1 < board.size() && !board[row + 1][col].isBarrier 
            && board[row + 1][col].square == LAMP) {
        lampsAround++;
    }
                    
    // At left
    if (col - 1 >= 0 && !board[row][col - 1].isBarrier 
            && board[row][col - 1].square == LAMP) {
        lampsAround++;
    }
                    
    return board[row][col].barrier == lampsAround;
}

bool Board::isAllBarriersValid() const {
    bool isValid = true;
    
    for (int i = 0; i < board.size() && isValid; i++) {
        for (int j = 0; j < board[i].size() && isValid; j++) {
            if (board[i][j].isBarrier && !isValidBarrier(i, j)) {
                isValid = false;
            }
        }
    }
    
    return isValid;
}


bool Board::isWinningConfig() const {
    bool isWinningConfig = true;
    
    if (!isFullyLit()) {
        isWinningConfig = false;
    } else if (!isAllBarriersValid()) {
        isWinningConfig = false;
    }
    
    return isWinningConfig;
}

bool Board::blockAround(int row, int col) {
    // If it's not a barrier of value zero, return false
    if (!board[row][col].isBarrier || board[row][col].barrier != ZERO) {
        return false;
    }
    
    // At top
    if (row - 1 >= 0 && !board[row - 1][col].isBarrier 
            && board[row - 1][col].square == EMPTY) {
        board[row - 1][col].square = BLOCKED;
    }
    
    // At right
    if (col + 1 < board[row].size() && !board[row][col + 1].isBarrier 
            && board[row][col + 1].square == EMPTY) {
        board[row][col + 1].square = BLOCKED;
    }
    
    // At bottom
    if (row + 1 < board.size() && !board[row + 1][col].isBarrier 
            && board[row + 1][col].square == EMPTY) {
        board[row + 1][col].square = BLOCKED;
    }
    
    // At left
    if (col - 1 >= 0 && !board[row][col - 1].isBarrier 
            && board[row][col - 1].square == EMPTY) {
        board[row][col - 1].square = BLOCKED;
    }
    
    return true;
}

bool Board::insertLamp(int row, int col) {
    // If is something where we can't insert a lamp, return false
    if (row < 0 
            || row >= board.size()
            || col < 0
            || col >= board[row].size()
            || board[row][col].isBarrier
            || board[row][col].square == BLOCKED 
            || board[row][col].square == LIT
            || board[row][col].square == LAMP) {
                
        return false;
    }
    
    // Insert the new lamp
    board[row][col].square = LAMP;
    numLamps++;
    
    // Light up the row
    for (int i = col - 1; i >= 0 && !board[row][i].isBarrier; i--) {
        board[row][i].square = LIT;
    }
    
    for (int i = col + 1; i < board[row].size() && !board[row][i].isBarrier; i++) {
        board[row][i].square = LIT;
    }
    
    // Light up the column
    for (int i = row - 1; i >= 0 && !board[i][col].isBarrier; i--) {
        board[i][col].square = LIT;
    }
    
    for (int i = row + 1; i < board.size() && !board[i][col].isBarrier; i++) {
        board[i][col].square = LIT;
    }
    
    return true;
}

std::vector<Board> Board::lightUpBarrierOne(int row, int col) const {
    std::vector<Board> vec;
    
    // Top, right, bottom and left
    int adjacency[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    if (!board[row][col].isBarrier || board[row][col].barrier != ONE) {
        return vec;   
    }
    
    for (int i = 0; i < 4; i++) {
        Board tmp = *this;
        int r = row + adjacency[i][0];
        int c = col + adjacency[i][1];
        
        bool inserted = tmp.insertLamp(r, c);
        if (inserted && tmp.isValidBarrier(row, col)) {
            for (int j = (i + 1) % 4; j != i; j = (j + 1) % 4) {
                r = row + adjacency[j][0];
                c = col + adjacency[j][1];
                
                if (r >= 0 && r < board.size() && c >= 0 && c < board[r].size()) {
                    if (!tmp[r][c].isBarrier && tmp[r][c].square == EMPTY) {
                        tmp[r][c].square = BLOCKED;            
                    }
                }
            }
            
            vec.push_back(tmp);
        }
    }

    return vec;
}

std::vector<Board> Board::lightUpBarrierTwo(int row, int col) const {
    std::vector<Board> vec;
    
    // Top, right, bottom and left
    int adjacency[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    // Based on positions of adjacency array
    // Top - right, top - bottom, top - left
    // Right - bottom, right - left
    // Bottom - left
    int possib[6][2] = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
    
    if (!board[row][col].isBarrier || board[row][col].barrier != TWO) {
        return vec;   
    }
    
    for (int i = 0; i < 6; i++) {
        Board tmp = *this;
        
        int r1 = row + adjacency[possib[i][0]][0];
        int c1 = col + adjacency[possib[i][0]][1];
        
        int r2 = row + adjacency[possib[i][1]][0];
        int c2 = col + adjacency[possib[i][1]][1];
        
        bool inserted1 = tmp.insertLamp(r1, c1);
        bool inserted2 = tmp.insertLamp(r2, c2);
        
        if ((inserted1 || inserted2) && tmp.isValidBarrier(row, col)) {
            for (int j = 0; j < 4; j++) {
                if (j != possib[i][0] && j != possib[i][1]) {
                    int r = row + adjacency[j][0];
                    int c = col + adjacency[j][1];
                    
                    if (r >= 0 && r < board.size() && c >= 0 && c < board[r].size()) {
                        if (!tmp[r][c].isBarrier && tmp[r][c].square == EMPTY) {
                            tmp[r][c].square = BLOCKED;            
                        }
                    }
                }
            }
            
            vec.push_back(tmp);
        }
    }

    return vec;
}

std::vector<Board> Board::lightUpBarrierThree(int row, int col) const {
    std::vector<Board> vec;
    
    // Top, right, bottom and left
    int adjacency[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    // Based on positions of adjacency array
    // Top - right - bottom, 
    // Top - left - bottom
    // Left - top - right
    // Left - bottom - right
    int possib[4][3] = {{0, 1, 2}, {0, 3, 2}, {3, 0, 1}, {3, 2, 1}};
    
    if (!board[row][col].isBarrier || board[row][col].barrier != THREE) {
        return vec;   
    }
    
    for (int i = 0; i < 4; i++) {
        Board tmp = *this;
        
        int r1 = row + adjacency[possib[i][0]][0];
        int c1 = col + adjacency[possib[i][0]][1];
        
        int r2 = row + adjacency[possib[i][1]][0];
        int c2 = col + adjacency[possib[i][1]][1];
        
        int r3 = row + adjacency[possib[i][2]][0];
        int c3 = col + adjacency[possib[i][2]][1];
        
        bool inserted1 = tmp.insertLamp(r1, c1);
        bool inserted2 = tmp.insertLamp(r2, c2);
        bool inserted3 = tmp.insertLamp(r3, c3);
        
        if ((inserted1 || inserted2 || inserted3) && tmp.isValidBarrier(row, col)) {
            for (int j = 0; j < 4; j++) {
                if (j != possib[i][0] && j != possib[i][1] && j != possib[i][2]) {
                    int r = row + adjacency[j][0];
                    int c = col + adjacency[j][1];
                    
                    if (r >= 0 && r < board.size() && c >= 0 && c < board[r].size()) {
                        if (!tmp[r][c].isBarrier && tmp[r][c].square == EMPTY) {
                            tmp[r][c].square = BLOCKED;            
                        }
                    }
                }
            }
            
            vec.push_back(tmp);
        }
    }

    return vec;
}

std::vector<Board> Board::lightUpBarrierFour(int row, int col) const {
    std::vector<Board> vec;
    
    // Top, right, bottom and left
    int adjacency[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    
    if (!board[row][col].isBarrier || board[row][col].barrier != FOUR) {
        return vec;   
    }
    
    Board tmp = *this;
    
    // Top, right, bottom and left
    int r1 = row + adjacency[0][0];
    int c1 = col + adjacency[0][1];
    
    int r2 = row + adjacency[1][0];
    int c2 = col + adjacency[1][1];
    
    int r3 = row + adjacency[2][0];
    int c3 = col + adjacency[2][1];
    
    int r4 = row + adjacency[3][0];
    int c4 = col + adjacency[3][1];
    
    bool inserted1 = tmp.insertLamp(r1, c1);
    bool inserted2 = tmp.insertLamp(r2, c2);
    bool inserted3 = tmp.insertLamp(r3, c3);
    bool inserted4 = tmp.insertLamp(r4, c4);
    
    if ((inserted1 || inserted2 || inserted3 || inserted4) 
            && tmp.isValidBarrier(row, col)) {
        vec.push_back(tmp);
    }

    return vec;
}

void Board::show() const {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j].isBarrier) {
                std::cout << board[i][j].barrier;
                
                if (board[i][j].barrier == -1) {
                    std::cout << " ";
                } else {
                    std::cout << "  ";
                }
            } else if (board[i][j].square == EMPTY) {
                std::cout << "E  ";
            } else if (board[i][j].square == BLOCKED) {
                std::cout << "X  ";
            } else if (board[i][j].square == LIT) {
                std::cout << "I  ";
            } else {
                std::cout << "L  ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    // freopen("input.in", "r", stdin);
    // freopen("output.out", "w", stdout);
    
    int numRows, numCols;
    std::cin >> numRows >> numCols;
    
    while (numRows != 0 || numCols != 0) {
        Board board(numRows, numCols);
        int numBarriers;
        std::cin >> numBarriers;
        
        std::vector<std::vector<std::pair<int, int> > > barriers(4);
        for (int i = 0; i < numBarriers; i++) {
            int row, col;
            int barrier;
            
            std::cin >> row >> col >> barrier;
            row--;
            col--;
            
            board[row][col].isBarrier = true;
            board[row][col].barrier = barrier;
            
            if (barrier == 0) {
                board.blockAround(row, col);
            } else if (barrier != -1) {
                barriers[barrier - 1].push_back(std::make_pair(row, col));
            }
        }
    
        std::queue<Board> queue;
        std::queue<Board> auxQueue;
        queue.push(board);
        
        int numLamps = INT_MAX;
        // Light up around every 4-barrier
        while (barriers[3].size() > 0 && !queue.empty()) {
            Board b = queue.front();
            queue.pop();
            
            for (int i = 0; i < barriers[3].size(); i++) {
                Board tmp = b;
                
                int row = barriers[3][i].first;
                int col = barriers[3][i].second;
                
                std::vector<Board> nextStates = tmp.lightUpBarrierFour(row, col);
        
                for (int j = 0; j < nextStates.size(); j++) {
                    queue.push(nextStates[j]);
                    auxQueue.push(nextStates[j]);
                }
            }
        }
        if (!auxQueue.empty()) {
            queue = auxQueue;
            auxQueue = std::queue<Board>();
        }
        
        // Light up around every 3-barrier
        while (barriers[2].size() > 0 && !queue.empty()) {
            Board b = queue.front();
            queue.pop();
            
            for (int i = 0; i < barriers[2].size(); i++) {
                Board tmp = b;
                
                int row = barriers[2][i].first;
                int col = barriers[2][i].second;
                
                std::vector<Board> nextStates = tmp.lightUpBarrierThree(row, col);
        
                for (int j = 0; j < nextStates.size(); j++) {
                    queue.push(nextStates[j]);
                    auxQueue.push(nextStates[j]);
                }
            }
        }
        if (!auxQueue.empty()) {
            queue = auxQueue;
            auxQueue = std::queue<Board>();
        }
        
        // Light up around every 2-barrier
        while (barriers[1].size() > 0 && !queue.empty()) {
            Board b = queue.front();
            queue.pop();
            
            for (int i = 0; i < barriers[1].size(); i++) {
                Board tmp = b;
                
                int row = barriers[1][i].first;
                int col = barriers[1][i].second;
                
                std::vector<Board> nextStates = tmp.lightUpBarrierTwo(row, col);
        
                for (int j = 0; j < nextStates.size(); j++) {
                    queue.push(nextStates[j]);
                    auxQueue.push(nextStates[j]);
                }
            }
        }
        if (!auxQueue.empty()) {
            queue = auxQueue;
            auxQueue = std::queue<Board>();
        }
        
        // Light up around every 1-barrier
        while (barriers[0].size() > 0 && !queue.empty()) {
            Board b = queue.front();
            queue.pop();
            
            for (int i = 0; i < barriers[0].size(); i++) {
                Board tmp = b;
                
                int row = barriers[0][i].first;
                int col = barriers[0][i].second;
                
                std::vector<Board> nextStates = tmp.lightUpBarrierOne(row, col);
        
                for (int j = 0; j < nextStates.size(); j++) {
                    queue.push(nextStates[j]);
                    auxQueue.push(nextStates[j]);
                }
            }
        }
        if (!auxQueue.empty()) {
            queue = auxQueue;
            auxQueue = std::queue<Board>();
        }
        
        while (!queue.empty()) {
            Board b = queue.front();
            queue.pop();
            
            if (b.isWinningConfig() && b.getNumLamps() < numLamps) {
                numLamps = b.getNumLamps();
            }
            
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    Board tmp = b;
                    if (!tmp[i][j].isBarrier 
                            && tmp[i][j].square == EMPTY) {
                        bool inserted = tmp.insertLamp(i, j);
                        
                        if (inserted) {
                            queue.push(tmp);
                        }
                    }
                }
            }
        }
        
        if (numLamps == INT_MAX) {
            std::cout << "No solution" << std::endl;
        } else {
            std::cout << numLamps << std::endl;
        }
        std::cin >> numRows >> numCols;
    }
    
    return 0;
}