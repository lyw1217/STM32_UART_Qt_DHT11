#include "DHT11.h"

extern TIM_HandleTypeDef htim2;

//---------- Function define start ----------//
void DHT11_Init(){
	HAL_GPIO_WritePin(DHT11_data_GPIO_Port, DHT11_data_Pin, GPIO_PIN_SET);
	HAL_Delay(3000);
}

void DHT11_Trigger(){
	// start signal and Pull Down for at least 18ms 
	HAL_GPIO_WritePin(DHT11_data_GPIO_Port, DHT11_data_Pin, GPIO_PIN_RESET);
	HAL_Delay(20);
	
	// Pull Up and wait for DHT response (20~40 us)
	HAL_GPIO_WritePin(DHT11_data_GPIO_Port, DHT11_data_Pin, GPIO_PIN_SET);
	delay_us(5);
}

// Set DHT11_data_Pin => INPUT
void DHT11_Data_Input(){
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/*Configure GPIO pin : DHT11_data_Pin */
	GPIO_InitStruct.Pin = DHT11_data_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // set input
	
	// external pull up registor in DHT11 Module
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DHT11_data_GPIO_Port, &GPIO_InitStruct);
}

// Set DHT11_data_Pin => OUTPUT
void DHT11_Data_Output(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/*Configure GPIO pin : DHT11_data_Pin */
	GPIO_InitStruct.Pin = DHT11_data_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // set output
	
	// external pull up registor in DHT11 Module
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DHT11_data_GPIO_Port, &GPIO_InitStruct);
}

uint8_t DHT11_Rx_Byte(){
	/* DHT11 Data format
	   8bit integral RH data + 8bit decimal RH data
	   + 8bit integral T data + 8bit decimal T data + 8bit checksum */
	
	uint8_t rx_data = 0;
	uint8_t retries = 0;
	
	for(int i = 0; i < 8; i++){
		// Start to transmit 1-bit data(50us)
		while( !HAL_GPIO_ReadPin(DHT11_data_GPIO_Port, DHT11_data_Pin) ){
			retries += 1;
			if(retries >= 100) break;
		}
		retries = 0;
		// 26-28us voltage-length means data = 0;
		delay_us(10);
		rx_data <<= 1;
		if(HAL_GPIO_ReadPin(DHT11_data_GPIO_Port, DHT11_data_Pin)){
			// if 1, set LSB 1
			rx_data |= 1;
		}
		while(HAL_GPIO_ReadPin(DHT11_data_GPIO_Port, DHT11_data_Pin)){
			retries += 1;
			if(retries >= 100) break;
		}
		retries = 0;
	}
	
	return rx_data;
}

void DHT11_Dumi_read(){
	uint8_t retries = 0;
	// pass HIGH signal after Trigger
	while( HAL_GPIO_ReadPin(DHT11_data_GPIO_Port, DHT11_data_Pin) ){
		retries += 1;
		if(retries >= 100) break;
	}
	retries = 0;
	// Waiting for DHT response signal(LOW) and keep it for 80us
	while( !HAL_GPIO_ReadPin(DHT11_data_GPIO_Port, DHT11_data_Pin) ){
		retries += 1;
		if(retries >= 100) break;
	}
	retries = 0;
	// DHT pulls up voltage and keep it for 80us
	while( HAL_GPIO_ReadPin(DHT11_data_GPIO_Port, DHT11_data_Pin) ){
		retries += 1;
		if(retries >= 100) break;
	}
	
	// and Start Data transmission
}

void get_DHT11(DHT11 *dht){
	DHT11_Trigger();

	DHT11_Data_Input();
	DHT11_Dumi_read();

	// DHT11 data read(data format)
	dht->i_RH = DHT11_Rx_Byte();
	dht->d_RH = DHT11_Rx_Byte();
	dht->i_Tmp = DHT11_Rx_Byte();
	dht->d_Tmp = DHT11_Rx_Byte();
	DHT11_Rx_Byte();

	DHT11_Data_Output();
	HAL_GPIO_WritePin(DHT11_data_GPIO_Port, DHT11_data_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	return;
}
//---------- Function define end ----------//
