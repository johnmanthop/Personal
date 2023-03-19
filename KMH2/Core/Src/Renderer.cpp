/*
 * Renderer.cpp
 *
 *  Created on: Mar 12, 2023
 *      Author: imanthoc
 */

#include "Renderer.h"
#include "ILI9225.h"

void Renderer::draw(const Drawable_Content &content)
{
	fill_rectangle(content.current_x,
				   content.current_y,
				   content.current_x + 40, //experimentally found magic values
				   content.current_y + 40, //i have no idea why they are what they are
				   COLOR_BACKGROUND
	);

	IM_draw_bitmap(content.next_x, content.next_y, content.scale, content.bitmap);
}

