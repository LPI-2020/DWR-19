#include "fifo.h"
#include "stdint.h"
#include "usart.h"


//init an empty stfifo
//
int8_t fifo_init(ST_FIFO *stfifo)
{
	HAL_NVIC_DisableIRQ(USART1_IRQn);
	
	if(stfifo->fifo_dead==0)
	{
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		return EPERM;
	}
	
	stfifo->index_write = 0;
	stfifo->index_read = 0;
	stfifo->fifo_dead=0;
	
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	return EXIT_SUCESS;
}


//kill the fifo
//
int8_t fifo_kill(ST_FIFO *stfifo)
{
	HAL_NVIC_DisableIRQ(USART1_IRQn);
	
	if(stfifo->fifo_dead)
	{
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		return EPERM;
	}
		
	stfifo->fifo_dead=1;	      	//stfifo cannot be used until stfifo_init 
	
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	return EXIT_SUCESS;
}

//insert element on our fifo
//
int8_t fifo_push(ST_FIFO *stfifo,uint8_t c)
{
  HAL_NVIC_DisableIRQ(USART1_IRQn);
	
	if (c > MAX_CHAR_VAL)
	{
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		return EICHAR;
	}
	
	if(stfifo->fifo_dead)
	{
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		return EPERM;
	}
		
	//is stfifo full?
	if((stfifo->index_write-stfifo->index_read)>=stfifo->fifo_len)
	{
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		return ENOBUFS;					//error stfifo full
	}
	
	stfifo->fifo[stfifo->index_write & (stfifo->fifo_len-1)]=c;
	stfifo->index_write++;
	
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	return EXIT_SUCESS;
}


//remove first element from fifo
//

int8_t fifo_pop(ST_FIFO *stfifo)
{
	HAL_NVIC_DisableIRQ(USART1_IRQn);
	
	uint8_t c;
	
	if(stfifo->fifo_dead)
	{
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		return EPERM;
	}
	
	if(!(stfifo->index_write^stfifo->index_read))
	{
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		return ENODATA;
	}
	
	c=stfifo->fifo[stfifo->index_read & stfifo->fifo_len-1];
	stfifo->index_read++;
	
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	return c;	
}

//remove last element from fifo
//
int8_t fifo_pop_last(ST_FIFO *stfifo)
{
	HAL_NVIC_DisableIRQ(USART1_IRQn);
	
	uint8_t c;
	
	if(stfifo->fifo_dead)
	{
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		return EPERM;
	}
	
	if(!(stfifo->index_write^stfifo->index_read))
	{
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		return ENODATA;
	}
	
	c=stfifo->fifo[stfifo->index_write];
	stfifo->index_write--;
	
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	return c;	
}


//number of elements in our fifo
//
int16_t fifo_size(ST_FIFO *stfifo)
{
	HAL_NVIC_DisableIRQ(USART1_IRQn);
	
	if(stfifo->fifo_dead)
	{
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		return EPERM;
	}
	
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	return (stfifo->index_write-stfifo->index_read);
}
