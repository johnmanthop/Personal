#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class player {
    sf::Sprite sp;
    sf::Texture tx;
    double x;
    double y;
    double r_x;
    double r_y;
    double j_counter;
    double pl_line;//This is the y coordinate that the player walks across
    //Very usefull tool for manipulations like gravity, collisions etc...
    bool bl;
    int health;
    sf::Text health_text;
    sf::Font font;
public:
    bool br;
    const double gravity_constant = 6;//Not 9.81
    player();
    sf::Sprite get_sp();
    void set_c(double _x, double _y);//This function
    void reloc();//                    This function
    void move_to(double _x, double _y);//And this function may be used for special manipulations, otherwise use the go_left, go_right functions etc..
    void go_right();
    void go_left();
    void jump();
    bool is_jumping();
    double get_x();
    double get_y();
    void gravity_pull();
    int get_j_count();
    bool is_on_air();
    void stop_jump();
    void set_line(double _c);
    double get_line();
    void block_right();
    void unblock_right();
    void block_left();
    void unblock_left();
    bool get_rs();
    bool get_ls();
    double get_health();
    void set_health(double _h);
    sf::Text get_text();
};

#endif // PLAYER_HPP_INCLUDED
