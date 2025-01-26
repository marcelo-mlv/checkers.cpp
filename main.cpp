#include "classes/board.cpp"
#include <stdlib.h>

int main() {
    Board x;

    while(x.checkEndgame() == NONE) {
        std::cout << x;
        x.playTurn();
    }

    system("pause");

    return 0;
}