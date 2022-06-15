#include "SPI.h"

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

