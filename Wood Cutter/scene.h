#ifndef SCENE_H
#define SCENE_H
#include <iostream>
#include <vector>
#include "block.h"
#include "player.h"

class General_Block;
class Player;
class Scene
{
    std::vector<std::vector<General_Block*>> tile_map;
    std::vector<std::vector<int>> int_map;
    const int tile_width = 32;
    const int tile_height = 32;
    sf::Sprite sp;
    sf::Texture tx;
    double view_x;
    std::vector<std::string> file_names;
public:
    Scene(const char* background_file);
    ~Scene();

    void read_file(const char*);
    void init_map();

    void draw(sf::RenderWindow& win);//The object is responsible for drawing itself

    void go_right();
    void go_left();

    void handle_collisions(Player& p);
    General_Block* get_tile_with_coordinate(double x, double y);
};

#endif // SCENE_H
