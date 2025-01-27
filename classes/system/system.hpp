#include "../game/game.cpp"

class System {
    private:
        Color checkEndgame(Game& game);
        int total_wins[2];

        // increases the win count for the given color
        void increaseWinCount(Color p) { total_wins[p]++; }

    public:
        // starts the main game loop
        void newGame();

        // initial message
        void welcomeMessage();

        // constructor declaration
        System();
};
