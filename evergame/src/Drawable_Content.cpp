#include <iostream>

#include "Drawable_Content.h"

Drawable_Static::Drawable_Static(const std::string &file, int x, int y)
{
    reset(file, x, y);
}

void Drawable_Static::reset(const std::string &file, int x, int y)
{
    if (!texture.loadFromFile(file))
    {
        std::cout << "Error loading texture\n";
    }
    
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

Drawable_Animation::Drawable_Animation(const std::string &file, int no_of_frames_, int animation_speed_, int x, int y)
{
    reset(file, no_of_frames_, animation_speed_, x, y);
}

void Drawable_Animation::reset(const std::string &file, int no_of_frames_, int animation_speed_, int x, int y)
{
    if (!spritesheet.loadFromFile(file))
    {
        std::cout << "Error loading spritesheet\n";
    }

    local_frame_tick_counter = 1;
    global_animation_tick_counter = 1;
    no_of_frames        = no_of_frames_;
    animation_speed     = animation_speed_;
    rect_left_top       = 0;

    spritesheet_width  = spritesheet.getSize().x;
    spritesheet_height = spritesheet.getSize().y;

    frame_height = spritesheet_height;
    frame_width = spritesheet_width / no_of_frames;

    current_sprite.setTexture(spritesheet);
    current_sprite.setTextureRect({ { 0, 0 }, { frame_width, frame_height } });
    current_sprite.setPosition(x, y);
}

void Drawable_Animation::reset_sprite()
{
    current_sprite.setTextureRect({ { 0, 0 }, { frame_width, frame_height } });
}

void Drawable_Animation::tick()
{
    global_animation_tick_counter++;

    int formet_left = current_sprite.getTextureRect().left;

    if (local_frame_tick_counter == animation_speed)
    {
        // that means the frame needs to wraparound
        if (formet_left + frame_width >= spritesheet_width)
        {
            current_sprite.setTextureRect({ { 0, 0 }, { frame_width, frame_height } });
            global_animation_tick_counter = 1;
        }
        else 
        {
            current_sprite.setTextureRect({ { formet_left + frame_width, 0 }, { frame_width, frame_height } });
        }
        local_frame_tick_counter = 1;
    }
    else
    {
        local_frame_tick_counter++;
    }
}