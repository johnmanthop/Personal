#include "player.h"
#include <iostream>

Person::Person(const char* fname, double _x, double _y)
{
    x = _x;
    y = _y;
    tx.loadFromFile(fname);
    walk_animation.init(tx, 6);
    walk_animation.set_speed(12);
    walk_animation.set_position(x, y);
}

Person::~Person()
{  }

void Person::set_position(double _x, double _y)
{
    x = _x;
    y = _y;
    walk_animation.set_position(x, y);
}


Player::Player(const char* fname, double _x, double _y):
    Person(fname, _x, _y),
    gravity_counter(0),
    ground_level(320),
    jump_counter(0),
    bleft(false),
    bright(false),
    bup(false),
    bdown(false),
    trees_cut(0),
    is_cutting_in(false),
    cut_counter(0),
    paused(false)
{
    cut_tx.loadFromFile("Dependencies/Characters/Woodcutter/Woodcutter_attack1.png");
    font.loadFromFile("Dependencies/Pixellari.ttf");
    text.setFont(font);
    text.setString("TREES CUT :" + std::to_string(trees_cut));
    cut_animation.init(cut_tx, 6);
    cut_animation.set_position(_x, _y);
    cut_animation.set_speed(23);
}

Player::~Player()
{  }

void Player::jump()
{
    jump_counter++;
    gravity_counter = 0;
    if (jump_counter > 20)
    {
        jump_counter = 0;//End jump here
        return;
    }
    if (jump_counter <= 10) y -= 3;
    else if (jump_counter <= 15) y -= 1.5;
    else if (jump_counter <= 20) y -= 0.7;
    walk_animation.set_position(x, y);//From now, gravity takes hold of the down motion
    cut_animation.set_position(x, y);
}

void Player::gravity()
{
    if (y+48 < ground_level)
    {
        y += GRAVITY_CONSTANT*(++gravity_counter);
        walk_animation.set_position(x, y);
        cut_animation.set_position(x, y);
    }
    else
    {
        gravity_counter = 0;
        y = ground_level - 48;
        walk_animation.set_position(x, y);
        cut_animation.set_position(x, y);
    }
}

void Player::hit(Scene& s)
{
    cut_counter += 23;//Same as animation speed
    if (cut_counter > 260)
    {
        General_Block* temp_tile = s.get_tile_with_coordinate(x+24, y+24);
        if (temp_tile)
        {
            if (temp_tile->hit() == -1) trees_cut++;
            text.setString("TREES CUT :" + std::to_string(trees_cut));
        }
        cut_counter = 0;
    }
    //Don't delete the tile since it is owned by the scene class
}

Tree_Cop::Tree_Cop():
    Person("Dependencies/Characters/GraveRobber/GraveRobber_walk.png", 0, 0),
    state(DEAD),
    fade_counter(0)
{
    font.loadFromFile("Dependencies/Pixellari.ttf");
    text.setFont(font);
    text.setString("I am the ghost of the bored programmer,\nand you should respect the environment!");
    text.setCharacterSize(20);
}

void Tree_Cop::run()
{
    walk_animation.run();
}

void Tree_Cop::spawn(double _x, double _y)
{
    state = SPAWNING;
    x = _x;
    y = _y;
    text.setPosition(x-230, y-50);
    walk_animation.set_position(x, y);
}

void Tree_Cop::despawn()
{
    state = DYING;
}

void Tree_Cop::update_movement()
{
    if (state == SPAWNING)
    {
        if (fade_counter < 254) fade_counter += 2;
        walk_animation.get_sp().setColor(sf::Color(256, 256, 256, (fade_counter>255)?255:fade_counter));//Alpha fade in
    }
    else if (state == DYING)
    {
        fade_counter -= 2;
        if (fade_counter <= 2) state = DEAD;
        walk_animation.get_sp().setColor(sf::Color(256, 256, 256, (fade_counter<0)?0:fade_counter));//Alpha fade out
    }
}

void Tree_Cop::handle_spawning(Player& p)
{
    if (spawn_clock.getElapsedTime() > sf::seconds(10))
    {
        if (rand()% 50 == 7 && state == DEAD)
        {
            spawn(p.get_x()-20, p.get_y());
            p.pause();
        }
    }
    if (spawn_clock.getElapsedTime() > sf::seconds(14))
    {
        if (state == DEAD) spawn_clock.restart();
        despawn();
        p.unpause();
    }
}
