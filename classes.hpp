#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <stdlib.h>

const char visuals[3] = {'w', 'b', ' '};
const std::string colors[3] = {"white", "black", " "};

// list of all values a position on grid can assume
enum Color {
    white,
    black,
    NONE
};

struct pos {
    int x;
    int y;

    friend std::ostream& operator<<(std::ostream& os, const pos& position) {
        os << char(position.x + 'a') << position.y + 1 <<  ", (" << position.x << ", " << position.y << ")";
        return os;
    }
};

// the variables correspond to the respective indexation at grid. e.g, b3 to a4 would correspond to [1][4] to [0][5]
struct Move {
    int startX;
    int startY;
    int endX;
    int endY;
};

class Board {
    private:
        int total_moves;
        int total_wins[2];
        int total_pieces[2];
        std::vector<Move> move_history;
        Color grid[8][8];

        friend std::ostream& operator<<(std::ostream& os, const Board& board);
        Move getMove(Color currentColor);
        void decreasePieceCount(Color p) { total_pieces[p]++; }
        void increaseTotalMoves() { total_moves++; }
        std::vector<pos> getPieceMoves(pos piece_pos, Color currentColor);
    public:
        bool checkEndgame() const {return total_pieces[white] == 0 || total_pieces[black] == 0;}
        Color getColorTurn() const { return total_moves % 2 == 0 ? black : white; }
        void playTurn();
        Board();
        void increaseWinCount(Color p) { total_wins[p]++; }
};

// board class constructor
Board::Board() {
    total_moves = 0;
    total_wins[white] = 0;
    total_wins[black] = 0;

    total_pieces[white] = 0;
    total_pieces[black] = 0;
    
    // initializes as empty board
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            grid[i][j] = NONE;
    
    // generates black/white pieces
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            int exp = 2*j+(i+1)%2;
            grid[i][exp] = black;
            grid[7-i][7-exp] = white;
        }
    }
}

// changes a given piece's position on the board
void Board::playTurn() {
    Color currentColor = getColorTurn();
    struct Move current_move = getMove(currentColor);

    grid[current_move.startY][current_move.startX] = NONE;
    grid[current_move.endY][current_move.endX] = currentColor;
    move_history.push_back(current_move);

    increaseTotalMoves();
}

// return all possible moves from a given piece (no captures for now)
std::vector<pos> Board::getPieceMoves(pos piece_pos, Color currentColor) {
    std::vector<pos> possible_moves;
    int dir = currentColor == black ? 1 : -1;

    if(piece_pos.y + dir < 0 || piece_pos.y + dir > 7)
        return possible_moves;

    if(piece_pos.x != 7 && grid[piece_pos.y + dir][piece_pos.x + 1] == NONE)
        possible_moves.push_back({piece_pos.x + 1, piece_pos.y + dir});

    if(piece_pos.x != 0 && grid[piece_pos.y + dir][piece_pos.x - 1] == NONE)
        possible_moves.push_back({piece_pos.x - 1, piece_pos.y + dir});

    return possible_moves;
}

// gets move input from user
Move Board::getMove(Color currentColor) {
    std::cout << "Type the coordinates of the piece you would like to move (e.g., a1): ";
    char startX, endX;
    int startY, endY;
    std::cin >> startX >> startY;

    // clears input and checks if it is a valid position
    if(std::cin.fail() || startY < 1 || startY > 8 || startX < 'a' || startX > 'h' || grid[startY - 1][startX - 'a'] != currentColor) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try again." << std::endl;
        
        system("pause");
        system("cls");
        std::cout << *this;
        return getMove(currentColor);
    }

    std::vector<pos> possible_moves = getPieceMoves({startX - 'a', startY - 1}, currentColor);

    if (possible_moves.size() == 0) {
        std::cout << "No possible moves for this piece. Try again." << std::endl;

        system("pause");
        system("cls");
        std::cout << *this;
        return getMove(currentColor);
    }

    std::cout << "Type the coordinates of destination (e.g., b2): ";
    std::cin >> endX >> endY;

    bool valid = false;
    for(int i = 0; i < possible_moves.size(); i++)
        if(possible_moves[i].x == endX - 'a' && possible_moves[i].y == endY - 1)
            valid = true;

    // clears input and checks if it is a valid position
    if(std::cin.fail() || !valid) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try again." << std::endl;

        system("pause");
        system("cls");
        std::cout << *this;
        return getMove(currentColor);
    }

    system("cls");

    // converts variables for the move struct
    return {startX - 'a', startY - 1, endX - 'a', endY - 1};
}

// overloads the << operator to print the board
std::ostream& operator<<(std::ostream& os, const Board& board) {
    os << "=-= " << colors[board.getColorTurn()] << " turn " << "=-=" << std::endl;
    for(int i = 0; i < 8; i++) {
        os << i+1 << "  ";
        for(int j = 0; j < 8; j++)
            os << static_cast<char>(visuals[board.grid[i][j]]) << " "; 
        os << std::endl; 
    }
    os << "   a b c d e f g h" << std::endl;
    return os;
}
