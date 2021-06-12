#ifndef _FIFO_MODULE_
#define _FIFO_MODULE_

#include "limits.h"
#include "stdint.h"

#define BUFFER_SIZE 64
#define TBUFF_SIZE 64
#define RBUFF_SIZE 64
#define MAX_CHAR_VAL 127

// error codes 
#define EXIT_SUCESS	SCHAR_MIN			 //all OK
#define ENODATA			SCHAR_MIN +1   //error no Data in FIFO 
#define EIFLEN      SCHAR_MIN +2   //error invalid fifo LEN
#define ENOBUFS		  SCHAR_MIN +3 	 //error buffer full (FIFO Full)
#define EPERM				SCHAR_MIN	+4	 //operation not permited
#define EICHAR      SCHAR_MIN +5   //error invalid char 


//Struct to handle fifo
typedef struct st_fifo{
	unsigned char* fifo;             //pointer to FIFO buffer
	unsigned char index_write;
	unsigned char index_read;
	unsigned char fifo_len;          //tamanho da fifo
	unsigned char fifo_dead;
}ST_FIFO;



//
// init an empty FIFO
//
int8_t fifo_init(ST_FIFO *stfifo);

//
// kill a FIFO
//
int8_t fifo_kill(ST_FIFO *stfifo);

//
// insert an element into FIFO (push)
//
int8_t fifo_push(ST_FIFO *stfifo,uint8_t c);

//
// removes first element from FIFO
//
int8_t fifo_pop(ST_FIFO *stfifo);

//
// removes last element from FIFO
//
int8_t fifo_pop_last(ST_FIFO *stfifo);

//
// get number of elements on the FIFO
//
int16_t fifo_size(ST_FIFO *stfifo);




#endif //final  de _FIFO_MODULE_
