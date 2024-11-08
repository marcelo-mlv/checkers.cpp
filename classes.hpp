#include <iostream>

const char visuals[3] = {'w', 'b', ' '};

enum Piece {
    white,
    black,
    NONE
};

class Board {
    private:
        friend std::ostream& operator<<(std::ostream& os, const Board& board);
        Piece grid[8][8];
        int n_wins[2];
    public:
        Board();
};

Board::Board() {
    n_wins[white] = 0;
    n_wins[black] = 0;
    
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            grid[i][j] = NONE;
    
    // Generating black/white pieces
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            int exp = 2*j+(i+1)%2;
            grid[i][exp] = black;
            grid[7-i][7-exp] = white;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
            os << static_cast<char>(visuals[board.grid[i][j]]) << " "; 
        os << std::endl; 
    }
    return os;
}
