#ifndef COLLISION_HPP_INCLUDED
#define COLLISION_HPP_INCLUDED
#include "level.hpp"
class block;
enum COL_TYPE {LEFT, RIGHT, UP, DOWN, AIR_DOWN, DEATH, END, NO};

class collision {
    COL_TYPE type;
    block* b;
public:
    collision();
    collision(COL_TYPE _type, block* _b);
    COL_TYPE get_t();
    block* get_block();
};

#endif // COLLISION_HPP_INCLUDED
