/*const
 * DrawableContent.cpp
 *
 *  Created on: Mar 12, 2023
 *      Author: imanthoc
 */

#include "Drawable_Content.h"

Drawable_Content::Drawable_Content(unsigned int btmap[18][15], int x, int y, int s):
	width(15),
	height(18)
{
	for (int i = 0; i < 18; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			bitmap[i][j] = btmap[i][j];
		}
	}

	current_x = next_x = x;
	current_y = next_y = y;
	scale = s;
}
