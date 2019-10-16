/*
 * DHT11.h
 *
 *  Created on: 2019. 9. 2.
 *      Author: LYW
 */

#ifndef SRC_DHT11_H_
#define SRC_DHT11_H_

#include "main.h"
#include "delay.h"

typedef struct{
	uint8_t i_RH, d_RH, i_Tmp, d_Tmp;
} DHT11;

//---------- function prototype ----------//
void DHT11_Init();
void DHT11_Trigger();
void DHT11_Data_Input();
void DHT11_Data_Output();
uint8_t DHT11_Rx_Byte();
void DHT11_Dumi_read();
void get_DHT11(DHT11 *dht);

#endif /* SRC_DHT11_H_ */
