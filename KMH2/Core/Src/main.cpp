/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <Soldier_Handler.h>
#include "stm32f4xx.h"

#include "Level_Manager.h"

unsigned int player_rgb[15][15] = {};
unsigned int enemy_rgb[15][15] = {};

void init_graphic_tables()
{
	translate_bitmap_to_rgb(player_bitmap_binary, player_rgb);
	translate_bitmap_to_rgb(enemy_bitmap_binary, enemy_rgb);
}

uint8_t uint_to_str(char buffer[], uint32_t number)
{
	uint8_t size = 0;
	uint32_t digit;

	while (number)
	{
		digit = number % 10;
		number /= 10;
		buffer[size++] = digit + 48;
	}

	buffer[size] = 0;

	return size;
}

int main(void)
{
	IM_GPIO_INIT();
	/* Initialize SPI1 */
	IM_SPI1_GPIOA_init();
	IM_SPI1_config();

	lcd_init();
	init_graphic_tables();

	char 			score_str[10];
	bool 			playing;
	int 			score;

// screen 1
	fill_rectangle(0, 0, 220, 176, COLOR_BACKGROUND);
	draw_string(75, 50, COLOR_BLACK, 2, "KMH2");
	draw_string(23, 100, COLOR_BLACK, 1, "Press fire to start");

	for (;;)
	{
		if (is_select_pressed())
		{
			break;
		}
	}
restart:
	Level_Manager 	lvl;
	playing = true;
	speaker_music_start();
	fill_rectangle(0, 0, 220, 176, COLOR_BACKGROUND);
// main game
	while (playing)
	{
		playing = !lvl.tick();
		lvl.draw();
	}

// end screen
	score = lvl.get_score();
	uint_to_str(score_str, score);

	fill_rectangle(0, 0, 220, 176, COLOR_BACKGROUND);
	draw_string(30, 50, COLOR_RED, 2,"You lost!");
	draw_string(70, 100, COLOR_BLACK, 1, "Score: ");
	if (score)
	{
		draw_string(130, 100, COLOR_BLACK, 1, score_str);
	}
	else
	{
		draw_string(130, 100, COLOR_BLACK, 1, "0...");
	}
	draw_string(15, 115, COLOR_BLACK, 1,"Press fire to restart");
	speaker_music_lose();

	for (;;)
	{
		if (is_select_pressed())
		{
			goto restart;
		}
	}
}
