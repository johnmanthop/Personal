#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "animation.h"

#define GRAVITY_CONSTANT 0.5

class Scene;

class Person
{
protected:
    sf::Texture tx;
    double x, y;
    Animation walk_animation;
public:
    Person(const char* fname);//Probably won't get used but whatever
    Person(const char* fname, double _x, double _y);
    ~Person();

    void set_position(double _x, double _y);
};

class Player : public Person
{
    Animation cut_animation;
    double ground_level;
    int gravity_counter;
    //This indicates where the ground coordinate should be
    //Ex: On a platform the ground coordinate is higher than when
    //the player is on the floor level

    int jump_counter;
    sf::Texture cut_tx;
    bool looks_right;
    int trees_cut;
    sf::Text text;
    sf::Font font;
    bool is_cutting_in;
    int cut_counter;
    bool paused;
    //Used to call the hit function at the end of the cut animation instead of the start
public:
    bool bup, bdown, bleft, bright;
    Player(const char* fname, double _x, double _y);
    ~Player();

    void jump();
    void gravity();//These two work together

    void set_ground_level(double _g) { ground_level = _g; }

    double get_x() { return x; }
    double get_y() { return y; }

    const bool is_jumping() { return jump_counter >= 1; }
    const bool is_freefalling()
    {
        return y + 48 < ground_level && jump_counter == 0;
    }

    void reset_anim() { walk_animation.pause(); }
    void reverse_right() { walk_animation.reverse_right(); cut_animation.reverse_right(); }
    void reverse_left() { walk_animation.reverse_left(); cut_animation.reverse_left(); }
    void animate_walk() { walk_animation.run(); }

    void animate_cut() { cut_animation.run(); }
    void stop_cut() { cut_animation.pause(); }
    void update_idle_cutting_animation() { cut_animation.set_position(x, y); }

    void stop_jump() { jump_counter = 0; }
    void zero_cut_counter() { cut_counter = 0; }

    void cut(Scene& s);

    void is_cutting(bool _c) { is_cutting_in = _c; }

    void draw(sf::RenderWindow& win) { win.draw(get_active_anim().get_sp()); win.draw(text); }
    //All objects are responsible for drawing themselvs

    bool is_looking_right() { return looks_right; }

    void step_animation_forward() { walk_animation.step_forward(); }

    void reset_blocks()
    {
        bleft = bright = bup = bdown = false;
    }
    void hit(Scene& s);
    void add_tree() { trees_cut++; }

    void pause() { paused = true; }
    void unpause() { paused = false; }
    bool get_paused() { return paused; }
    int get_trees_cut() { return trees_cut; }

    Animation& get_active_anim() { return (is_cutting_in)?cut_animation:walk_animation; }
};

enum STATE{ALIVE, DEAD, DYING, SPAWNING};
class Tree_Cop : public Person
{
    void check_player();
    STATE state;
    int fade_counter;
    sf::Text text;
    sf::Font font;
    sf::Clock spawn_clock;
public:
    Tree_Cop();
    void update_movement();

    void run();
    void draw(sf::RenderWindow& win)
    {
        if (state != DEAD)
        {
            win.draw(walk_animation.get_sp());
            if (state != DYING) win.draw(text);
        }

    }

    bool is_alive() { return state != DEAD; }

    void spawn(double _x, double _y);
    void despawn();

    void handle_spawning(Player& p);
};//Hopefully an npc



#endif // PLAYER_H
