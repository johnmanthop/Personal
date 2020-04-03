#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "snake.h"

struct Board
{
    int rows, cols;
    struct Point food;
    //A char 2d pointer would be useless since all characters are ' ' anyway
};

struct Board *init_board (int rows, int cols);
void print(struct Board *board, struct Snake *snake);//Pass by reference for speed

void check_food(struct Board *board, struct Snake *snake);
char check_game_over(struct Board *board, struct Snake *snake);

#endif // BOARD_H_INCLUDED
