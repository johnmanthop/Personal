#include "animation.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Animation::Animation()
{  }

Animation::Animation(const sf::Texture& tx, int _count)
{
    x = y = 0;
    count = _count;
    stride = tx.getSize().x / count;
    speed = 1;//default animation speed
    animation_rectangle = sf::IntRect(0, 0, stride, stride);
    counter = 0;
    looks_right = true;
    current_frame = 1;

    sp.setTexture(tx);
    sp.setTextureRect(animation_rectangle);
    r1 = r2 = 0;
    r3 = r4 = stride;
}

Animation::~Animation()
{
    //dtor
}

void Animation::init(const sf::Texture& tx, int _count)
{
    x = y = 0;
    count = _count;
    stride = tx.getSize().x / count;
    speed = 1;//default animation speed
    animation_rectangle = sf::IntRect(0, 0, stride, stride);
    counter = 0;
    looks_right = true;
    current_frame = 1;

    sp.setTexture(tx);
    sp.setTextureRect(animation_rectangle);
    r1 = r2 = 0;
    r3 = r4 = stride;
}

void Animation::run()
{
    if (counter > 60)
    {
        r1 += 48;
        if (looks_right)
        {
            animation_rectangle = sf::IntRect(r1, r2, r3, r4);
        }
        else
        {
            if (current_frame == 1)
                animation_rectangle = sf::IntRect(stride, r2, -r3, r4);
            else
                animation_rectangle = sf::IntRect(r1, r2, -r3, r4);
        }

        sp.setTextureRect(animation_rectangle);
        current_frame++;
        counter = 0;

    }
    else counter += speed;
    if (current_frame == count)
    {
        current_frame = 1;
        r1 = 0;
    }

}

void Animation::step_forward()
{
    if (looks_right)
    {
        animation_rectangle = sf::IntRect(r1, r2, r3, r4);
    }
    else
    {
        if (current_frame == 1)
            animation_rectangle = sf::IntRect(stride, r2, -r3, r4);
        else
            animation_rectangle = sf::IntRect(r1, r2, -r3, r4);
    }
    sp.setTextureRect(animation_rectangle);
}

void Animation::pause()
{
    r1 = r2 = 0;
    r3 = r4 = stride;
    animation_rectangle = sf::IntRect((looks_right)?r1:stride, r2, (looks_right)?r3:-r3, r4);
    sp.setTextureRect(animation_rectangle);
    counter = 0;
    current_frame = 1;
}

void Animation::reset()
{
    r1 = r2 = 0;
    r3 = r4 = stride;
    animation_rectangle = sf::IntRect(r1, r2, r3, r4);
    sp.setTextureRect(animation_rectangle);
    counter = 0;
    current_frame = 1;
}

void Animation::reverse_right()
{
    looks_right = true;
}

void Animation::reverse_left()
{
    looks_right = false;
}
