#include "USART.h"



static void closeUSART_ISR_Rx(USART_HandleTypedef_t* handle)
{
	handle->RxDataSize = 0;
	handle->pRxbuf = NULL;
	handle->Bus_RxStatus = USART_BUS_FREE;

	handle->Instance->CR1 &= ~(1 << USART_CR1_RXNEIE_Pos);
}




static void closeUSART_ISR_Tx(USART_HandleTypedef_t* handle)
{
	handle->TxDataSize = 0;
	handle->pTxdata = NULL;
	handle->Bus_TxStatus = USART_BUS_FREE;

	handle->Instance->CR1 &= ~(1 << USART_CR1_TXEIE_Pos);
}


static void USART_SendWithIT(USART_HandleTypedef_t* handle)
{
	if( (handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (handle->Init.Parity == USART_PARITY_NONE))
	{
		uint16_t* ptemp = (uint16_t*)handle->pTxdata;
		handle->Instance->TDR = (uint16_t)(*ptemp & (uint16_t)0x01ff);
		handle->pTxdata += sizeof(uint16_t);
		handle->TxDataSize -= 2;
	}
	else
	{
		handle->Instance->TDR = (uint8_t)(*(handle->pTxdata) & (uint8_t)0xff);
		handle->pTxdata++;
		handle->TxDataSize--;
	}


	if(handle->TxDataSize == 0)
		closeUSART_ISR_Tx(handle);
}


static void USART_ReceiveWithIT(USART_HandleTypedef_t* handle)
{
	uint16_t *p16BitBuffer;
	uint8_t* p8BitBuffer;

	if( ( handle->Init.WordLength == USART_WORDLENGTH_9Bits) && handle->Init.Parity == USART_PARITY_NONE)
	{
		p16BitBuffer = (uint16_t*)handle->pRxbuf;
		p8BitBuffer = NULL;
	}
	else
	{
		p8BitBuffer = (uint8_t*)handle->pRxbuf;
		p16BitBuffer = NULL;
	}

	if( p8BitBuffer == NULL)
	{
		*p16BitBuffer = (uint16_t)(handle->Instance->RDR & 0x01ff);
		handle->pRxbuf += sizeof(uint16_t);
		handle->RxDataSize -=2;
	}

	else
	{
		if( ( handle->Init.WordLength == USART_WORDLENGTH_9Bits) && handle->Init.Parity != USART_PARITY_NONE)
		{
			*p8BitBuffer = (uint8_t)(handle->Instance->RDR & 0x0ff);
			handle->pRxbuf++;
			handle->RxDataSize--;
		}

		else if( ( handle->Init.WordLength == USART_WORDLENGTH_8Bits) && handle->Init.Parity == USART_PARITY_NONE)
		{
			*p8BitBuffer = (uint8_t)(handle->Instance->RDR & 0x0ff);
			handle->pRxbuf++;
			handle->RxDataSize--;
		}

		else
		{
			*p8BitBuffer = (uint8_t)(handle->Instance->RDR & 0x0ef);
			handle->pRxbuf++;
			handle->RxDataSize--;
		}
	}
	closeUSART_ISR_Rx(handle);
}


/**
 * @brief		USART_Init , Configures the USART Peripheral
 *
 * @param		handle = User Config structure
 *
 * retval  void
 *
 */


void USART_Init(USART_HandleTypedef_t* handle)
{
	uint32_t periph_clock = 0;
	uint32_t mantissaPart = 0;
	uint32_t fractionPart = 0;
	uint32_t USART_DIV_Value = 0;
	uint32_t temp_brr = 0;
	/* CR1-> WordLength -  OverSampling - Parity - Mode CONF */

	uint32_t temp = handle->Instance->CR1;
	temp |= handle->Init.WordLength | handle->Init.OverSampling | handle->Init.Parity | handle->Init.Mode;
	handle->Instance->CR1 = temp;

	/* CR2-> STOP BITS CONF */
	temp = handle->Instance->CR2;
	temp &= ~(0x03 << USART_CR2_STOP_Pos);
	temp |= handle->Init.StopBits;
	handle->Instance->CR2 = temp;

	/* CR3 -> Hardware flow control */
	temp = handle->Instance->CR3;
	temp &= ~(0x1 << 9);
	temp |= handle->Init.HardWareFlowControl;
	handle->Instance->CR3 = temp;

	/* BRR -> Baudrate Config */

	if(handle->Instance == USART1)
		periph_clock = RCC_GetAPB2_Clock();
	else
		periph_clock = RCC_GetAPB1_Clock();

	if( handle->Init.OverSampling == USART_OVERSAMPLE_8)
	{
		USART_DIV_Value = __USART_DIV_VALUE_8(periph_clock,handle->Init.BaudRate);
		mantissaPart = (USART_DIV_Value / 100U);
		fractionPart = (USART_DIV_Value) - (mantissaPart * 100U);

		fractionPart = ( ( ( (fractionPart * 8U) + 50U) ) / 100U) & (0X7U);
	}
	else
	{
		USART_DIV_Value  = __USART_DIV_VALUE_16(periph_clock,handle->Init.BaudRate);
		mantissaPart = (USART_DIV_Value / 100U);
		fractionPart = (USART_DIV_Value) - (mantissaPart * 100U);

		fractionPart = ( ( ( (fractionPart * 8U) + 50U) ) / 100U) & (0xFU);

	}
	temp_brr |= ( mantissaPart << 4U );
	temp_brr |= (0xB << 0U );
	handle->Instance->BRR = temp_brr;
}




/**
 * @brief		USART_Periph_Cmd , Enable or Dısable USART Peripheral
 *
 * @param		handle = User Config structure
 *
 * @param 		state = ENABLE or DISABLE
 *
 * retval  void
 *
 */

void USART_Periph_Cmd(USART_HandleTypedef_t* handle, FunctionalState_t state)
{
	if(state == ENABLE )
		handle->Instance->CR1 |= (0x1U<< USART_EN_Pos);
	else
		handle->Instance->CR1 = ~(0x1U<< USART_EN_Pos);
}







// 9 bit frame no parity	9 bit frame yes parity(8bit 1parity frame)
// 8 bit frame no parity	8 bit frame yes parity(7bit data 1 parity)

/**
 * @brief		USART_TransmitData , Transmits data
 *
 * @param		handle = User Config structure
 *
 * @param 		pdata = Address of data to send
 *
 * @param 		sizeOfData = Length of your data in bytes
 *
 * retval  void
 *
 */

void USART_TransmitData(USART_HandleTypedef_t* handle, uint8_t *pdata, uint16_t dataSize)
{
	uint16_t * ptemp ;

	if( (handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (handle->Init.Parity == USART_PARITY_NONE) )
	{
		ptemp = (uint16_t*)pdata;
	}
	else
	{
		ptemp = NULL;
	}

	while(dataSize > 0 )
	{
		while( !USART_GetFlagStatus(handle, USART_ISR_TXE_Flag) );

		/* 9 Bits Data No paritiy is for else Condition,
		 * for others conditions you will be in if case
		 */

		if(ptemp == NULL)
		{
			handle->Instance->TDR = (uint8_t)(*pdata & (0xFFU));
			pdata++;
			dataSize --;
		}
		else
		{
			handle->Instance->TDR = (uint16_t)(*ptemp & (0x01FFU));
			ptemp++;
			dataSize -= 2;
		}

		while( !USART_GetFlagStatus(handle, USART_ISR_TC_Flag) );

	}

}







/**
 * @brief		USART_ReceiveData , Receive data from the slave
 *
 * @param		handle = User Config structure
 *
 * @param 		buf = Address of data to store
 *
 * @param 		sizeOfData = Length of your data in bytes
 *
 *
 * retval  none
 *
 */


void USART_ReceiveData(USART_HandleTypedef_t* handle, uint8_t *buf, uint16_t dataSize)
{
	uint16_t* pdata;

	if(handle->Init.WordLength == USART_WORDLENGTH_9Bits && handle->Init.Parity == USART_PARITY_NONE)
		pdata = (uint16_t*)buf;
	else
		pdata = NULL;

	while(dataSize > 0)
	{
		while(!USART_GetFlagStatus(handle, USART_ISR_RXNE_Flag));

		if(pdata == NULL)
		{
			if(handle->Init.WordLength == USART_WORDLENGTH_9Bits && handle->Init.Parity != USART_PARITY_NONE) //data = 8 parity = 1
			{
				*buf = (( uint8_t )(handle->Instance->RDR & 0x00ffU));
				buf++;
				dataSize--;
			}
			else if(handle->Init.WordLength == USART_WORDLENGTH_8Bits && handle->Init.Parity == USART_PARITY_NONE) //data = 8 none parity
			{
				*buf = (( uint8_t )(handle->Instance->RDR & 0x00ffU));
				buf++;
				dataSize--;
			}
			else // data 7 1 parity
			{
				*buf = (( uint8_t )(handle->Instance->RDR & 0x00efU));
				buf++;
				dataSize--;
			}

		}
		else
		{
			*pdata = (uint16_t)(handle->Instance->RDR & 0X01ffU);
			pdata++;
			dataSize -= sizeof(pdata);
		}

	}

}

void USART_TransmitData_IT(USART_HandleTypedef_t* handle, uint8_t *buf, uint16_t dataSize)
{
	USART_BusStatus_t state = handle->Bus_TxStatus;

	if(state != USART_BUS_BUSY_TX)
	{
		handle->Bus_TxStatus = USART_BUS_BUSY_TX;
		handle->TxDataSize = dataSize;
		handle->pTxdata = buf;
		handle->TxISRfunc = USART_SendWithIT;

		handle->Instance->CR1 |= (1 << USART_CR1_TXEIE_Pos);

	}
}



void USART_ReceiveData_IT(USART_HandleTypedef_t* handle, uint8_t *buf, uint16_t dataSize)
{
	USART_BusStatus_t state = handle->Bus_RxStatus;

	if(state != USART_BUS_BUSY_RX)
	{
		handle->Bus_RxStatus = USART_BUS_BUSY_RX;
		handle->RxDataSize = dataSize;
		handle->pRxbuf = buf;
		handle->RxISRfunc = USART_ReceiveWithIT;

		handle->Instance->CR1 |= (1 << USART_CR1_RXNEIE_Pos);

	}
}



/**
 * @brief		USART_GetFlagStatus , Return the flag of ISR register
 *
 * @param		handle = User Config structure
 *
 * @param 		FlagStatus = Flaf name of ISR register
 *
 *
 * retval  SPI_FlagStatus_t
 *
 */

USART_FlagStatus USART_GetFlagStatus(USART_HandleTypedef_t* handle, uint16_t FlagStatus)
{
	return (handle->Instance->ISR & FlagStatus) ? USART_FLAG_SET : USART_FLAG_RESET;
}




/**
 * @brief		USART_InterruptHandler , USART Interrupt control handle function
 *
 * @param		handle = User Config structure
 *
 * retval  none
 *
 */

void USART_InterruptHandler(USART_HandleTypedef_t* handle)
{
	uint8_t flag = 0;
	uint8_t interrupt = 0;

	flag = (uint8_t)((handle->Instance->ISR >> USART_ISR_TXE_Pos) & 0X01U );
	interrupt = (uint8_t)((handle->Instance->ISR >> USART_CR1_TXEIE_Pos) & 0X01U );

	if(flag && interrupt)
		handle->TxISRfunc(handle);

	flag = (uint8_t)((handle->Instance->ISR >> USART_ISR_RXNE_Pos) & 0X01U );
	interrupt = (uint8_t)((handle->Instance->ISR >> USART_CR1_RXNEIE_Pos) & 0X01U );

	if(flag && interrupt)
		handle->RxISRfunc(handle);
}



