/*
 * DrawableContent.h
 *
 *  Created on: Mar 12, 2023
 *      Author: imanthoc
 */

#ifndef DRAWABLE_CONTENT_H_
#define DRAWABLE_CONTENT_H_

#include <stdint.h>

#define STEP 10

struct Drawable_Content {
public:
	int scale;
	int width, height;
	int current_x, current_y;
	int next_x, next_y;
	unsigned int bitmap[18][15];
public:
	Drawable_Content(unsigned int bitmap[18][15], int pos_x, int pos_y, int s);
};

#endif /* DRAWABLE_CONTENT_H_ */
