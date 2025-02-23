#include <game.hpp>

class System {
    private:
        // checks winning conditions
        Color checkEndgame(Game& game);

        // stores the total wins for each team
        int total_wins[2];
        
        // increases the win count for the given color
        void increaseWinCount(Color p) { total_wins[p]++; }

        // starts the main game loop
        void newGame();

        // initial message
        void welcomeMessage();

    public:
        // constructor declaration
        System();
};
