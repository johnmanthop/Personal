#include "collision.hpp"

collision::collision() {}
collision::collision(COL_TYPE _type, block* _b) {
    type = _type;
    b = _b;
}

COL_TYPE collision::get_t() { return type; }

block* collision::get_block() { return b; }
