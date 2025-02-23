#include <iostream>
#include <vector>
#include <string>

// how the board is displayed in the program
const char visuals[3] = {'w', 'b', ' '};

// each color's name as string
const std::string colors[3] = {"white", "black", " "};

// enum of all values a position on grid can assume
enum Color {
    white,
    black,
    NONE
};

// x, y correspond to the respective indexation at grid
// e.g, b3 <=> x = 1, y = 2
struct Pos {
    int x;
    int y;

    // overloads the << operator to print the position in a readable format
    friend std::ostream& operator<<(std::ostream& os, const Pos& position) {
        os << char(position.x + 'a') << position.y + 1 <<  ", (" << position.x << ", " << position.y << ")";
        return os;
    }
};

// struct to store the start and end positions of a move
struct Move {
    Pos startPos;
    Pos endPos;

    // overloads the << operator to print the move in a readable format
    friend std::ostream& operator<<(std::ostream& os, const Move& move) {
        os << "Move from " << move.startPos << " to " << move.endPos;
        return os;
    }
};
