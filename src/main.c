// Description----------------------------------------------------------------|
/*
 *
 */
// DEFINES AND INCLUDES-------------------------------------------------------|

#include <stdlib.h>
#define STM32F051												 //COMPULSORY
#include "stm32f0xx.h"										  	 //COMPULSORY
#include "lcd_stm32f0.h"
#include <stdio.h>

//FUNCTION DECLARATIONS -----------------------------------------------------|

//void main(void);                                                   //COMPULSORY
void display_on_LCD(uint8_t number);
void init_LCD(void);
void init_LEDs(void);
void display_on_LEDs(uint8_t number);
void init_switches(void);
void delay(unsigned int microseconds);

// MAIN FUNCTION -------------------------------------------------------------|

void main(void){
	init_LCD();
	init_LEDs();
	init_switches();
	//display_on_LCD(122);
	//display_on_LEDs(12);
	lcd_command(CLEAR);
	display_on_LCD(0);
	uint8_t count = 0;
	while(1){
		if ((GPIOA -> IDR & GPIO_IDR_1)==0){
			if(count<255){
				lcd_command(CLEAR);
				count += 1;
				display_on_LCD(count);
				display_on_LEDs(count);
				delay(25000);
			}
		}
		if ((GPIOA -> IDR & GPIO_IDR_2)==0) {
			if (count>0){
				lcd_command(CLEAR);
				count -= 1;
				display_on_LEDs(count);
				display_on_LCD(count);
				delay(25000);
			}
		}
	}
}

// OTHER FUNCTIONS -----------------------------------------------------------|

void display_on_LCD(uint8_t number){
	char str[3];
	sprintf(str, "%d", number);

	lcd_putstring(str);
}

void display_on_LEDs(uint8_t number){
	GPIOB -> ODR = number;
}

void init_LEDs(void){

	RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;

	GPIOB -> MODER |= (
			GPIO_MODER_MODER0_0 |
			GPIO_MODER_MODER1_0 |
			GPIO_MODER_MODER2_0 |
			GPIO_MODER_MODER3_0 |
			GPIO_MODER_MODER4_0 |
			GPIO_MODER_MODER5_0 |
			GPIO_MODER_MODER6_0 |
			GPIO_MODER_MODER7_0);
}

void init_switches(void){

	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA -> MODER &= (
			~GPIO_MODER_MODER1 &
			~GPIO_MODER_MODER2);

	GPIOA -> PUPDR |= (
			GPIO_PUPDR_PUPDR1_0 |
			GPIO_PUPDR_PUPDR2_0);
}

