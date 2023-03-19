/*
 * IM_IO.h
 *
 *  Created on: Mar 12, 2023
 *      Author: imanthoc
 */

#ifndef IM_IO_H_
#define IM_IO_H_

#include <stdint.h>
#include "stm32f401xe.h"

void IM_GPIO_INIT();

void IM_GPIO_SetPin		(GPIO_TypeDef *base, uint16_t pin);
void IM_GPIO_ResetPin	(GPIO_TypeDef *base, uint16_t pin);

void IM_SPI1_GPIOA_init	();
void IM_SPI1_config		();
void IM_SPI1_Transmit	(uint8_t *data, uint32_t size);

void set_SPI1_CR1	(uint8_t bit);
void reset_SPI1_CR1	(uint8_t bit);

void enable_cs ();
void disable_cs();

bool is_left_pressed	();
bool is_right_pressed	();
bool is_select_pressed	();
void speaker_fire		();
void speaker_music_lose	();
void speaker_music_start();
#endif /* SRC_IM_IO_H_ */
