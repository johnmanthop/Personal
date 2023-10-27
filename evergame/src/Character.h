#ifndef CHARACTER
#define CHARACTER

#include <iostream>
#include <map>
#include <string>

#include "Constants.h"
#include "Drawable_Content.h"
#include "Animation_Manager.h"

class Character
{
private:
    double y_position;
    int jump_counter;
    double universal_position;
    double relative_position;
    const double center_position;
    Drawable_Static character_static;
    std::map<int, double> jumping_force_map;
public:
    Character();
    // no reason for this to be private
    Animation_Manager animation_manager;
    sf::Sprite& get_sprite();
    void inc_uposition() { universal_position += ROLL_STEP; }
    void dec_uposition() { universal_position -= ROLL_STEP; }
    void move_left(); 
    void move_right();

    // move both static and animation sprites
    void universal_move(float x, float y);

    double get_absolute_x() const { return universal_position; }
    double get_absolute_y() const { return y_position; }

    bool can_move_left() const;
    bool can_move_right() const;
    bool is_at_center() const { return relative_position == center_position; }

    void trigger_jump() { jump_counter = 0; }
    int get_jumping_state() const;
    double get_jumping_force() const;
    double get_max_gravity_force() const;
    void tick_jump();

    bool is_in_proximity(int p) const;
};

#endif