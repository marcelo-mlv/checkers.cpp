#include "constants.hpp"

class Board {
    private:
        int total_moves;
        int total_wins[2];
        int total_pieces[2];
        std::vector<Move> move_history;
        Color grid[8][8];

        // overloads the << operator to print the board
        friend std::ostream& operator<<(std::ostream& os, const Board& board);

        // gets move input from the user and validates it
        Move getMove(Color currentColor);

        void decreaseTotalPieces(Color p) { total_pieces[p]--; }
        void increaseTotalMoves() { total_moves++; }
        std::vector<pos> getPieceMoves(pos piece_pos, Color currentColor);

    public:
        // checks if the game has ended by checking if one of the players has no pieces left
        Color checkEndgame();

        // determines the current player's turn based on the total number of moves
        Color getColorTurn() const { return total_moves % 2 == 0 ? black : white; }

        // executes a turn by moving a piece according to the current player's input
        void playTurn();

        // increases the win count for the given color
        void increaseWinCount(Color p) { total_wins[p]++; }

        // constructor declaration
        Board();
};
