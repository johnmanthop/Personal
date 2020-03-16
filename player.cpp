#include "player.hpp"
#include <iostream>
#include <math.h>

player::player() {
    tx.loadFromFile("player.png");
    sp.setTexture(tx);
    j_counter = 0;//Jump counter. Used to control the jump mechanism
    pl_line = 150;//Player line. Dictates how high is the player right now (yeah i know, high....)
    br = false;//block right and block left. Used to check collision's with left and right platforms
    bl = false;
    font.loadFromFile("font.ttf");
    health_text.setFont(font);
    health_text.setPosition(10, 10);
    health_text.setCharacterSize(15);
    set_health(100);
}
sf::Sprite player::get_sp() { return sp; }
void player::set_c(double _x, double _y) {
    x = _x;
    y = _y;
}
void player::reloc() {
    sp.setPosition(x, y);
}
void player::move_to(double _x, double _y) {
    x = _x;
    y = _y;
    sp.setPosition(x, y);
}
void player::go_right() {
    if (br == false) {
            x += 5;
        sp.setPosition(x, y);
    }
}
void player::go_left() {
    if (bl == false) {
        x -= 5;
        sp.setPosition(x, y);
    }
}
void player::jump() {//Jump means only the positive part(the upward motion), the downward motion is handled by a different mechanism(gravity_pull() and collision detection)
    j_counter++;//Indicates jumping progression
    //The j_counter increnates once every frame, so i can know at which point of the jump are we now (the jump lasts 15 frames)
    if (j_counter >= 15) {//If 15 frames have passed the jump is over
        j_counter = 0;
        return;
    }
    if (j_counter <= 15) {//Actual jumping mechanism
        y -= 5;//The start of the jump is intense
    } else if (j_counter <= 10) {
        y -= 3;//The mid is not so intense
    } else if (j_counter <= 15) {
        y -= 2;
    }
    sp.setPosition(x, y);
}
bool player::is_jumping() {//Indicates if the player is currently jumping
    //The j counter is zero if and only if the player is not actively jumping (actively means at the upward part)
    if (j_counter == 0) { return false; }
    else { return true; }
}

bool player::is_on_air() {
    if (sp.getPosition().y < pl_line) {//If the player is over the current ground line
        return true;
    } else {
        return false;
    }
}//Different from is_jumping:
//Is_on_air can mean that the player is free falling from a platform
//Is_jumping means that the player is at the positive part of the jump (the upward motion)
//When the upward motion is over(j_counter > 15) then the mechanism is transfered to the gravity_pull function
//Eg: jumping from a platform and then free-falling. Only a collision mechanisn can determine where the player
//Will stop, the negative part of the jump can only be handled by the gravity mechanism

double player::get_x() { return x; }
double player::get_y() { return y; }

int player::get_j_count() { return j_counter; }

void player::gravity_pull() {//
    if ((is_on_air()) &&(!is_jumping())) {//Negative part of the jump, when the player is on the air but is not going upward(free-falling)
        if (sp.getPosition().y < pl_line) {//If the player is over the player line (remember y coordinates are inverted)
            y += gravity_constant;
            sp.setPosition(x, y);
        }
    }
}

/**
    note: difference between groud and player line:
    The ground line is the floor (constantly at y = 180)
    the player line is how high the player must be right now (ex: on a platform)
**/

void player::stop_jump() {//Abruptly stop the jump (directly set the jump counter to end(=15))
    j_counter = 15;
}

void player::set_line(double _c) {
    pl_line = _c;//Set the current player line (how high is the player currently)
}

double player::get_line() { return pl_line; }

void player::block_right() { br = true; }//Logic functions regarding the block/unblock left and right mechanism
void player::unblock_right() { br = false; }
void player::block_left() { bl = true; }
void player::unblock_left() { bl = false; }
bool player::get_rs() { return br; }
bool player::get_ls() { return bl; }

double player::get_health() { return health; }
void player::set_health(double _h) {
    health = _h;

    health_text.setString("HEALTH:" + std::to_string(health));
}

sf::Text player::get_text() { return health_text; }

