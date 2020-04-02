#include "block.h"
#include "player.h"

General_Block::General_Block(double _x, double _y):
    print(true)
{
    x = _x;
    y = _y;
    sp.setPosition(x, y);
}

General_Block::~General_Block()
{  }

void General_Block::set_position(double _x, double _y)
{
    x = _x;
    y = _y;
    sp.setPosition(x, y);
}

Air_Block::Air_Block(double _x, double _y):
    General_Block(_x, _y)
{  }

Air_Block::~Air_Block()
{  }

Platform_Block::Platform_Block(const char* fname, double _x, double _y):
    General_Block(_x, _y)
{
    tx.loadFromFile(fname);
    sp.setTexture(tx);
}

int Platform_Block::check_collision(Player& p)
{
    double px = p.get_x();
    double py = p.get_y();

    if (sp.getGlobalBounds().contains(px+6, py+15))
    {
        if (sp.getGlobalBounds().contains(px+6, py+20))
        {
            p.bleft = true;
        }
        else
        {
            p.bup = true;
        }
    }
    if (sp.getGlobalBounds().contains(px+25, py+15))
    {
        if (sp.getGlobalBounds().contains(px+25, py+20))
        {
            p.bright = true;
        }
        else
        {
            p.bup = true;
        }
    }
    if (sp.getGlobalBounds().contains(px+6, py+48))
    {
        p.bdown = true;
        p.set_ground_level(sp.getPosition().y);
    }
    if (sp.getGlobalBounds().contains(px+25, py+48))
    {
        p.bdown = true;
        p.set_ground_level(sp.getPosition().y);
    }

    if (sp.getGlobalBounds().contains(px+6, py+45))
    {
        p.bleft = true;
    }
    if (sp.getGlobalBounds().contains(px+25, py+45))
    {
        p.bright = true;
    }
}

Tree::Tree(const char* fname, double _x, double _y):
    General_Block(_x, _y),
    health(100)
{
    tx.loadFromFile(fname);
    sp.setTexture(tx);
}
