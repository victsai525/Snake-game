#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;

class window;

class SnakeMove{
    public:
        // wasd
        char direction = 'd'; // init
        vector <pair<int, int>> body;
        int head_x, head_y;
        void moving(window &game);
        void ai_moving(window &game);
};

class window{
    public:
        // the size of map;
        bool status;
        char _map[40][40];
        vector <pair<int, int>> fruits;
        void print_out();
        void init(SnakeMove &s);
        void generate_fruit();
        void update(SnakeMove &m);
        bool get_status();
        int getscore();
    private:
        long long step = 0;
        int score = 0;
        static const int length = 40;
        static const int width = 40;
        //int fruit_x, fruit_y;
        
};

