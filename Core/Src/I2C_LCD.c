/*
 * I2C_LCD.c
 *
 *  Created on: 2019. 9. 4.
 *      Author: LYW
 */

#include "I2C_LCD.h"

extern I2C_HandleTypeDef hi2c1;

void I2C_LCD_Command(uint8_t command){
	uint8_t high_nibble, low_nibble;		// 8�� PIN�� �ƴ϶� 4�� PIN�� ����ϹǷ� 4bit �����͸� 2�� �������Ѵ�.
	uint8_t i2c_buffer[4];

	high_nibble = (command & 0xf0);			// command�� ���� 4��Ʈ
	low_nibble  = ((command << 4) & 0xf0);	// command�� ���� 4��Ʈ

	// 0x04 : EN 1, RS 0, RW 0			 0x08 : backlight On
	// 0x00 : EN 0, RS 0, RW 0
	i2c_buffer[0] = high_nibble | 0x04 | 0x08;
	i2c_buffer[1] = high_nibble | 0x00 | 0x08;
	i2c_buffer[2] = low_nibble  | 0x04 | 0x08;
	i2c_buffer[3] = low_nibble  | 0x00 | 0x08;

	// HAL_Transmit �Լ��� �����ϸ� HAL_OK�� ��ȯ
	while(HAL_I2C_Master_Transmit(&hi2c1, I2C_LCD_ADDR,
			i2c_buffer, 4, 100) != HAL_OK){
		HAL_Delay(1);
	}
}

void I2C_LCD_Data(uint8_t data){
	uint8_t high_nibble, low_nibble;		// 8�� PIN�� �ƴ϶� 4�� PIN�� ����ϹǷ� 4bit �����͸� 2�� �������Ѵ�.
	uint8_t i2c_buffer[4];

	high_nibble = (data & 0xf0);			// data�� ���� 4��Ʈ
	low_nibble  = ((data << 4) & 0xf0);		// data�� ���� 4��Ʈ

	// 0x05 : EN 1, RS 1, RW 0			 0x08 : backlight On
	// 0x01 : EN 0, RS 1, RW 0
	i2c_buffer[0] = high_nibble | 0x05 | 0x08;
	i2c_buffer[1] = high_nibble | 0x01 | 0x08;
	i2c_buffer[2] = low_nibble  | 0x05 | 0x08;
	i2c_buffer[3] = low_nibble  | 0x01 | 0x08;

	// HAL_Transmit �Լ��� �����ϸ� HAL_OK�� ��ȯ
	while(HAL_I2C_Master_Transmit(&hi2c1, I2C_LCD_ADDR,
			i2c_buffer, 4, 100) != HAL_OK){
		HAL_Delay(1);
	}
}

void I2C_LCD_Init(){
	I2C_LCD_Command(0x33);
	I2C_LCD_Command(0x32);
	I2C_LCD_Command(0x28);			// Function Set 4-bit mode
	I2C_LCD_Command(DISPLAY_ON);	// Display On/Off control
	I2C_LCD_Command(0x06);			// Entry mode set
	I2C_LCD_Command(CLEAR_DISPLAY);	// Clear display
	HAL_Delay(20);
}

void I2C_LCD_String(uint8_t *str){
	while(*str){
		I2C_LCD_Data(*str++);
	}
}

void move_Cursor(uint8_t row, uint8_t col){
	I2C_LCD_Command(0x80 | row << 6 | col);	// Set DDRAM Address
	// AC6~AC4�� row�� ǥ���ϹǷ� 6�� �̵��Ѵ�.
}

void I2C_LCD_XY_String(uint8_t row, uint8_t col, uint8_t *str){
	move_Cursor(row, col);
	I2C_LCD_String(str);
}

void I2C_LCD_XY_Data(uint8_t row, uint8_t col, uint8_t data){
	move_Cursor(row, col);
	I2C_LCD_Data(data);
}

void I2C_LCD_Clear(){
	I2C_LCD_Command(CLEAR_DISPLAY);	// Clear display
}
