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

#define UART1 1

ST_FIFO RxFifo_UART1;
ST_FIFO TxFifo_UART1;

uint8_t Message[BUFFER_SIZE];

static char char_received;

int Rx_string_processing;
int Tx_string_transmitting;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;

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
}

/* USER CODE BEGIN 1 */

void init_UART1(){
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&char_received , 1);
}

void printmsg(char* ptr)
{

	while (Tx_string_transmitting)
		;

		while(*ptr!='\0')
		{
			fifo_push(&TxFifo_UART1,*ptr);
			ptr++;
		}
		
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_TC);
}

void newMessage(ST_FIFO* stfifo)
{
	uint8_t local_index = 0;
	uint8_t local_char;
	
	while (fifo_size(stfifo) != 0)
	{
	local_char = fifo_pop(stfifo);
	
	Message[local_index] = local_char;
	local_index++;
	}
	Message[local_index-1] = '\0';																	//deletes input CR 
	Rx_string_processing = 1;												 						    //string is ready to be processed
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
	
	if(huart->Instance == USART1){
		
		HAL_UART_Receive_IT(&huart1, (uint8_t*)&char_received , 1); 
		//HAL_UART_Transmit_IT(&huart1,(uint8_t*)&char_received, 1);
		
		if(char_received == CR)
		{
			fifo_push(&RxFifo_UART1, char_received);
			newMessage(&RxFifo_UART1);                                  //Copies string received to Message[] array
			init_UART1();
			return;
		}
		
		if(fifo_size(&RxFifo_UART1) != BUFFER_SIZE)										//if Rx buffer not full it pushes the char. If its full char is discarded
		{
			fifo_push(&RxFifo_UART1, char_received);
			init_UART1();
			return;
		}
		
	}		
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart){
	
	uint8_t local_char;
	//UART1
	if(huart->Instance == USART1){
		
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);              
		
		if(fifo_size(&TxFifo_UART1) == 0)													
		{
			Tx_string_transmitting = 0;
			return;
		}
		
		Tx_string_transmitting = 1;												 	
		local_char = fifo_pop(&TxFifo_UART1);										
		HAL_UART_Transmit_IT(&huart1, &local_char, 1);			
		return;
	}		
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
