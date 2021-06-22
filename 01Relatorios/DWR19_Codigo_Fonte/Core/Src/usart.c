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
//#include "special_keys.h"

#define UART_Bluetooth (huart1)

uart_t debug_uart = {
		.uart = &huart3,
		.Rx_index = 0,
		.Rx_flag = 0
};

uart_t bluet_uart = {
		.uart = &UART_Bluetooth,
		.Rx_index = 0,
		.Rx_flag = 0
};

volatile uint8_t cmd_received = 0;

volatile uint8_t c; // received char

/******************************************************************************
Function prototypes
******************************************************************************/

static void process_as_data(uart_t *huart);
//static char process_as_control(void);

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
    GPIO_InitStruct.Pin = BLUET_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART1;
    HAL_GPIO_Init(BLUET_RX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BLUET_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(BLUET_TX_GPIO_Port, &GPIO_InitStruct);

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
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
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
    HAL_GPIO_DeInit(GPIOB, BLUET_RX_Pin|BLUET_TX_Pin);

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
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/******************************************************************************
@brief	 	 Receives a char by UART serial port
******************************************************************************/
char UART_Receive(uart_t *huart)
{
	if(c != NEW_LINE) // Is this the end of reception?
		Rx_UART_init(huart); // prepare for next character

	if(huart->Rx_index == (RX_BUFF_LEN - 1)) // Is the buffer full?
		// Treat as 'CR'
		c = NEW_LINE;
	
//	if(c == 0) // Is the received char a control char?
//		return (char)(-1);
	
	if(c == NEW_LINE)
	{
		huart->Rx_Buffer[huart->Rx_index] = 0;	// mark end of string
		huart->Rx_index = 0;
		cmd_received = 1;
		return (char)(-1);
	}

	// Its not a special character
	process_as_data(huart);

	return c;
}

/******************************************************************************
@param  	 char received 'c' via UART

@brief	 	 process the char received as a special character
******************************************************************************/

//static char process_as_control(void)
//{
//	const Special_Key_t *s_key_ptr = s_key_list;
//
//	while(s_key_ptr->code)
//	{
//		if(c == (s_key_ptr->code))// Is this a control char?
//		{
//			// Execute this control char callback
//			s_key_ptr->fn();
//			return 0; // processed as control
//		}
//		s_key_ptr++;
//	}
//	return (char)(-1);
//}

/******************************************************************************
@param  	 char received 'c' via UART

@brief	 	 process the char received as a data character
******************************************************************************/

static void process_as_data(uart_t *huart)
{
	// add received char to Rx_Buffer
	huart->Rx_Buffer[huart->Rx_index] = c;
	huart->Rx_index++;
}

// set the interrupt for UART
void Rx_UART_init(uart_t *huart)
{
	HAL_UART_Receive_IT(huart->uart, (uint8_t*)&c, 1);
}

//implementation of UART ISR
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// debug uart
	if (huart->Instance == debug_uart.uart->Instance)
		debug_uart.Rx_flag = 1;

	// bluetooth uart
	else if (huart->Instance == bluet_uart.uart->Instance)
		bluet_uart.Rx_flag = 1;

//	HAL_UART_Receive_IT(huart, (uint8_t*)&c, 1);
}

//implementation of UART ISR
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
//{
//	if (huart->Instance == USART3) //current UART?
//		Tx_flag = 1;
//}

/******************************************************************************
@brief	 	 Sends a char by UART - Polling (Waits for UART_Tx to transmit
							queued data
@param  	 Char to be transmitted
******************************************************************************/
void UART_putchar(uart_t *huart, char ch)
{
	while(huart->uart->gState == HAL_UART_STATE_BUSY_TX) // Waits for UART_Tx to transmit queued data
		;
	
	c = ch; // 'ch' cannot be used to transmit since its local to this function. Content may be lost
	HAL_UART_Transmit_IT(huart->uart, (uint8_t*)&c, 1);
}

/******************************************************************************
@brief	 	 Sends a string by UART - Polling (Waits for UART_Tx to transmit
							queued data
@param  	 String to be transmitted
******************************************************************************/
void UART_puts(uart_t *huart, const char *str)
{
	if((str == NULL) || (str[0] == 0))	// string empty?
		return;
	
	int len = strlen(str);
	if(len > TX_BUFF_LEN)		// string size bigger than the max size of Tx_Buffer?
		return;

	while(huart->uart->gState == HAL_UART_STATE_BUSY_TX) // Waits for UART_Tx to transmit queued data
		;
	
	strcpy((char *)huart->Tx_Buffer, str);	// send string 'str' to 'TX_Buffer'
	HAL_UART_Transmit_IT(huart->uart, (uint8_t*)huart->Tx_Buffer, len);
}

//void UART_puts(const char *s)
//{
//	const char *ptr = s;
//	
//	if((s == NULL) || (s[0] == 0))
//		return;
//	
//	while (*ptr)
//	{
//		UART_putchar(*ptr);
//		ptr++;
//	}
//}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
