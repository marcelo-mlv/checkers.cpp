#include "system.hpp"
#include <stdlib.h>

System::System() {
    total_wins[white] = 0;
    total_wins[black] = 0;
}

void System::newGame() {
    Game game;

    // game execution
    while(this->checkEndgame(game) == NONE) {
        std::cout << game;
        game.playTurn();
    }
    system("pause");
}

Color System::checkEndgame(Game &game) {
    if(game.getTotalPieces(white) == 0) {
        increaseWinCount(black);
        std::cout << "Black wins!" << std::endl;
        return black;
    }
    if(game.getTotalPieces(black) == 0) {
        increaseWinCount(white);
        std::cout << "White wins!" << std::endl;
        return white;
    }
    return NONE;
}
