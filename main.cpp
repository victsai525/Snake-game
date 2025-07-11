#include "snake.hpp"
int main() {
    cout << "Start!\n";
    window game;
    SnakeMove m;
    game.init(m);      
    m.moving(game);     
    return 0;
}
