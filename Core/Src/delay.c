#include "delay.h"

void delay_us(uint32_t _us){
	if(_us > 1){
		volatile uint32_t count = _us*6 - 4;
		while(count--);
	}
	else{
		volatile uint32_t count = 4;
		while(count--);
	}
}