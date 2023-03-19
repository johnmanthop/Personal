/*
 * bitmaps.h
 *
 *  Created on: Mar 12, 2023
 *      Author: imanthoc
 */

#ifndef INC_BITMAPS_H_
#define INC_BITMAPS_H_

#include "ILI9225.h"
#include <stdint.h>

extern unsigned int player_rgb[15][15];
extern unsigned int enemy_rgb[15][15];
//bitmap representation
//hopefully these will be saved in the flash instead of the ram

static const uint8_t player_bitmap_binary[15][15] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 3, 3, 1, 1 },
	{ 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 3, 3, 1, 1 },
	{ 0, 1, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0 },
	{ 3, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0 },
	{ 3, 1, 1, 1, 1, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0 },
	{ 3, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0 },
	{ 0, 1, 1, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 3, 3, 1, 1 },
	{ 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 3, 3, 1, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

static const uint8_t enemy_bitmap_binary[15][15] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 0 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2 },
	{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2 },
	{ 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 0 },
	{ 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0 },
	{ 1, 1, 2, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void translate_bitmap_to_rgb(const uint8_t bitmap[15][15], unsigned int rgb_buffer[15][15]);

#endif /* INC_BITMAPS_H_ */
