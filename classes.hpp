#include <iostream>

const char visuals[3] = {'w', 'b', ' '};

enum Color {
    white,
    black,
    NONE
};

struct Move {
    int startX, startY, endX, endY;
};

class Board {
    private:
        int total_moves;
        int total_wins[2];
        int total_pieces[2];
        Color grid[8][8];

        friend std::ostream& operator<<(std::ostream& os, const Board& board);
        Move getMove(Color currentColor);
        Color getCurrentColorTurn() { return total_moves % 2 == 0 ? black : white; }
        bool checkEndgame() {return total_pieces[white] == 0 || total_pieces[black] == 0;}
        void decreasePieceCount(Color p) { total_pieces[p]++; }
        void increaseTotalMoves() { total_moves++; }
    public:
        void playTurn();
        Board();
        void increaseWinCount(Color p) { total_wins[p]++; }
};

Board::Board() {
    total_moves = 0;
    total_wins[white] = 0;
    total_wins[black] = 0;

    total_pieces[white] = 0;
    total_pieces[black] = 0;
    
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

void Board::playTurn() {
    Color currentColor = getCurrentColorTurn();
    struct Move current_move = getMove(currentColor);

    grid[current_move.startY][current_move.startX] = NONE;
    grid[current_move.endY][current_move.endX] = currentColor;

    increaseTotalMoves();
}

Move Board::getMove(Color currentColor) {
    std::cout << "Type the coordinates of the piece you would like to move (e.g., a1): ";
    char startX, endX;
    int startY, endY;
    std::cin >> startX >> startY;
    std::cout << "Type the coordinates of destination (e.g., b2): ";
    std::cin >> endX >> endY;
    return {startX - 'a', startY - 1, endX - 'a', endY - 1};
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(int i = 0; i < 8; i++) {
        os << i+1 << "  ";
        for(int j = 0; j < 8; j++)
            os << static_cast<char>(visuals[board.grid[i][j]]) << " "; 
        os << std::endl; 
    }
    os << "   a b c d e f g h" << std::endl;
    return os;
}
