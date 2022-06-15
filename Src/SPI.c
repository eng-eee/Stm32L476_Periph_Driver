#include "SPI.h"


/**
 * @brief		SPI_CloseISR_Tx , Disables the interrupt for Transmission
 *
 * @param		handle = User Config structure
 *
 * retval  void
 *
 */


static void SPI_CloseISR_Tx(SPI_HandleTypedef_t* handle)
{
	handle->Instance->CR2 &= ~(0x1U << SPI_CR2_TXEIE);
	handle->TxDataSize = 0;
	handle->pTxDataAddr = NULL;
	handle->bus_state_tx = SPI_BUS_FREE;

}





/**
 * @brief		SPI_CloseISR_Rx , Disables the interrupt for Transmission
 *
 * @param		handle = User Config structure
 *
 * retval  void
 *
 */


static void SPI_CloseISR_Rx(SPI_HandleTypedef_t* handle)
{
	handle->Instance->CR2 &= ~(0x1U << SPI_CR2_RXNEIE);
	handle->RxDataSize = 0;
	handle->pRxDataAddr = NULL;
	handle->bus_state_rx = SPI_BUS_FREE;

}





/**
 * @brief		SPI_ReceiverHelper_16Bits , Stores the DR register into the user buffer
 *
 * @param		handle = User Config structure
 *
 * retval  void
 *
 */




static void SPI_ReceiverHelper_16Bits(SPI_HandleTypedef_t* handle)
{
	*((uint16_t*)handle->pRxDataAddr) = handle->Instance->DR;
	handle->RxDataSize -= sizeof(uint16_t);
	handle->pRxDataAddr -= sizeof(uint16_t);

	if(handle->RxDataSize == 0)
		SPI_CloseISR_Rx(handle);

}






/**
 * @brief		SPI_ReceiverHelper_8Bits , Stores the DR register into the user buffer
 *
 * @param		handle = User Config structure
 *
 * retval  void
 *
 */

static void SPI_ReceiverHelper_8Bits(SPI_HandleTypedef_t* handle)
{
	*((uint8_t*)handle->pRxDataAddr) = *( (__IO uint8_t*)(&handle->Instance->DR) );
	handle->RxDataSize -= sizeof(uint8_t);
	handle->pRxDataAddr -= sizeof(uint8_t);

	if(handle->RxDataSize == 0)
		SPI_CloseISR_Rx(handle);
}






/**
 * @brief		SPI_TransmitHelper_16Bits , Stores the user data into the DR register for 16bits
 *
 * @param		handle = User Config structure
 *
 * retval  void
 *
 */


static void SPI_TransmitHelper_16Bits(SPI_HandleTypedef_t* handle)
{
	handle->Instance->DR = *(( uint16_t*)(handle->pTxDataAddr));
	handle->pTxDataAddr += sizeof(uint16_t);
	handle->TxDataSize -= 2;

	if(handle->TxDataSize == 0)
		SPI_CloseISR_Tx(handle);
}






/**
 * @brief		SPI_TransmitHelper_8Bits , Stores the user data into the DR register for 8bits
 *
 * @param		handle = User Config structure
 *
 * retval  void
 *
 */


static void SPI_TransmitHelper_8Bits(SPI_HandleTypedef_t* handle)
{
	handle->Instance->DR = *((uint8_t*)(handle->pTxDataAddr));
	handle->pTxDataAddr += sizeof(uint8_t);
	handle->TxDataSize--;

	if(handle->TxDataSize == 0)
		SPI_CloseISR_Tx(handle);
}






/**
 * @brief		SPI_Init , Configures the SPI Peripheral
 *
 * @param		handle = User Config structure
 *
 * retval  void
 *
 */


void SPI_Init(SPI_HandleTypedef_t* handle)
{
	uint32_t temp;

	temp = handle->Instance->CR1;

	temp |= (handle->Init.BaudRate) | (handle->Init.CPHA) | (handle->Init.CPOL) | (handle->Init.DFF_Format) | \
			(handle->Init.Mode) | (handle->Init.FrameFormat) | (handle->Init.Bus_Config) | (handle->Init.SSM_Cmd);

	handle->Instance->CR1 = temp;
}





/**
 * @brief		SPI_PeriphCmd , Enable or Dısable SPI Peripheral
 *
 * @param		handle = User Config structure
 *
 * @param 		state = ENABLE or DISABLE
 *
 * retval  void
 *
 */


void SPI_PeriphCmd(SPI_HandleTypedef_t* handle, FunctionalState_t state)
{
	if( state == ENABLE)
		handle->Instance->CR1 |= (0x1 << SPI_Enable_Pos);
	else
		handle->Instance->CR1 &= ~(0x1 << SPI_Enable_Pos);
}





/**
 * @brief		SPI_TransmitData , Transmits data to the slave
 *
 * @param		handle = User Config structure
 *
 * @param 		buf = Address of data to send
 *
 * @param 		sizeOfData = Length of your data in bytes
 *
 * retval  void
 *
 */

