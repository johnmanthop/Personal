#include <stdio.h>
#include <stdlib.h>


#include "snake.h"

#include "l_list.h"


struct Snake *init_snake()
{
    struct Snake *snake = malloc(sizeof(struct Snake));

    snake->head = init_list(sizeof(struct Point));
    snake->current = snake->head;

    struct Point point0 = { 10, 10 };
    struct Point point1 = { 10, 11 };
    struct Point point2 = { 10, 12 };
    struct Point point3 = { 10, 13 };
    set_data(&snake->current, &point0, sizeof(struct Point));

    add_node(&snake->current);
    set_data(&snake->current, &point1, sizeof(struct Point));

    add_node(&snake->current);
    set_data(&snake->current, &point2, sizeof(struct Point));

    add_node(&snake->current);
    set_data(&snake->current, &point3, sizeof(struct Point));


    snake->current = snake->head;
    snake->direction = RIGHT;
    snake->count = 3;

    //Sadly i use the f*cking array notation (rows, cols)
    //Instead of the cartesian (x, y)
    return snake;
}


void turn_right(struct Snake *snake)
{
    snake->direction = RIGHT;
}

void turn_left(struct Snake *snake)
{
    snake->direction = LEFT;
}

void turn_up(struct Snake *snake)
{
    snake->direction = UP;
}

void turn_down(struct Snake *snake)
{
    snake->direction = DOWN;
}

void tick(struct Snake *snake)
{//Here comes the hard part
    struct List_Node *temp = snake->head;

    snake->current = snake->head;
    snake->head = snake->head->next;

    while (snake->current->next) traverse_forward(&snake->current);

    reserve_node(&snake->current);

    temp->next = 0;
    if (snake->direction == RIGHT)
    {
        ((struct Point*)temp->data)->i = ((struct Point*)snake->current->data)->i;
        ((struct Point*)temp->data)->j = ((struct Point*)snake->current->data)->j + 1;
    }
    else if (snake->direction == LEFT)
    {
        ((struct Point*)temp->data)->i = ((struct Point*)snake->current->data)->i;
        ((struct Point*)temp->data)->j = ((struct Point*)snake->current->data)->j - 1;
    }
    else if (snake->direction == UP)
    {
        ((struct Point*)temp->data)->j = ((struct Point*)snake->current->data)->j;
        ((struct Point*)temp->data)->i = ((struct Point*)snake->current->data)->i - 1;
    }
    else if (snake->direction == DOWN)
    {
        ((struct Point*)temp->data)->j = ((struct Point*)snake->current->data)->j;
        ((struct Point*)temp->data)->i = ((struct Point*)snake->current->data)->i + 1;
    }

    snake->current->next = temp;

}

void add_point(struct Snake *snake)
{
    snake->count++;
    struct List_Node *temp = malloc(sizeof(struct List_Node));
    //Spent about 1 hour because i mistyped List as Link.....
    struct Point point = { 0, 0 };
    set_data(&temp, &point, sizeof(struct Point));

    if (snake->direction == RIGHT)
    {
        ((struct Point*)temp->data)->i = ((struct Point*)snake->head->data)->i;
        ((struct Point*)temp->data)->j = ((struct Point*)snake->head->data)->j - 1;
    }
    else if (snake->direction == LEFT)
    {
        ((struct Point*)temp->data)->i = ((struct Point*)snake->head->data)->i;
        ((struct Point*)temp->data)->j = ((struct Point*)snake->head->data)->j - 1;
    }
    else if (snake->direction == UP)
    {
        ((struct Point*)temp->data)->j = ((struct Point*)snake->head->data)->j;
        ((struct Point*)temp->data)->i = ((struct Point*)snake->head->data)->i - 1;
    }
    else if (snake->direction == DOWN)
    {
        ((struct Point*)temp->data)->j = ((struct Point*)snake->head->data)->j;
        ((struct Point*)temp->data)->i = ((struct Point*)snake->head->data)->i + 1;
    }
    temp->next = snake->head;
    snake->head = temp;
}
