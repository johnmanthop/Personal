#include <fstream>
#include "scene.h"
#include "block.h"

Scene::Scene(const char* background_file):
    view_x(0)
{
    tx.loadFromFile(background_file);
    tx.setRepeated(true);
    sp.setTextureRect(sf::IntRect(0, 0, 100000, 324));
    sp.setTexture(tx);
    file_names.reserve(10);
    file_names.push_back("");//0
    file_names.push_back("dependencies/Tiles/Tiles/Tile_02.png");//1
    file_names.push_back("dependencies/Tiles/Tiles/Tile_01.png");//2
    file_names.push_back("dependencies/Tiles/Tiles/Tile_03.png");//3
    file_names.push_back("dependencies/Tiles/Tiles/Tile_31.png");//4
    file_names.push_back("dependencies/Tiles/Tiles/Tile_33.png");//5
    file_names.push_back("dependencies/Tiles/Tiles/Tile_32.png");//6
    file_names.push_back("dependencies/Tiles/Tiles/Tile_34.png");//7
    file_names.push_back("dependencies/Tiles/Objects/Trees/1.png");//8
}

Scene::~Scene()
{
    for (auto i : tile_map)
    {
        for (auto j : i)
        {
            delete j;
        }
    }
}

void Scene::read_file(const char* fname)
{
    std::ifstream inp(fname, std::ios_base::in);
    std::string c;
    int i = 0;
    int j = 0;
    while (inp >> c)
    {//Read the input file and write it's contents to the integer array(the one that will be converted, see the parse function)
        std::vector<int> a;
        int_map.push_back(a);
        for (j = 0; j < c.size(); j++)
        {
            int_map[i].push_back(c[j]-48);
        }
        i++;
    }
    inp.close();
}

void Scene::init_map()
{
    double x = 0, y = 0;
    for (int i = 0; i < int_map.size();i++)
    {
        std::vector<General_Block*> a;

        for (int j = 0; j < int_map[0].size(); j++)
        {
            tile_map.push_back(a);
            if (int_map[i][j] == 0)
            {
                tile_map[i].push_back(new Air_Block(x, y));
            }
            else if (int_map[i][j] == 1)
            {
                tile_map[i].push_back(new Platform_Block(file_names[1].c_str(), x, y));
            }
            else if (int_map[i][j] == 2)
            {
                tile_map[i].push_back(new Platform_Block(file_names[2].c_str(), x, y));
            }
            else if (int_map[i][j] == 3)
            {
                tile_map[i].push_back(new Platform_Block(file_names[3].c_str(), x, y));
            }
            else if (int_map[i][j] == 4)
            {
                tile_map[i].push_back(new Platform_Block(file_names[4].c_str(), x, y));
            }
            else if (int_map[i][j] == 5)
            {
                tile_map[i].push_back(new Platform_Block(file_names[5].c_str(), x, y));
            }
            else if (int_map[i][j] == 6)
            {
                tile_map[i].push_back(new Platform_Block(file_names[6].c_str(), x, y));
            }
            else if (int_map[i][j] == 7)
            {
                tile_map[i].push_back(new Platform_Block(file_names[7].c_str(), x, y));
            }
            else if (int_map[i][j] == 8)
            {
                tile_map[i].push_back(new Tree(file_names[8].c_str(), x, y));
            }
            x += tile_width;
        }

        y += tile_height;
        x = 0;
    }
}

void Scene::draw(sf::RenderWindow& win)
{
    win.draw(sp);
    for (auto v : tile_map)
    {
        for (auto tile : v)
        {
            if (tile->to_print()) win.draw(tile->get_sp());
        }
    }
}

void Scene::go_right()
{
    view_x += 2;
    sp.setPosition(sp.getPosition().x - 0.5, sp.getPosition().y);
    for (auto v : tile_map)
    {
        for (auto tile : v)
        {
            tile->set_position(tile->get_x() - 2, tile->get_y());
        }
    }
}

void Scene::go_left()
{
    if (view_x > 10)
    {
        view_x -= 2;
        sp.setPosition(sp.getPosition().x + 0.5, sp.getPosition().y);
        for (auto v : tile_map)
        {
            for (auto tile : v)
            {
                tile->set_position(tile->get_x() + 2, tile->get_y());
            }
        }
    }
}

void Scene::handle_collisions(Player& p)
{
    for (auto i : tile_map)
    {
        for (auto tile : i)
        {
            if (tile->get_x() > p.get_x()-10 && tile->get_x() < p.get_x()+50)
            {//Don't collision check all tiles, only those close to the player
                tile->check_collision(p);
            }
        }
    }
}

General_Block* Scene::get_tile_with_coordinate(double x, double y)
{//Returns a pointer instead of a reference because of polymorphism between general, air, platform etc blocks
    for (auto i : tile_map)
    {
        for (auto tile : i)
        {
            if (tile->get_x() >= x - 50 && tile->get_x() <= x + 50)
            {
                if (tile->get_sp().getGlobalBounds().contains(x, y)) return tile;
            }
        }
    }
    return nullptr;//Return a null pointer if it not found
}
