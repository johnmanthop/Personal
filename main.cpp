#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
const double GROUNDLEVEL = 150;
//Used to check if player is on the ground or not

#include "player.hpp"
#include "level.hpp"
#include "collision.hpp"
#include "screen.hpp"


int main() {
    sf::RenderWindow win(sf::VideoMode(600, 180), "Wannabe retro game");
    sf::Color background(0, 162, 232);


    screen end_screen;
    screen start_screen;
    screen win_screen;
    start_screen.add_text(new text(224, 0, "WELCOME"));//Non selectable text
    start_screen.add_s_text(new text(50, 40, "START"));//Selectable tex
    start_screen.add_s_text(new text(50, 80, "EXIT"));
    start_screen.add_image(new image(400, 50, "player.png", 3, 3));
    end_screen.add_text(new text(224, 0, "YOU LOSE"));
    end_screen.add_s_text(new text(50, 40, "RETRY"));
    end_screen.add_s_text(new text(50, 80, "EXIT"));
    end_screen.set_active(false);
    win_screen.add_text(new text(220, 0, "YOU WIN"));
    win_screen.add_s_text(new text(50, 40, "RESTART"));
    win_screen.add_s_text(new text(50, 80, "EXIT"));
    win_screen.set_active(false);


restart:
    win_screen.set_active(false);
    end_screen.set_active(false);
    player p;
    level l;
    l.play();
    l.read_file();
    l.parse();

    p.set_c(0, p.get_line());
    p.reloc();
    bool game_active = false;//Indicates that all other screens are inactive and the game is running
    //The actual game starts when all other screens are inactive
    while(win.isOpen()) {

        if (//Check
            !start_screen.get_active() &&
            !end_screen.get_active() &&
            !win_screen.get_active()
            ) { game_active = true; }
        else { game_active = false;}
        if (start_screen.get_active()) {//HANDLE SELECTION
            if (start_screen.handle_selection() == 0) {
                start_screen.set_active(false);
                game_active = true;
            } else if (start_screen.handle_selection() == 1) {
                return 0;
            }
        }

        win.setFramerateLimit(60);
        if (game_active) {//ALL THE GAME STUFF GOES HERE
            {//Keyboard listening here:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    if (p.get_sp().getPosition().x > 400) {
                        l.reloc(-1, &p);//Relocate to the right
                    } else {
                        p.go_right();
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    if (p.get_sp().getPosition().x < 100) {
                        l.reloc(1, &p);
                    } else {
                        p.go_left();
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    if ((!p.is_jumping()) && (!p.is_on_air()))//Activate only once (not for every frame that w is being pressed)
                        p.jump();
                }
            }//Keyboard listening end

            {//Check for jump mechanism
                if (p.is_jumping()) {
                    p.jump();//Since the jump is a continous move, I call the jump function for 15 frames after the w button is pressed
                }
                p.gravity_pull();//Handles all the gravity stuff
            }//End

            {//Check for collisions
                bool lc = false;//lc: left(movement) changed. Logic checks to ensure that once an action has happend it won't happen again
                bool rc = false;//rc: right(movement) changed
                bool cl = false;//cl : changed line
                //Check mark bellow
                for (int i = 0; i < l.i_size(); i++) {
                    for (int j = 0; j < l.j_size(); j++) {
                        /**
                            Every map block returns a collision object that contains information
                            regarding that block's collision condition.
                        **/
                        collision*c = NULL;
                        c = l.get_block(i, j)->check_collision(&p);
                        if (c != NULL) {//Is not null
                            if (c->get_t() == END) {//If the player collides with an END block (victory) set the victory screen active
                                win_screen.set_active(true);
                            }
                            else if (c->get_t() == DEATH) {//Act accordingly...
                                p.set_health(p.get_health()- 1);
                            }
                            if (c->get_t() == UP) {
                                p.stop_jump();
                            } else if (c->get_t() == DOWN) {
                                p.set_line(c->get_block()->get_sp()->getPosition().y - 27);
                                cl = true;//Mark
                                //Once the ground line has changed in this frame it can't be changed again
                            }
                            if (c->get_t() == RIGHT) {
                                p.block_right();
                                rc = true;//Ensures that the right movement will stay blocked for the rest of the check(will not be unchecked by another block)
                            } else {
                                if (rc == false) {
                                    p.unblock_right();
                                }
                            }
                            if (c->get_t() == LEFT) {
                                p.block_left();//The block left/right methods block the left and right movement in case of a left/right collision
                                lc = true;
                            } else {
                                if (lc == false) {
                                    p.unblock_left();
                                }
                            }
                            if (c->get_t() == AIR_DOWN) {//If the player collides with an air block
                                if (cl == false)
                                    p.set_line(GROUNDLEVEL);//Set the ground line to the ground level (the player will start falling)
                            }
                            delete c;//Garbage collection, IMPORTANT
                        }
                    }
                }
            }
        }


        if (p.get_health() <= 0) { end_screen.set_active(true); }//If the player has bellow zero health activate the end scren


        sf::Event ev;
        while (win.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                win.close();
            }


        }

        //DRAWING GOES HERE

        win.clear(background);
        if (start_screen.get_active()) {//If the starting screen is active
            start_screen.print_texts(&win);//Display all texts, selectable texts and images (all of the scene's information)
            start_screen.print_selectable_texts(&win);
            start_screen.print_images(&win);
        }
        else if (game_active) {//If the game is active
            for (int i = 0; i < l.i_size(); i++) {
                for (int j = 0; j < l.j_size(); j++) {
                    win.draw(*(l.get_block(i, j)->get_sp()));//Draw all the map blocks
                }
            }

            win.draw(p.get_sp());
            win.draw(p.get_text());//Health text
        } else if (end_screen.get_active()) {//If the end screen is active
            end_screen.print_texts(&win);//Again print all of the scene's information
            end_screen.print_selectable_texts(&win);
            if (end_screen.handle_selection() == 0) {//Handle button selection
                l.delete_map();//Garbage collection
                goto restart;//I know, i know... don't use goto
                //It solves the problem so easily though
            } else if (end_screen.handle_selection() == 1) {
                return 0;
            }
        } else if (win_screen.get_active()) {//If the victory screen is active
            win_screen.print_texts(&win);
            win_screen.print_selectable_texts(&win);
            if (win_screen.handle_selection() == 0) {
                l.delete_map();
                goto restart;
            } else if (win_screen.handle_selection() == 1) {
                return 0;
            }
        }
        win.display();
    }
    return 0;
}