void SPI_TransmitData(SPI_HandleTypedef_t* handle, uint8_t* buf, uint16_t sizeOfData)
{
	if(handle->Init.DFF_Format == SPI_DFF_16BITS)
	{
		while(sizeOfData > 0)
		{
			if(SPI_GetFlagStatus(handle, SPI_TxE_FLAG))
			{

				handle->Instance->DR = *( ( uint16_t* )buf );
				buf += sizeof(uint16_t);
				sizeOfData -= 2;;
			}
		}
	}
	else
	{
		while(sizeOfData > 0)
		{
			if(SPI_GetFlagStatus(handle, SPI_TxE_FLAG))
			{
				handle->Instance->DR = *buf;
				buf += sizeof(uint8_t);
				sizeOfData--;
			}
		}
	}

	while(SPI_GetFlagStatus(handle, SPI_Bussy_FLAG)); // WAIT FOR BUSSY FLAG

}





/**
 * @brief		SPI_ReceiveData , Receive data from the slave
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


void SPI_ReceiveData(SPI_HandleTypedef_t* handle, uint8_t* buf, uint16_t sizeOfData)
{
	if(handle->Init.DFF_Format == SPI_DFF_16BITS)
	{
		while(sizeOfData > 0)
		{
			if(SPI_GetFlagStatus(handle, SPI_RxNE_FLAG))
			{
				*( (uint16_t*)buf) = (uint16_t)handle->Instance->DR;
				buf += sizeof(uint16_t);
				sizeOfData -= 2;
			}
		}
	}
	else
	{
		while(sizeOfData > 0)
		{
			if(SPI_GetFlagStatus(handle, SPI_RxNE_FLAG))
			{

				*buf = *((__IO uint8_t*)(&handle->Instance->DR));
				buf += sizeof(uint8_t);
				sizeOfData -= 1;
			}
		}
	}
}






/**
 * @brief		SPI_TransmitData_IT , Transmits data to the slave with Interrupt
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

void SPI_TransmitData_IT(SPI_HandleTypedef_t* handle, uint8_t* buf, uint16_t sizeOfData) /* Interrup init */
{
	SPI_BusStatus_t bus_state = handle->bus_state_tx; // Konumu kontrol et benden önce transmisson yapmıyorsa konf

	if(bus_state != SPI_BUS_BUSY_TX)
	{
		handle->pTxDataAddr = (uint8_t*)buf; // globala çek
		handle->TxDataSize = (uint16_t)sizeOfData; // globale çek
		handle->bus_state_tx = SPI_BUS_BUSY_TX; // hattın state i bussy yap

		if(handle->Instance->CR1 & ( 0x1U << SPI_CR1_DFF ) )
		{
			handle->TxISRFunction = SPI_TransmitHelper_16Bits; // function adres ver
		}
		else
		{
			handle->TxISRFunction = SPI_TransmitHelper_8Bits;	// function adres ver
		}

		handle->Instance->CR2 |= (0x1U << SPI_CR2_TXEIE);
	}
}






/**
 * @brief		SPI_ReceiveData , Receive data from the slave with Interrupt method
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


void SPI_ReceiveData_IT(SPI_HandleTypedef_t* handle, uint8_t* buf, uint16_t sizeOfData)
{

	SPI_BusStatus_t bus_state = handle->bus_state_rx;

	if(bus_state != SPI_BUS_BUSY_RX)
	{
		handle->pRxDataAddr = (uint8_t*)buf;
		handle->RxDataSize = (uint16_t)sizeOfData;
		handle->bus_state_rx = SPI_BUS_BUSY_RX;

		if(handle->Instance->CR1 & ( 0x1U << SPI_CR1_DFF ) )
			handle->RxISRFunction = SPI_ReceiverHelper_16Bits;
		else
			handle->RxISRFunction = SPI_ReceiverHelper_8Bits;

		handle->Instance->CR2 |= (0x1U << SPI_CR2_RXNEIE);

	}
}







/**
 * @brief		SPI_InterruptHandler , SPI Interrupt control handle function
 *
 * @param		handle = User Config structure
 *
 * retval  none
 *
 */
void SPI_InterruptHandler(SPI_HandleTypedef_t* handle)
{
	uint8_t interruptSource = 0;
	uint8_t interruptFlag = 0;

	/* Interrupt geldi mi kontrolü */

	interruptSource = handle->Instance->CR2 & (0x1U << SPI_CR2_TXEIE);
	interruptFlag = handle->Instance->SR & (0x1U << SPI_SR_TxE_Pos);

	if((interruptFlag != 0) && (interruptSource != 0))
	{
		handle->TxISRFunction(handle);
	}

	interruptSource = handle->Instance->CR2 & (0x1U << SPI_CR2_RXNEIE);
	interruptFlag = handle->Instance->SR & (0x1U << SPI_SR_RxNE_Pos);

	if((interruptFlag != 0) && (interruptSource != 0))
	{
		handle->RxISRFunction(handle);
	}

}







/**
 * @brief		SPI_GetFlagStatus , Return the flag of SR register
 *
 * @param		handle = User Config structure
 *
 * @param 		SPI_FLAG = Flaf name of SR register
 *
 *
 * retval  SPI_FlagStatus_t
 *
 */

SPI_FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypedef_t* handle, uint16_t SPI_Flag)
{
	return (handle->Instance->SR & SPI_Flag) ? SPI_FLAG_SET : SPI_FLAG_RESET;
}


