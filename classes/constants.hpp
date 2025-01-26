#include <iostream>
#include <vector>
#include <string>
#include <limits>

const char visuals[3] = {'w', 'b', ' '};
const std::string colors[3] = {"white", "black", " "};

// enum of all values a position on grid can assume
enum Color {
    white,
    black,
    NONE
};

// the variables correspond to the respective indexation at grid e.g, b3 is x = 1, y = 2
struct pos {
    int x;
    int y;

    // overloads the << operator to print the position in a readable format
    friend std::ostream& operator<<(std::ostream& os, const pos& position) {
        os << char(position.x + 'a') << position.y + 1 <<  ", (" << position.x << ", " << position.y << ")";
        return os;
    }
};

// struct to store the start and end positions of a move
struct Move {
    pos startPos;
    pos endPos;
};
