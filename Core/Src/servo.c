/*
 * servo.c
 *
 *  Created on: 2019. 9. 26.
 *      Author: LYW
 */
#include "main.h"

extern TIM_HandleTypeDef htim1;

void servo_Init(){
	// ���ֺ� 64, ARR = 5000 ���� �����ؼ� 20ms �ֱ⸦ ������־���
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	// CCR4�� ���� �������ָ� ��Ƽ�� ���� ����
	// ��Ƽ�� = ARR / CCR4 * 100
}

void servo_Run(uint8_t degree){
	uint16_t degValue = 0;

	degValue = (degree / 180.0) * 475 + 125;

	TIM1->CCR4 = degValue - 1;
	return;
}
