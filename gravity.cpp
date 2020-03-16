#include <SFML/Graphics.hpp>
#include "gravity.hpp"

force::force() {}
force::force(player* p, double _x, double _y) {
    x = _x;
    y = _y;
    v = sf::Vector2f(x, y);
//d    object = p;
}

double force::get_x() { return x; }
double force::get_y() { return y; }
void force::set_x(double _x) {
    x = _x;
    v.x = x;//Automatically update vector
}
void force::set_y(double _y) {
    y = _y;
    v.y = y;
}

