#include <iostream>
#include "classes.hpp"

int main() {
    Board x;

    while(x.checkEndgame()) {
        std::cout << x;
        x.playTurn();
    }

    return 0;
}