/*
 * Level_Manager.cpp
 *
 *  Created on: Mar 17, 2023
 *      Author: imanthoc
 */

#include "Bitmaps.h"
#include "Renderer.h"
#include "Level_Manager.h"

Level_Manager::Level_Manager()
{
	score = 0;
	player = Soldier(player_rgb, 80, 900);
	// sadly const members of Drawable Content need to be non const for this to work
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		enemies[i] = Soldier(enemy_rgb, positions_x[i], 0);
	}
}

bool Level_Manager::tick()
{
	if (soldier_handler.command_player(player, enemies))
	{
		score++;
	}
	soldier_handler.command_enemies(enemies);

	return check_end();
}

bool Level_Manager::check_end()
{
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i].get_y() + 20 >= (player.get_y() >> 3))
		{
			return true;
		}
	}

	return false;
}

void Level_Manager::draw()
{
	Renderer::draw(player.get_drawable());
	player.reset_frame();

	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		Renderer::draw(enemies[i].get_drawable());
		enemies[i].reset_frame();
	}
}
