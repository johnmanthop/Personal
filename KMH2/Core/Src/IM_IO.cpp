/*
 * IM_IO.cpp
 *
 *  Created on: Mar 12, 2023
 *      Author: imanthoc
 */

#include "stm32f401xe.h"
#include "IM_IO.h"
#include "ILI9225.h"

#define CS (1U << 9)
#define RS (1U << 8)

void IM_GPIO_INIT()
{
	RCC->AHB1ENR |= (1U << 0);
}

// peripheral init
void IM_SPI1_GPIOA_init()
{
	/*
	 * player io:
	 * PA0  -> speaker driver
	 * PC1  -> left
	 * PB0  -> right
	 * PA4  -> fire / select
	 *
	 * spi:
	 * PA5  -> clk
	 * PA6  -> MISO
	 * PA7  -> MOSI
	 * PA8  -> RS
	 * PA9  -> CS
	 * PA10 -> RST
	 */
	// enable gpioa b and c
	RCC->AHB1ENR |= (1U << 0) | (1U << 1) | (1U << 2);
	/* SPI init */
	// set PA5 to alternate function
	GPIOA->MODER &= ~(1U << 10);
	GPIOA->MODER |=  (1U << 11);
	// same for PA6 and PA7
	GPIOA->MODER &= ~(1U << 12);
	GPIOA->MODER |=  (1U << 13);

	GPIOA->MODER &= ~(1U << 14);
	GPIOA->MODER |=  (1U << 15);

	// set pa8, 9 and 10 to output
	GPIOA->MODER |=  (1U << 16);
	GPIOA->MODER &= ~(1U << 17);

	GPIOA->MODER |=  (1U << 18);
	GPIOA->MODER &= ~(1U << 19);

	GPIOA->MODER |=  (1U << 20);
	GPIOA->MODER &= ~(1U << 21);

	// set alternate function type for all pins
	GPIOA->AFR[0] |=  (1U << 20);
	GPIOA->AFR[0] &= ~(1U << 21);
	GPIOA->AFR[0] |=  (1U << 22);
	GPIOA->AFR[0] &= ~(1U << 23);

	GPIOA->AFR[0] |=  (1U << 24);
	GPIOA->AFR[0] &= ~(1U << 25);
	GPIOA->AFR[0] |=  (1U << 26);
	GPIOA->AFR[0] &= ~(1U << 27);

	GPIOA->AFR[0] |=  (1U << 28);
	GPIOA->AFR[0] &= ~(1U << 29);
	GPIOA->AFR[0] |=  (1U << 30);
	GPIOA->AFR[0] &= ~(1U << 31);

	/* Generic IO init */
	// pa0
	GPIOA->MODER |=  (1U << 0);
	GPIOA->MODER &= ~(1U << 1);
	// pb0
	GPIOB->MODER &= ~(1U << 0);
	GPIOB->MODER &= ~(1U << 1);
	// pc1
	GPIOC->MODER &= ~(1U << 2);
	GPIOC->MODER &= ~(1U << 3);
	// pa4
	GPIOA->MODER &= ~(1U << 8);
	GPIOA->MODER &= ~(1U << 9);

	/* Set to pull down */
	//pb0
	GPIOB->PUPDR &= ~(1U << 0);
	GPIOB->PUPDR |=  (1U << 1);
	//pc1
	GPIOC->PUPDR &= ~(1U << 2);
	GPIOC->PUPDR |=  (1U << 3);
	// pa4
	GPIOA->PUPDR &= ~(1U << 8);
	GPIOA->PUPDR |=  (1U << 9);
}

void set_SPI1_CR1(uint8_t bit)
{
	SPI1->CR1 |=  (1U << bit);
}

void reset_SPI1_CR1(uint8_t bit)
{
	SPI1->CR1 &= ~(1U << bit);
}

void IM_SPI1_config()
{
	RCC->APB2ENR |= (1U << 12);		// enable clk to spi1

	set_SPI1_CR1(0);	// set clk phase
	set_SPI1_CR1(1);	// set clk polarity
	set_SPI1_CR1(2);	// set to master config
	reset_SPI1_CR1(3); reset_SPI1_CR1(4); reset_SPI1_CR1(5);	// set baud rate to clk/2
	reset_SPI1_CR1(7);	// msb first
	set_SPI1_CR1(8);
	set_SPI1_CR1(9);
	reset_SPI1_CR1(11);	// 8 bit transmition
	reset_SPI1_CR1(13);	// disable crc
	set_SPI1_CR1(15);	// 1 line bidirectional
	set_SPI1_CR1(14);	// transmit only
	set_SPI1_CR1(6);	// enable module
}

uint8_t global;

void IM_SPI1_Transmit(unsigned char *data, uint32_t size)
{
	uint32_t temp;

	for (uint32_t i = 0; i < size; ++i)
	{
		while (!(SPI1->SR & (1U << 1)));
		SPI1->DR = (uint32_t)data[i];
	}

	while (!(SPI1->SR & (1U << 1))) { global = 0; }
	while (SPI1->SR & (1U << 7)) { global = 0; }

	temp = SPI1->DR;
	temp = SPI1->SR;

	global = temp;
}

void enable_cs()
{
	GPIOA->ODR &= ~CS;
}

void disable_cs()
{
	GPIOA->ODR |= CS;
}

void IM_GPIO_SetPin(GPIO_TypeDef *base, uint16_t pin)
{
	base->ODR |= pin;
}

void IM_GPIO_ResetPin(GPIO_TypeDef *base, uint16_t pin)
{
	base->ODR &= ~pin;
}

bool is_left_pressed()
{
	return (GPIOC->IDR & (1U << 1));
}

bool is_right_pressed()
{
	return (GPIOB->IDR & (1U << 0));
}

bool is_select_pressed()
{
	return (GPIOA->IDR & (1U << 4));
}

void speaker_fire()
{
	for (int i = 0; i < 20; ++i)
	{
		GPIOA->ODR |=  (1U << 0);
		delay_ms(50);
		GPIOA->ODR &= ~(1U << 0);
		delay_ms(50);
	}
}

void speaker_music_lose()
{
	for (int i = 0; i < 100; ++i)
	{
		GPIOA->ODR |=  (1U << 0);
		delay_ms(25);
		GPIOA->ODR &= ~(1U << 0);
		delay_ms(25);
	}
	for (int i = 0; i < 100; ++i)
	{
		GPIOA->ODR |=  (1U << 0);
		delay_ms(37);
		GPIOA->ODR &= ~(1U << 0);
		delay_ms(37);
	}
}

void speaker_music_start()
{
	for (int i = 0; i < 100; ++i)
	{
		GPIOA->ODR |=  (1U << 0);
		delay_ms(37);
		GPIOA->ODR &= ~(1U << 0);
		delay_ms(37);
	}
	for (int i = 0; i < 100; ++i)
	{
		GPIOA->ODR |=  (1U << 0);
		delay_ms(25);
		GPIOA->ODR &= ~(1U << 0);
		delay_ms(25);
	}
}
