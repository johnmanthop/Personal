#include <stdio.h>
#include <stdlib.h>


#include "board.h"
#include "snake.h"
#include "l_list.h"

struct Board *init_board(int rows, int cols)
{
    struct Board *board = malloc(sizeof(struct Board));

    board->cols = cols;
    board->rows = rows;

    board->food.i = 10;
    board->food.j = 15;

    return board;
}

void print(struct Board *board, struct Snake *snake)
{
    int i, j;
    for (i = 0; i < board->rows; i++)
    {
        printf("|");
        for (j = 0; j < board->cols; j++)
        {
            if (i == board->food.i && j == board->food.j) printf("*");
            else
            {
                char in_snake = 0;
                do
                {
                    if (i == ((struct Point*)snake->current->data)->i &&
                        j == ((struct Point*)snake->current->data)->j)
                    {
                        in_snake = 1;
                    }
                } while(!traverse_forward(&snake->current));

                printf((in_snake)?"*":" ");
                snake->current = snake->head;
            }
        }
        printf("|\n");
    }
}

void check_food(struct Board *board, struct Snake *snake)
{
    struct Link_Node *temp = snake->current;
    snake->current = snake->head;
    while (snake->current->next) traverse_forward(&snake->current);
    if ( ((struct Point*)snake->current->data)->i == board->food.i &&
         ((struct Point*)snake->current->data)->j == board->food.j) {
        board->food.i = rand() % board->rows;
        board->food.j = rand() % board->cols;
        add_point(snake);
    }
    snake->current = temp;
}

char check_game_over(struct Board *board, struct Snake *snake)
{
    snake->current = snake->head;
    int i = 0, j = 0;
    while (snake->current->next)
    {
        struct List_Node *temp = snake->current;
        j = 0;
        snake->current = snake->head;
        while (snake->current->next)
        {
            if (i != j)
            {
                if (((struct Point*)snake->current->data)->i == ((struct Point*)temp->data)->i &&
                    ((struct Point*)snake->current->data)->j == ((struct Point*)temp->data)->j)
                {
                    snake->current = temp;
                    return -1;
                }
            }
            traverse_forward(&snake->current);
            j++;
        }

        snake->current = temp;
        traverse_forward(&snake->current);
        i++;
    }
    return 0;
}
