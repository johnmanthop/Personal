#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "scene.h"
#include "Player.h"
#include "animation.h"

int main()
{
    srand(time(NULL));
    sf::RenderWindow win(sf::VideoMode(576, 324), "ASD");

    Scene sc1("dependencies/Tiles/Background/Background.png");
    sc1.read_file("scene1.txt");
    sc1.init_map();
    sf::Texture t;

    Player pl("Dependencies/Characters/Woodcutter/Woodcutter_walk.png", 260, 200);
    Tree_Cop cop;

    sf::Text text;
    sf::Font font;
    font.loadFromFile("Dependencies/Pixellari.ttf");
    text.setFont(font);
    text.setPosition(100, 120);
    text.setCharacterSize(20);
    bool gameover = false;

    while (win.isOpen())
    {
        win.setFramerateLimit(60);
        sf::Event ev;

        if (!gameover)
        {

            sc1.handle_collisions(pl);

            cop.update_movement();

            if (!pl.bdown) pl.set_ground_level(320);

            if (!pl.get_paused())
            {
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) pl.reset_anim();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || pl.is_jumping())
                {
                    if (!pl.is_freefalling() && !pl.bup) pl.jump();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !pl.bright)
                {
                    sc1.go_right();
                    pl.reverse_right();
                    if (!pl.is_looking_right()) pl.step_animation_forward();//Go directly one frame forward in the animation
                    pl.animate_walk();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !pl.bleft)
                {
                    sc1.go_left();
                    pl.reverse_left();
                    if (pl.is_looking_right()) pl.step_animation_forward();
                    pl.animate_walk();
                }
            }


            if (pl.bup) pl.stop_jump();

            if (!pl.is_jumping()) pl.gravity();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                pl.is_cutting(true);
                pl.animate_cut();
                pl.hit(sc1);
            }
            else
            {
                pl.is_cutting(false);
                pl.update_idle_cutting_animation();
                pl.zero_cut_counter();
                pl.stop_cut();
            }
            pl.reset_blocks();

            cop.handle_spawning(pl);

            if (pl.get_trees_cut() == 10)
            {
                text.setString("               CONGRATULATIONS\nYOU DISRESPECTED THE GHOST 10 TIMES\n          YOU MUST BE REALY PROUD");
                gameover = true;
            }
        }
        while(win.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                win.close();
        }

        win.clear();
        sc1.draw(win);
        pl.draw(win);
        cop.draw(win);
        if (gameover) win.draw(text);
        win.display();
    }
    return 0;
}
