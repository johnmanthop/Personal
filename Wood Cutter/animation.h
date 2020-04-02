#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>

class Animation
{
    sf::Sprite sp;
    sf::IntRect animation_rectangle;
    int count, stride;
    double speed;
    int counter;
    bool looks_right;
    int current_frame;
    double x, y;
    double r1, r2, r3, r4;
public:
    Animation();
    Animation(const sf::Texture& tx, int _count);
    ~Animation();

    void init(const sf::Texture& tx, int _count);

    void set_speed(double _speed) { speed = _speed; }
    void run();
    void reset();
    void pause();
    void reverse_right();
    void reverse_left();
    void set_position(double _x, double _y)
    {
        x = _x;
        y = _y;
        sp.setPosition(x, y);
    }
    void step_forward();//Step forward one frame

    sf::Sprite& get_sp() { return sp; }
};

#endif // ANIMATION_H
