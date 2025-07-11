# Snake Game 🐍

This is a simple ai snake game using Greedy algorithm. 
If you want to control manually, you can adjust the ai_moving() in snake.cpp, I had already written.

## Intro

- When the program get started, the snake will keep moving automatically.
- When the snake eats a fruit(@) or keep moving for five steps, the fruit will generate randomly. 
- When it crash itself our the wall, the game will end.
- At the end, it will show the score.

## Complie

Please complie by g++：

```bash
g++ main.cpp snake.cpp -o snake
./snake
```

## Project Structure
- [main.cpp](./main.cpp)        - main function
- [snake.cpp](./snake.cpp)      - Snake game logic implementation
- [snake.hpp](./snake.hpp)      - Snake class declarations



