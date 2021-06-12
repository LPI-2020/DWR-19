#include "fifo.h"
#include "stdint.h"


//init an empty stfifo
//
int8_t fifo_init(ST_FIFO *stfifo)
{
	__disable_irq();
	
	if(stfifo->fifo_dead==0)
	{
		__enable_irq();
		return EPERM;
	}
	
	stfifo->index_write = 0;
	stfifo->index_read = 0;
	stfifo->fifo_dead=0;
	
	__enable_irq();
	return EXIT_SUCESS;
}


//kill the fifo
//
int8_t fifo_kill(ST_FIFO *stfifo)
{
	__disable_irq();
	
	if(stfifo->fifo_dead)
	{
		__enable_irq();
		return EPERM;
	}
		
	stfifo->fifo_dead=1;	      	//stfifo cannot be used until stfifo_init 
	
	__enable_irq();
	return EXIT_SUCESS;
}

//insert element on our fifo
//
int8_t fifo_push(ST_FIFO *stfifo,uint8_t c)
{
  __disable_irq();
	
	if (c > MAX_CHAR_VAL)
	{
		__enable_irq();
		return EICHAR;
	}
	
	if(stfifo->fifo_dead)
	{
		__enable_irq();
		return EPERM;
	}
		
	//is stfifo full?
	if((stfifo->index_write-stfifo->index_read)>=stfifo->fifo_len)
	{
		__enable_irq();
		return ENOBUFS;					//error stfifo full
	}
	
	stfifo->fifo[stfifo->index_write & (stfifo->fifo_len-1)]=c;
	stfifo->index_write++;
	
	__enable_irq();
	return EXIT_SUCESS;
}


//remove first element from fifo
//

int8_t fifo_pop(ST_FIFO *stfifo)
{
	__disable_irq();
	
	uint8_t c;
	
	if(stfifo->fifo_dead)
	{
		__enable_irq();
		return EPERM;
	}
	
	if(!(stfifo->index_write^stfifo->index_read))
	{
		__enable_irq();
		return ENODATA;
	}
	
	c=stfifo->fifo[stfifo->index_read & stfifo->fifo_len-1];
	stfifo->index_read++;
	
	__enable_irq();
	return c;	
}

//remove last element from fifo
//
int8_t fifo_pop_last(ST_FIFO *stfifo)
{
	__disable_irq();
	
	uint8_t c;
	
	if(stfifo->fifo_dead)
	{
		__enable_irq();
		return EPERM;
	}
	
	if(!(stfifo->index_write^stfifo->index_read))
	{
		__enable_irq();
		return ENODATA;
	}
	
	c=stfifo->fifo[stfifo->index_write];
	stfifo->index_write--;
	
	__enable_irq();
	return c;	
}


//number of elements in our fifo
//
int16_t fifo_size(ST_FIFO *stfifo)
{
	__disable_irq();
	
	if(stfifo->fifo_dead)
	{
		__enable_irq();
		return EPERM;
	}
	
	__enable_irq();
	return (stfifo->index_write-stfifo->index_read);
}
