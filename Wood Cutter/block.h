#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>
#include "player.h"

class Player;
class General_Block
{
protected:
    sf::Sprite sp;
    sf::Texture tx;
    double x, y;
    bool print;
public:
    General_Block(double _x, double _y);
    ~General_Block();
    const sf::Sprite& get_sp() { return sp; }
    double get_x() { return x; }
    double get_y() { return y; }
    void set_position(double _x, double _y);

    bool to_print() { return print; }

    virtual int check_collision(Player&) = 0;
    virtual int hit() = 0;
    virtual void destroy() = 0;
};

class Air_Block : public General_Block
{
public:
    Air_Block(double _x, double _y);
    ~Air_Block();

    int check_collision(Player& p) { return 0; }
    int hit() { return 1; }
    void destroy() {  }
};

class Platform_Block : public General_Block
{
public:
    Platform_Block(const char* fname, double _x, double _y);
    ~Platform_Block();
    int check_collision(Player&);
    int hit() { return 1; }
    void destroy() {  }
};

class Tree : public General_Block
{
    int health;
public:
    Tree(const char* fname, double _x , double _y);

    int check_collision(Player& p) { return 0; }

    int hit()
    {
        health -= 20;
        if (health == 0) { destroy(); return -1; health = -1; }
        else return 0;
    }

    void destroy() { print = false; }
    int get_health() { return health; }

};

#endif // BLOCK_H
