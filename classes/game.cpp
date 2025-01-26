#include "game.hpp"
#include <stdlib.h>

// Game class constructor
// initializes the board with the starting positions of the pieces and sets the initial game state
Game::Game() {
    total_moves = 0;
    total_wins[white] = 0;
    total_wins[black] = 0;

    total_pieces[white] = 0;
    total_pieces[black] = 0;
    
    // initializes as empty board
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            board[i][j] = NONE;
    
    // generates black/white pieces
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            int exp = 2*j+(i+1)%2;
            board[i][exp] = black;
            board[7-i][7-exp] = white;
            total_pieces[white]++;
            total_pieces[black]++;
        }
    }

    // // endgame test
    // board[4][3] = white;
    // board[3][4] = black;
    // total_pieces[white]++;
    // total_pieces[black]++;

    // game execution
    while(this->checkEndgame() == NONE) {
        std::cout << *this;
        this->playTurn();
    }
    system("pause");
}

Color Game::checkEndgame() {
    if(total_pieces[white] == 0) {
        increaseWinCount(black);
        std::cout << "Black wins!" << std::endl;
        return black;
    }
    if(total_pieces[black] == 0) {
        increaseWinCount(white);
        std::cout << "White wins!" << std::endl;
        return white;
    }
    return NONE;
}

// changes a given piece's position on the board
void Game::playTurn() {
    Color currentColor = getColorTurn();
    struct Move current_move = getMove(currentColor);

    board[current_move.startPos.y][current_move.startPos.x] = NONE;
    board[current_move.endPos.y][current_move.endPos.x] = currentColor;

    if(current_move.startPos.x - current_move.endPos.x == 2 || current_move.startPos.x - current_move.endPos.x == -2) {
        board[(current_move.startPos.y + current_move.endPos.y)/2][(current_move.startPos.x + current_move.endPos.x)/2] = NONE;
        decreaseTotalPieces(currentColor);
    }

    move_history.push_back(current_move);

    increaseTotalMoves();
}

// returns all possible moves from a given piece (no captures for now)
// them moves are determined based on the current position of the piece and its color
std::vector<pos> Game::getPieceMoves(pos piece_pos, Color currentColor) {
    std::vector<pos> possible_moves;
    int dir = currentColor == black ? 1 : -1;

    if(piece_pos.y + dir < 0 || piece_pos.y + dir > 7)
        return possible_moves;

    if(piece_pos.x != 7) {
        if(board[piece_pos.y + dir][piece_pos.x + 1] == NONE)
            possible_moves.push_back({piece_pos.x + 1, piece_pos.y + dir});
        else if(board[piece_pos.y + dir][piece_pos.x + 1] != currentColor)
            if(piece_pos.y + 2*dir >= 0 && piece_pos.y + 2*dir <= 7 && piece_pos.x + 2 <= 7 && board[piece_pos.y + 2*dir][piece_pos.x + 2] == NONE)
                possible_moves.push_back({piece_pos.x + 2, piece_pos.y + 2*dir});
    }

    if(piece_pos.x != 0) {
        if(board[piece_pos.y + dir][piece_pos.x - 1] == NONE)
            possible_moves.push_back({piece_pos.x - 1, piece_pos.y + dir});
        else if(board[piece_pos.y + dir][piece_pos.x - 1] != currentColor)
            if(piece_pos.y + 2*dir >= 0 && piece_pos.y + 2*dir <= 7 && piece_pos.x - 2 >= 0 && board[piece_pos.y + 2*dir][piece_pos.x - 2] == NONE)
                possible_moves.push_back({piece_pos.x - 2, piece_pos.y + 2*dir});
    }

    return possible_moves;
}

// gets move input from user
Move Game::getMove(Color currentColor) {
    std::cout << "Type the coordinates of the piece you would like to move (e.g., a1): ";
    char startX, endX;
    int startY, endY;
    std::cin >> startX >> startY;

    // clears input and checks if it is a valid position
    if(std::cin.fail() || startY < 1 || startY > 8 || startX < 'a' || startX > 'h' || board[startY - 1][startX - 'a'] != currentColor) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try another one." << std::endl;
        
        system("pause");
        system("cls");
        std::cout << *this;
        return getMove(currentColor);
    }

    std::vector<pos> possible_moves = getPieceMoves({startX - 'a', startY - 1}, currentColor);

    if (possible_moves.size() == 0) {
        std::cout << "No possible moves for this piece. Try another one." << std::endl;

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
        std::cout << "Invalid input. Try another one." << std::endl;

        system("pause");
        system("cls");
        std::cout << *this;
        return getMove(currentColor);
    }

    system("cls");

    // converts variables for the move struct
    return {{startX - 'a', startY - 1}, {endX - 'a', endY - 1}};
}

// overloads the << operator to print the board
std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "=-= " << colors[game.getColorTurn()] << " turn " << "=-=" << std::endl;
    for(int i = 0; i < 8; i++) {
        os << i+1 << "  ";
        for(int j = 0; j < 8; j++)
            os << static_cast<char>(visuals[game.board[i][j]]) << " "; 
        os << std::endl; 
    }
    os << "   a b c d e f g h" << std::endl;
    return os;
}
