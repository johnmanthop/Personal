/*
 * Soldier.cpp
 *
 *  Created on: Mar 12, 2023
 *      Author: imanthoc
 */

#include "Soldier.h"
#include "Bitmaps.h"
#include "Drawable_Content.h"

#define MAX_ENEMIES 5

Soldier::Soldier():
	drw_content(nullptr, 0, 0, 0)
{

}

Soldier::Soldier(unsigned int bitmap[15][15], int x, int y):
	drw_content(bitmap, x, y, 2)
{
	init_x = x;
	init_y = y;
	alive = true;
}

void Soldier::reset_pos()
{
	drw_content.next_x = init_x;
	drw_content.next_y = init_y;
}

void Soldier::move_down()
{
	if (drw_content.next_y + STEP + drw_content.height * drw_content.scale >= HEIGHT) return;
	else drw_content.next_y += STEP;
}
void Soldier::move_right()
{
	if (drw_content.next_x + 2*STEP + drw_content.width * drw_content.scale>= WIDTH) return;
	else drw_content.next_x += 2*STEP;
}
void Soldier::move_left()
{
	if (drw_content.next_x - 2*STEP < 0) return;
	else drw_content.next_x -= 2*STEP;
}

void Soldier::fire(Soldier enemies[])
{
	int gun_position = drw_content.current_x + (drw_content.width*drw_content.scale >> 1); //current gun position

	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (
			gun_position > enemies[i].get_x() &&
			gun_position < enemies[i].get_x() + enemies[i].drw_content.width*enemies[i].drw_content.scale
		)
		{
			enemies[i].die();
			break;
		}
	}

}

void Soldier::reset_frame()
{
	drw_content.current_x = drw_content.next_x;
	drw_content.current_y = drw_content.next_y;
}

void Soldier::die()
{
	reset_pos();
}

void Soldier::revive()
{
	alive = true;
}

bool Soldier::is_alive()
{
	return alive;
}
