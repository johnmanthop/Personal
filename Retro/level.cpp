#include "level.hpp"
#include "collision.hpp"
#include <fstream>
#include <string>
#include <sstream>
#define NORMAL_BLOCK "plb.png"



sf::Sprite* block::get_sp() { return &sp; }

collision* block::check_collision(player* p) {}//Basic definition, the actual functions are defined in the inherited classes

platform_block::platform_block() {}

platform_block::platform_block(double _x, double _y, const char* name) {
    tx.loadFromFile(name);
    sp.setTexture(tx);
    x = _x;
    y = _y;
    sp.setPosition(x, y);
    id = "platform";
}

collision* platform_block::check_collision(player* p) {
    double _x = p->get_x();//Player's sprite x and y
    double _y = p->get_y();
    if (sp.getGlobalBounds().contains(_x + 30, _y + 15)) {//Collision checks...
        return new collision(RIGHT, this);
        //The return value is a collision pointer that contains the collision's direction
        //(as well as it's nature, for example: a fire block collision causes damage etc...)
        //And a pointer to the block that the collision is happening at (return new collision(RIGHT, ->>this<<-));
        //So i can use the block pointer to retrieve it's coordinates
    }
    else if (sp.getGlobalBounds().contains(_x, _y + 15)) {
        return new collision(LEFT, this);
    }
    else if (sp.getGlobalBounds().contains(_x, _y)) {
        return new collision(UP, this);
    }
    else if (sp.getGlobalBounds().contains(_x + 12, _y)) {
        return new collision(UP, this);
    }
    else if (sp.getGlobalBounds().contains(_x + 24, _y)) {
        return new collision(UP, this);
    }
    else if (sp.getGlobalBounds().contains(_x+5, _y + 28)) {
        return new collision(DOWN, this);
    }
    else if (sp.getGlobalBounds().contains(_x + 24, _y + 28)) {
        return new collision(DOWN, this);
    }
    else if (sp.getGlobalBounds().contains(_x + 12, _y + 28)) {
        return new collision(DOWN, this);
    } else {
        return new collision(NO, NULL);//Always return a null pointer in the else case
    }
}

air_block::air_block() {}
air_block::air_block(double _x, double _y) {
    tx.loadFromFile("airb.png");
    sp.setTexture(tx);
    x = _x;
    y = _y;
    sp.setPosition(x, y);
    id = "air";
}

collision* air_block::check_collision(player* p) {
    double _x = p->get_sp().getPosition().x;
    double _y = p->get_sp().getPosition().y;

    if (sp.getGlobalBounds().contains(_x, _y + 30)) {
        return new collision(AIR_DOWN, this);//This signals the pl_line to be lowered at ground level
    }
    else if (sp.getGlobalBounds().contains(_x + 30, _y + 30)) {
        return new collision(AIR_DOWN, this);
    } else { return NULL; }
}

fire_block::fire_block() {}
fire_block::fire_block(double _x, double _y) {
    tx.loadFromFile("fireb.png");
    sp.setTexture(tx);
    x = _x;
    y = _y;
    sp.setPosition(x, y);
    id = "fire";
}

collision* fire_block::check_collision(player*p) {
    double _x = p->get_sp().getPosition().x;
    double _y = p->get_sp().getPosition().y;
    sf::FloatRect pr = sp.getGlobalBounds();
    if (
        pr.contains(_x, _y) ||
        pr.contains(_x + 30, _y) ||
        pr.contains(_x, _y + 30) ||
        pr.contains(_x + 30, _y + 30)
        ) { return new collision(DEATH, this); }
    else { return new collision(NO, NULL); }
}

end_block::end_block() {}
end_block::end_block(double _x, double _y) {
    tx.loadFromFile("airb.png");
    sp.setTexture(tx);
    x = _x;
    y = _y;
    sp.setPosition(x, y);
    id = "end";
}

collision* end_block::check_collision(player* p) {
    double _x = p->get_x();
    double _y = p->get_y();
    if (sp.getGlobalBounds().contains(_x + 30, _y + 15)) {
        return new collision(END, this);
    } else { return new collision(NO, NULL); }
    //Never forget to return a null collision

}

level::level() {
    x = 0;
    y = 0;
    music.openFromFile("sound.wav");
    music.setPosition(0, 1, 0);
    music.setPitch(1);
    music.setVolume(100);
    music.setLoop(true);

}

void level::parse() {//This converts the integer map to actual block map
    for (int i = 0; i < i_size();i++) {

        std::vector<block*> a;

        for (int j = 0; j < j_size(); j++) {
            block_map.push_back(a);
            if (level_map[i][j] == 0) {
                block_map[i].push_back(new air_block(x, y));
            } else if (level_map[i][j] == 1) {
                block_map[i].push_back(new platform_block(x, y, NORMAL_BLOCK));
            } else if (level_map[i][j] == 2) {
                block_map[i].push_back(new fire_block(x, y));
            } else if (level_map[i][j] == 3) {
                block_map[i].push_back(new end_block(x, y));
            }
            x += width;
        }

        y += height;
        x = 0;
    }
}

void level::reloc(int dir, player* p) {//Dir = direction, 1 = left and -1 = right
    int c;
    if (dir == 1) {
        c = 5;
    } else if (dir == -1) {
        c = -5;
    }
    if (dir == -1 && !(p->get_rs())) {
        for (int i = 0; i < i_size(); i++) {
            for (int j = 0; j < j_size(); j++) {//Shift every one block depending on the c variable
                block_map[i][j]->get_sp()->setPosition(block_map[i][j]->get_sp()->getPosition().x+c, block_map[i][j]->get_sp()->getPosition().y);
            }
        }
    }
    if (dir == 1 && !(p->get_ls())) {
        for (int i = 0; i < i_size(); i++) {
            for (int j = 0; j < j_size(); j++) {
                block_map[i][j]->get_sp()->setPosition(block_map[i][j]->get_sp()->getPosition().x+c, block_map[i][j]->get_sp()->getPosition().y);
            }
        }
    }
}
block* level::get_block(int i, int j) { return block_map[i][j]; }

int to_int(char c) {//I know it sucks but i had no internet when writing this
    if(c == '0')//So i went the brute-force way
        return 0;
    else if (c == '1')
        return 1;
    else if (c == '2')
        return 2;
    else if (c == '3')
        return 3;
    else
        return -1;
}

void level::read_file() {
    std::ifstream inp("a.txt", std::ios_base::in);
    std::string c;
    int i = 0;
    int j = 0;
    while (inp >> c) {//Read the input file and write it's contents to the integer array(the one that will be converted, see the parse function)
        std::vector<int> a;
        level_map.push_back(a);
        for (j = 0; j < c.size(); j++) {
            level_map[i].push_back(to_int(c[j]));
        }
        i++;
    }
}

int level::i_size() { return level_map.size(); }
int level::j_size() { return level_map[0].size(); }

void level::delete_map() {
    for (int i = 0; i < i_size(); i++) {
        for (int j = 0; j < j_size(); j++) {
            delete block_map[i][j];//When restarting delete previous blocks
        }
    }

}

void level::play() { music.play(); }
