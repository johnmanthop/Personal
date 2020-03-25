#ifndef GRAVITY_HPP_INCLUDED
#define GRAVITY_HPP_INCLUDED
#include "player.hpp"

class force {//A force is implemented as a 2d vector
    float x;
    float y;
    double f;
//    player* object;
    sf::Vector2f v;//Vector
public:
    force();
    force(player* p, double _x, double _y);
    double get_x();
    double get_y();
    void set_x(double _x);
    void set_y(double _y);
};

class gravity : public force {
    const double g = 1.5;
public:
    void set_c() {
        //set_x(object->get_x());
        set_y(get_y() + g);
    }
    void act() {
//        object->set_c();
    }
};

#endif // GRAVITY_HPP_INCLUDED
