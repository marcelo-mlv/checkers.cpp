#include "../../utils/constants.hpp"

class Game {
    private: 
        int total_moves;
        int total_pieces[2];
        std::vector<Move> move_history;
        Color board[8][8];

        // overloads the << operator to print the board
        friend std::ostream& operator<<(std::ostream& os, const Game& board);

        // gets move input from the user and validates it
        Move getMove(Color currentColor);

        void decreaseTotalPieces(Color p) { total_pieces[p]--; }
        void increaseTotalMoves() { total_moves++; }

        // returns all possible moves from a given piece
        // them moves are determined based on the current position of the piece and its color
        std::vector<Pos> getPieceMoves(Pos piece_pos, Color currentColor);
    public:
        // determines the current player's turn based on the total number of moves
        Color getColorTurn() const { return total_moves % 2 == 0 ? black : white; }

        // executes a turn by moving a piece according to the current player's input
        void playTurn();

        // returns the total number of pieces of a given color
        int getTotalPieces(Color p) const { return total_pieces[p]; }

        // constructor declaration
        Game();
};
