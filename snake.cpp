#include "snake.hpp"
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <algorithm>

bool window:: get_status(){
    return status;
}

int window:: getscore(){
    return score;
} 

void window:: init(SnakeMove &s){
    status = true;
    for (int i = 0; i < length; i++){
        for (int j = 0; j < width; j++){
            if (i == 0 || j == 0 || j == width - 1 || i == length - 1) {
                _map[i][j] = '#';
            }else{
                _map[i][j] = ' ';
            }
        }
    }

    s.head_x = width / 2;
    s.head_y = length / 2;
    
    s.body.clear();
    s.body.push_back({s.head_x, s.head_y});
    s.body.push_back({s.head_x - 1, s.head_y});

    _map[s.head_y][s.head_x] = 'O';
    _map[s.head_y][s.head_x - 1] = 'o';
    generate_fruit();


}

void window:: print_out(){
    system("cls");
    for (int i = 0; i < length; i++){
        for (int j = 0; j < width; j++){
            cout << _map[i][j];
        }
        cout << "\n";
    }
}

void window:: generate_fruit(){
    while(1){
        int x = rand() % width;
        int y = rand() % length;

        if (_map[y][x] == ' '){
            _map[y][x] = '@';
            fruits.push_back(make_pair(x,y));
            break;
        }   
        
    }
    
}

void window::update(SnakeMove &m){

    switch (m.direction){
            case 'w': m.head_y --; break;
            case 'a': m.head_x --; break;
            case 's': m.head_y ++; break;
            case 'd': m.head_x ++; break;
    }

    // hit the wall
    if (m.head_x <= 0 || m.head_x >= width - 1 || m.head_y <= 0 || m.head_y >= length - 1){
        status = false;
        return;
    }
    // hit itself
    if (_map[m.head_y][m.head_x] == 'o'){
        status = false;
        return;
    }
    // eat fruit
    bool ate = (_map[m.head_y][m.head_x] == '@');
    auto it = find(fruits.begin(), fruits.end(), make_pair(m.head_x, m.head_y));
    if (it != fruits.end()) fruits.erase(it);

    m.body.insert(m.body.begin(), {m.head_x, m.head_y});
    _map[m.head_y][m.head_x] = 'O';

     if (m.body.size() >= 2) {
        auto second = m.body[1];
        _map[second.second][second.first] = 'o';
    }

    if (!ate) {
        auto tail = m.body.back();
        _map[tail.second][tail.first] = ' ';
        m.body.pop_back();
    } else {
        score++;
        generate_fruit();
    }
    step ++;
    if (step % 5 == 0) generate_fruit();
    print_out();
}

void SnakeMove::ai_moving(window &game){
    if (game.fruits.empty()) return;

    int min_dist = 1e9;
    int target_x = head_x, target_y = head_y;
    
    for (auto &f: game.fruits){
        int dist = abs(f.first - head_x) + abs(f.second - head_y);
        if (dist < min_dist){
            min_dist = dist;
            target_x = f.first;
            target_y = f.second;
        }
    }
    // prediction
    vector<pair<char, pair<int, int>>> dirs = {
        {'d', {head_x + 1, head_y}},
        {'a', {head_x - 1, head_y}},
        {'s', {head_x, head_y + 1}},
        {'w', {head_x, head_y - 1}}
    };

    for (size_t i = 0; i < dirs.size(); ++i){
        char dir = dirs[i].first;
        int nx = dirs[i].second.first;
        int ny = dirs[i].second.second;

        // 180 degrees
        if ((direction == 'w' && dir == 's') ||
            (direction == 's' && dir == 'w') ||
            (direction == 'a' && dir == 'd') ||
            (direction == 'd' && dir == 'a')) continue;

        if (nx <= 0 || nx >= 39 || ny <= 0 || ny >= 39) continue;
        if (game._map[ny][nx] == 'o' || game._map[ny][nx] == '#') continue;

        if (abs(target_x - nx) + abs(target_y - ny) < min_dist){
            direction = dir;
            break;
        }
    }
}
void SnakeMove::moving(window &game){
    while (game.get_status()){
        /*if (_kbhit()){
            char c = _getch();
            // cannot turn 180 degree
            switch(c){
                case 'w' : case 'W':
                    if (direction != 's') direction = 'w';
                    break;
                case 'a' : case 'A':
                    if (direction != 'd') direction = 'a';
                    break;
                case 's' : case 'S':
                    if (direction != 'w') direction = 's';
                    break;
                case 'd' : case 'D':
                    if (direction != 'a') direction = 'd';
                    break;
            }*/
            ai_moving(game);
            game.update(*this);
            Sleep(120);
        }
        
    
        cout << "Score: " << game.getscore() << "\n";
        cout << "Game Over\n";
}

