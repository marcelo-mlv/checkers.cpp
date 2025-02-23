#include <system.hpp>
#include <stdlib.h>

// System class constructor
// initializes the total wins for each team and starts a new game
System::System() {
    total_wins[white] = 0;
    total_wins[black] = 0;
    
    welcomeMessage();
    newGame();
}

void System::newGame() {
    Game game;

    // game loop execution
    while(checkEndgame(game) == NONE) {
        std::cout << game;
        game.playTurn();
    }
    system("pause");
}

Color System::checkEndgame(Game &game) {
    if(game.getTotalPieces(white) == 0) {
        std::cout << colors[black] << " wins!" << std::endl;
        increaseWinCount(black);
        return black;
    }
    if(game.getTotalPieces(black) == 0) {
        std::cout << colors[white] << " wins!" << std::endl;
        increaseWinCount(white);
        return white;
    }
    return NONE;
}

void System::welcomeMessage() {
    std::cout << "=-=-=-=-=-=-=-=-=-=-=" << std::endl;
    std::cout << " Welcome to Checkers " << std::endl;
    std::cout << "       C++ nice      " << std::endl;
    std::cout << "=-=-=-=-=-=-=-=-=-=-=" << std::endl;
    system("pause");
    system("cls");
}
