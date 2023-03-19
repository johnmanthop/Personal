/*
 * Level_Manager.h
 *
 *  Created on: Mar 17, 2023
 *      Author: imanthoc
 */

#ifndef LEVEL_MANAGER_H_
#define LEVEL_MANAGER_H_


#include "Soldier_Handler.h"
#include "Bitmaps.h"
#include "Soldier.h"

#define MAX_ENEMIES 5

class Level_Manager
{
private:
	int score;
	int positions_x[MAX_ENEMIES] = { 0, 45, 90, 135, 180 };
private:
	Soldier_Handler soldier_handler;
	Soldier player;
	Soldier enemies[MAX_ENEMIES];
private:
	bool check_end();
public:
	Level_Manager();
public:
	bool tick();
	void draw();
	int  get_score() const { return score; }
};

#endif /* LEVEL_MANAGER_H_ */
