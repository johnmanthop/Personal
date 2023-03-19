/*
 * Soldier.h
 *
 *  Created on: Mar 12, 2023
 *      Author: imanthoc
 */

#ifndef SRC_SOLDIER_H_
#define SRC_SOLDIER_H_

#include <stdint.h>
#include "Drawable_Content.h"

class Soldier {
private:
	Drawable_Content drw_content;
	bool alive;
	int init_x, init_y;
private:
	void reset_pos();
public:
	Soldier();	// create an empty constructor for compatibility reasons
	Soldier(unsigned int bitmap[15][15], int x, int y);
public:
	int get_x() const { return drw_content.current_x; }
	int get_y() const { return drw_content.current_y; }

	void reset_frame();
	void move_down  ();
	void move_right	();
	void move_left  ();
	void fire		(Soldier enemies[]);

	void die		();
	void revive		();
	bool is_alive	();

	Drawable_Content get_drawable() const { return drw_content; }
};

#endif /* SRC_SOLDIER_H_ */
