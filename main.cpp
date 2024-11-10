#include <iostream>
#include "classes.hpp"

int main() {
    Board x;
    
    std::cout << x;

    x.playTurn();

    std::cout << x;

    return 0;

}