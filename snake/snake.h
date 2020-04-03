#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED



enum DIRECTION{ UP, DOWN, LEFT, RIGHT };

struct Point
{
    int i, j;
};

struct Snake
{
    struct List_Node *head;
    struct List_Node *current;
    int count;
    enum DIRECTION direction;
};

struct Snake *init_snake();

void turn_right(struct Snake *snake);
void turn_left(struct Snake *snake);
void turn_up(struct Snake *snake);
void turn_down(struct Snake *snake);

void add_point(struct Snake *snake);

void tick(struct Snake *snake);

#endif // SNAKE_H_INCLUDED
