/*
 * I2C_LCD.h
 *
 *  Created on: 2019. 9. 4.
 *      Author: LYW
 */

#ifndef SRC_I2C_LCD_H_
#define SRC_I2C_LCD_H_


#include "main.h"
#include <string.h>

#define I2C_LCD_ADDR	( 0x3f << 1 )
#define BACKLIGHT_ON	0x08

/* LCD command */
#define DISPLAY_ON		0x0C
#define DISPLAY_OFF		0x08
#define CLEAR_DISPLAY	0x01	// Delay 2msec
#define RETURN_HOME		0x02

void I2C_LCD_Command(uint8_t command);
void I2C_LCD_Data(uint8_t data);
void I2C_LCD_Init();
void I2C_LCD_String(uint8_t *str);
void move_Cursor(uint8_t row, uint8_t col);
void I2C_LCD_XY_String(uint8_t row, uint8_t col, uint8_t *str);
void I2C_LCD_Clear();


#endif /* SRC_I2C_LCD_H_ */
