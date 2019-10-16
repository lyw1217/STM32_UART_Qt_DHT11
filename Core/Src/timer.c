#include "main.h"
#include "timer.h"

// extern : already declared in main.c
extern TIM_HandleTypeDef htim2;

uint8_t update_flag = 1;
uint8_t start_flag = 0;

// timer2 => prescaler 16 , OCR 1000 ==> 1ms count

volatile uint16_t msec = 0;
uint8_t sec = 0, min = 0, hour = 0;
// what to do in an interrup
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	// timer2 is interrupted (htim == &htim2)
	if(htim == &htim2){
		msec++;
		if(msec >= 1000){
			msec = 0;
			sec++;
			if(sec % 3 == 0 && start_flag){
				update_flag = 1;
			}
			if(sec >= 60){
				sec = 0;
				min++;
				if(min >= 60){
					min = 0;
					hour++;
					if(hour >= 24) hour = 0;
				}
			}
		}
	}
}

void timer_Init(){
	// interrupt timer start
	HAL_TIM_Base_Start_IT(&htim2);
}
