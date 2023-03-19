/*
 * player_handler.h
 *
 *  Created on: Mar 17, 2023
 *      Author: imanthoc
 */

#ifndef SOLDIER_HANDLER_H_
#define SOLDIER_HANDLER_H_

#include "Soldier.h"

#define MAX_ENEMIES 5

class Soldier_Handler
{
private:
	// enemies advance slower than the player,
	// one advancment each 10 frames
	uint8_t state_frame_counters[MAX_ENEMIES];
private:
	void command_enemy(Soldier &enemy, uint8_t index);
public:
	Soldier_Handler();
public:
	bool command_player (Soldier &player, Soldier enemies[]);
	void command_enemies(Soldier enemies[]);
};

#endif /* INC_PLAYER_HANDLER_H_ */
