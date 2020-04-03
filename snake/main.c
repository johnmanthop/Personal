#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>


#include "board.h"
#include "snake.h"


int main()
{
    struct Board *board = init_board(20, 40);
    struct Snake *snake = init_snake();

    while (1)
    {
        system("cls");
        print(board, snake);
        if (GetAsyncKeyState('W') & 0x8000 && snake->direction != DOWN)
        {
            turn_up(snake);
        }
        else if (GetAsyncKeyState('S') & 0x8000 && snake->direction != UP)
        {
            turn_down(snake);
        }
        else if (GetAsyncKeyState('D') & 0x8000 && snake->direction != LEFT)
        {
            turn_right(snake);
        }
        else if (GetAsyncKeyState('A') & 0x8000 && snake->direction != RIGHT)
        {
            turn_left(snake);
        }
        check_food(board, snake);
        tick(snake);

        if (check_game_over(board, snake) == -1) break;
        //Sleep(500);

    }
    printf("GAME OVER!\nScore:%d\n", snake->count);
    system("pause");
    return 0;
}
