#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "collision.hpp"
#include "player.hpp"
#include "collision.hpp"
class collision;
class block {
public:
    std::string id;//Identifier, for inherited functions
    sf::Sprite sp;
    sf::Texture tx;
    virtual collision* check_collision(player* p);//Virtual function to be implemented in the inherited classes
    double x;
    double y;
    sf::Sprite* get_sp();
    //Blocks are what makes up a level
};

class platform_block : public block {
public:
    platform_block();
    platform_block(double _x, double _y, const char* name);
    virtual collision* check_collision(player* p);
};

class air_block : public block {

public:

    air_block();
    air_block(double _x, double _y);
    virtual collision* check_collision(player* p);
};

class fire_block : public block {

public:
    fire_block();
    fire_block(double _x, double _y);
    virtual collision* check_collision(player* p);
};

class end_block : public block {
public:
    end_block();
    end_block(double _x, double _y);
    virtual collision* check_collision(player* p);
};

class level {
//This is an integer representation of a level
    /**
        eg: 000000000000
            000000001110
            000011111110
            000000000000
            //Where 0 indicates air block and 1 indicates platform block
    **/
    std::vector< std::vector<block*> > block_map;//2d vector for the blocks
    const int width = 30;//Block's width and height
    const int height = 30;//A block is basically a square with certain properties
    double x;
    double y;
    std::vector< std::vector<int> > level_map;//2d vector for the integer representation
    sf::Music music;

public:
    level();
    void parse();//Translates the integer representation to actual blocks
    block* get_block(int i, int j);
    void reloc(int dir, player* p);//Relocate the map (when the player is close to the edge)
    void read_file();
    int i_size();
    int j_size();
    void delete_map();
    void play();
};

#endif // LEVEL_HPP_INCLUDED
