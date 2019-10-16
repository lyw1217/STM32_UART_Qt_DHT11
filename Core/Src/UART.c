#include "main.h"
#include <string.h>
#include <stdio.h>
#include "DHT11.h"
#include "I2C_LCD.h"
#include "timer.h"
#include "servo.h"

#define BUFFER_MAX	16
#define COMMAND_MAX 64

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

volatile uint8_t rx_data_3 = 0;

uint8_t rx_cmd_flag_3 = 0;
uint8_t command_index_3 = 0, rx_index_3 = 0;
uint8_t cmd_count = 0;

uint8_t command_buff_3[COMMAND_MAX][BUFFER_MAX] = {{0,0},};

extern uint8_t update_flag;
extern uint8_t start_flag;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart3){
		if(rx_index_3 < (BUFFER_MAX - 1)){
			if((rx_data_3 == '\n') || (rx_data_3 == '\r')){
				cmd_count++;
				rx_index_3 = 0;
				command_index_3++;
				command_index_3 %= COMMAND_MAX;
			}else{			
				command_buff_3[command_index_3][rx_index_3++] = rx_data_3;
				command_buff_3[command_index_3][rx_index_3] = '\0';
			}
		}
		else{
			printf("overflow buffer!!\n");
			rx_index_3 = 0;
		}
		HAL_UART_Receive_IT(&huart3, &rx_data_3, 1);
	}
}

//----------------- MAIN start -----------------//
void UART_main(){
	I2C_LCD_Init();
	timer_Init();
	servo_Init();
	DHT11_Init();
	HAL_UART_Receive_IT(&huart3, &rx_data_3, 1);
	I2C_LCD_XY_String(0, 0, "INITIALIZING");
	uint8_t process_index = 0;
	char buff[20];
	char *token;

	DHT11 dht;
	
	get_DHT11(&dht);
	I2C_LCD_Clear();

	printf("STM32 start\n");

	while(1){
		HAL_Delay(100);
		if(cmd_count){
			cmd_count--;
			printf("%s\n", command_buff_3[process_index]);
			I2C_LCD_XY_String(0, 0, command_buff_3[process_index]);
			HAL_GPIO_TogglePin(onBoard_Blue_LED_GPIO_Port, onBoard_Blue_LED_Pin);

			if( !strcmp((const char *)command_buff_3[process_index], "led on") ){
				HAL_GPIO_WritePin(onBoard_Green_LED_GPIO_Port, onBoard_Green_LED_Pin, GPIO_PIN_SET);
			}
			else if( !strcmp((const char *)command_buff_3[process_index], "led off") ){
				HAL_GPIO_WritePin(onBoard_Green_LED_GPIO_Port, onBoard_Green_LED_Pin, GPIO_PIN_RESET);
			}
			else if( !strcmp((const char *)command_buff_3[process_index], "led toggle") ){
				HAL_GPIO_TogglePin(onBoard_Green_LED_GPIO_Port, onBoard_Green_LED_Pin);
			}
			else if( !strcmp((const char *)command_buff_3[process_index], "get temp") ){
				printf("Temp : %02d.%01d Humi : %02d.%01d\n", dht.i_Tmp, dht.d_Tmp, dht.i_RH, dht.d_RH);
				sprintf(buff, "T: %02d.%01d H: %02d.%01d", dht.i_Tmp, dht.d_Tmp, dht.i_RH, dht.d_RH);
				I2C_LCD_XY_String(1, 0, buff);
			}else if( !strncmp((const char *)command_buff_3[process_index], "[servo]", 7) ){
				token = strtok((const char *)command_buff_3[process_index], "]");
				token = strtok(NULL, "]");
				uint8_t degree = atoi(token);
				printf("Servo Run : %d\n", degree);
				servo_Run(degree);
			}
			else if( !strncmp((const char *)command_buff_3[process_index], "start_flag", 10) ){
				token = strtok((const char *)command_buff_3[process_index], "=");
				token = strtok(NULL, "=");
				start_flag = atoi(token);
			}

		}
		process_index++;
		process_index %= COMMAND_MAX;

		if(update_flag && start_flag){
			get_DHT11(&dht);
			printf("[ti]%d\n", dht.i_Tmp);
			printf("[td]%d\n", dht.d_Tmp);
			sprintf(buff, "T: %02d.%01d H: %02d.%01d", dht.i_Tmp, dht.d_Tmp, dht.i_RH, dht.d_RH);
			I2C_LCD_Clear();
			I2C_LCD_XY_String(1, 0, buff);
			update_flag = 0;
		}
	}
}
//----------------- MAIN   end -----------------//
