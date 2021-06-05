/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "fifo.h"
#include "stdlib.h"
#include <string.h>

#define CR 13
#define BCKSP 0x08
#define DollarSign 0x24
#define ESC 0x1b

ST_FIFO RxFifo;
ST_FIFO TxFifo;

uint8_t Message[BUFFER_SIZE];

static char char_received;

int Rx_string_processing;
int Tx_string_transmitting;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PB15     ------> USART1_RX
    PB6     ------> USART1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PB15     ------> USART1_RX
    PB6     ------> USART1_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_15|GPIO_PIN_6);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOD, STLK_RX_Pin|STLK_TX_Pin);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void init_UART3(){
	HAL_UART_Receive_IT(&huart3, (uint8_t*)&char_received , 1);
}

void init_UART1(){
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&char_received , 1);
}

void printmsg(char* ptr)
{
	while (Tx_string_transmitting)
		;
	while(*ptr!='\0')
	{
		fifo_push(&TxFifo,*ptr);
		ptr++;
	}
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_TC);
}


void newMessage()
{
	uint8_t local_index = 0;
	uint8_t local_char;
	
	while (fifo_size(&RxFifo) != 0)
	{
	local_char = fifo_pop(&RxFifo);
	
	Message[local_index] = local_char;
	local_index++;
	}
	Message[local_index-1] = '\0';			//deletes input CR 
	Rx_string_processing = 1;												 						  //tells system that a string ready to be processed
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
	
	if(huart->Instance == USART3){
		
		if(Rx_string_processing)                   //string being processed?
		{
			init_UART3();
			return;
		}
	
		HAL_UART_Receive_IT(&huart3, (uint8_t*)&char_received , 1);      //receives char

	
		if(char_received == CR)
		{
			HAL_UART_Transmit_IT(&huart3,(uint8_t*) &char_received,1);   	//Echoes char received
			fifo_push(&RxFifo, char_received);
			newMessage();                                      						//Copies string received to Message[] array
			init_UART3();
			return;
		}
		
		
		if(char_received == BCKSP)
		{
			if(fifo_size(&RxFifo) != 0)
			{
				HAL_UART_Transmit_IT(&huart3, (uint8_t*)&char_received,1);   					//Echoes char received
				fifo_pop_last(&RxFifo);
				init_UART3();
				return;
			}
			else
			{
				init_UART3();
				return;
			}
		}
		
		if(char_received == ESC || char_received == DollarSign)         					 //char_received is $ or backspace ?
		{
			char str[BUFFER_SIZE];
			uint8_t index = 0;
			
			
			while(fifo_pop(&RxFifo) != ENODATA)
			{																					
				str[index] = BCKSP;																		//removes all chars from Rxfifo
				index++;
			}
			
			HAL_UART_Transmit_IT(&huart3,(uint8_t*)&str, index);
			//printmsg(str);																			        						  //clears all transmitted chars
			
			if(char_received == DollarSign)
			{
				fifo_push(&RxFifo, DollarSign);                          								//push char '$'
				fifo_push(&RxFifo, CR);                            											//push char CR
				newMessage();																														// sends command "$\r" to parser 
				init_UART3();
				return;
			}
			
			init_UART3();
			return;
		}
	 
		if(char_received == '\\')
			{
					HAL_UART_Transmit_IT(&huart3,(uint8_t*) &char_received,1);       //Echoes char received
									
					while(fifo_pop(&RxFifo) != ENODATA)
					;
					
					fifo_push(&RxFifo, char_received);
					fifo_push(&RxFifo, CR);
					newMessage();                                                              //Copies string received to Message[] array
					init_UART3();
					return;
			}
			
		if(char_received == '/')
			{
					HAL_UART_Transmit_IT(&huart3,(uint8_t*) &char_received,1);       //Echoes char received
									
					while(fifo_pop(&RxFifo) != ENODATA)
					;
					
					fifo_push(&RxFifo, char_received);
					fifo_push(&RxFifo, CR);
					
					newMessage();                                                              //Copies string received to Message[] array
					init_UART3();
					return;
			}
		
		if(fifo_size(&RxFifo) != BUFFER_SIZE)										//if Rx buffer not full it pushes the char. If its full char is discarded
		{
			HAL_UART_Transmit_IT(&huart3,(uint8_t*)&char_received,1);
			fifo_push(&RxFifo, char_received);
			init_UART3();
			return;
		}
		
		init_UART3();
		return;
	}
	if(huart->Instance == USART1){
		
		HAL_UART_Receive_IT(&huart1, (uint8_t*)&char_received , 1); 
		HAL_UART_Transmit_IT(&huart3,(uint8_t*)&char_received,1);
		
	}
		
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart){
	
	uint8_t local_char;
	
	if(huart->Instance == USART3){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);              //blink Red LED
		
		if(fifo_size(&TxFifo) == 0)													
		{
			Tx_string_transmitting = 0;
			return;
		}
		
		Tx_string_transmitting = 1;												 	//tells system that a string is being trasmitted
		local_char = fifo_pop(&TxFifo);											//pops char from TxFifo
		HAL_UART_Transmit_IT(&huart3, &local_char, 1);			//transmits char
		return;
	}	
		
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
