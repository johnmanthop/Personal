/*
 * Renderer.h
 *
 *  Created on: Mar 12, 2023
 *      Author: imanthoc
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <stdint.h>
#include "Drawable_Content.h"

class Renderer {
public:
	static void draw(const Drawable_Content &content);
};

#endif /* INC_RENDERER_H_ */
