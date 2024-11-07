#include <iostream>

const char visuals[3] = {'w', 'b', ' '};

enum Piece {
    white,
    black,
    NONE
};

class Board {
    public:
        Piece grid[8][8];
        int n_wins[2];
        void print_grid();
        friend std::ostream& operator<<(std::ostream& os, const Board& board);
    Board();
};

Board::Board() {
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            grid[i][j] = NONE;
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            int exp = 2*j+(i+1)%2;
            grid[i][exp] = black;
            grid[7-i][7-exp] = white;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    std::cout << std::endl;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
            os << static_cast<char>(visuals[board.grid[i][j]]) << " "; 
        os << std::endl; 
    }
    return os;
}
