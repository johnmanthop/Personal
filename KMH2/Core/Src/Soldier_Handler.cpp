/*
 * player_handler.cpp
 *
 *  Created on: Mar 17, 2023
 *      Author: imanthoc
 */

#include "Renderer.h"
#include "Soldier_Handler.h"
#include "IM_IO.h"

Soldier_Handler::Soldier_Handler()
{
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		state_frame_counters[i] = 0;
	}
}

bool Soldier_Handler::command_player(Soldier &player, Soldier enemies[])
{
	if (is_select_pressed())
	{
		player.fire(enemies);
		speaker_fire();

		return true;
	}
	else if (is_left_pressed())		player.move_left();
	else if (is_right_pressed()) 	player.move_right();

	return false;
}

void Soldier_Handler::command_enemy(Soldier &soldier, uint8_t i)
{
	if (state_frame_counters[i] == 1)
	{
		state_frame_counters[i] = 0;
		soldier.move_down();
	}
	else
	{
		state_frame_counters[i]++;
	}
}

void Soldier_Handler::command_enemies(Soldier enemies[])
{
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i].is_alive())
		{
			command_enemy(enemies[i], i);
		}
	}
}
