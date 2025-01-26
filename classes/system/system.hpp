#include "../game/game.cpp"

class System {
    private:
        Color checkEndgame(Game& game);
        int total_wins[2];
        
    public:
        void newGame();

        // increases the win count for the given color
        void increaseWinCount(Color p) { total_wins[p]++; }

        // constructor declaration
        System();
};
