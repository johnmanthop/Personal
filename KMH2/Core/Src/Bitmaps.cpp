/*
 * bitmaps.cpp
 *
 *  Created on: Mar 12, 2023
 *      Author: imanthoc
 */

#include "Bitmaps.h"

void translate_bitmap_to_rgb(const uint8_t bitmap[15][15], unsigned int rgb_buffer[15][15])
{
	for (int i = 0; i < 18; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			if 		(bitmap[i][j] == 0) rgb_buffer[i][j] = COLOR_BACKGROUND;
			else if (bitmap[i][j] == 1) rgb_buffer[i][j] = COLOR_BLACK;
			else if (bitmap[i][j] == 2)	rgb_buffer[i][j] = COLOR_DARKBLUE;
			else if (bitmap[i][j] == 3) rgb_buffer[i][j] = COLOR_BROWN;
		}
	}
}
