
#ifndef INC_USART_H_
#define INC_USART_H_

#include "stm32l476xx.h"


/*
 * @def_groups MODE_Types
 *
 *
 */

#define USART_MODE_Tx					( (uint32_t)(0x00000008) )
#define USART_MODE_Rx					( (uint32_t)(0x00000004) )
#define USART_MODE_Tx_Rx				( (uint32_t)(0x0000000C) )


/*
 * @def_groups WordLenth_Types
 *
 *
 */


/*This bit can only be written when the USART is disabled (UE=0)*/
#define USART_WORDLENGTH_7Bits				( (uint32_t)(0x10000000) )
#define USART_WORDLENGTH_8Bits				( (uint32_t)(0x00000000) )
#define USART_WORDLENGTH_9Bits				( (uint32_t)(0x00001000) )


/*
 *	@deg_group Parity_Mode
 *
 *
 */

#define USART_PARITY_NONE					( (uint32_t)(0x00000000) )
#define USART_PARITY_EVEN					( (uint32_t)(0x00000400) )
#define USART_PARITY_ODD					( (uint32_t)(0x00000600) )


/*
 *	@deg_group StopBits_Mode
 *
 *
 */

#define USART_STOPBITS_ONE					( (uint32_t)(0x00000000) )
#define USART_STOPBITS_HALF					( (uint32_t)(0x00001000) )
#define USART_STOPBITS_HALF_ONE				( (uint32_t)(0x00003000) )
#define USART_STOPBITS_TWO					( (uint32_t)(0x00002000) )


/*
 * @deg_group OverSampling_Mode
 *
 *
 */


#define USART_OVERSAMPLE_16					( (uint32_t)(0x00000000) )
#define USART_OVERSAMPLE_8					( (uint32_t)(0x00008000) )

/*
 * @deg_group HardWareFlowControl_Mode
 *
 *
 */

#define USART_HW_NONE						( (uint32_t)(0x00000000) )
#define USART_HW_CTS						( (uint32_t)(0x00000200) )
#define USART_HW_RTS						( (uint32_t)(0x00000100) )
#define USART_HW_CTS_RTS					( (uint32_t)(0x00000300) )


#define __USART_DIV_VALUE_8(__PCLOCK__,__BAUDRATE__)	( 25U * (uint32_t)(__PCLOCK__) ) / ( 2U * (uint32_t)(__BAUDRATE__) )
#define __USART_DIV_VALUE_16(__PCLOCK__,__BAUDRATE__)	( 25U * (uint32_t)(__PCLOCK__) ) / ( 4U * (uint32_t)(__BAUDRATE__) )

typedef enum
{
	USART_FLAG_RESET = 0x0U,
	USART_FLAG_SET = !USART_FLAG_RESET

}USART_FlagStatus;

typedef struct
{
	uint32_t Mode;						/*!< Transmissions and Reception Modes @deg_group Mode_Types  */
	uint32_t BaudRate;					/*!< User Value for Baudrate; 		*/
	uint32_t WordLength;				/*!< 8 Bits & 9 Bits Modes @deg_group WordLenth_Types  */
	uint32_t Parity;					/*!< Even and  Odd @deg_group Parity_Mode  */
	uint32_t StopBits;					/*!< 8 Stop Bits Modes @deg_group StopBits_Mode  */
	uint32_t OverSampling;				/*!< OverSampling Mode @deg_group OverSampling_Mode  */
	uint32_t HardWareFlowControl;		/*!< HardWareFlowControl Mode @deg_group HardWareFlowControl_Mode  */

}USART_InitTypedef_t;


typedef enum
{
	USART_BUS_FREE = 0x0U,
	USART_BUS_BUSY_TX = 0x1U,
	USART_BUS_BUSY_RX = 0x2U,

}USART_BusStatus_t;

typedef struct __USART_HandleTypedef_t
{
	USART_Typedef_t *Instance;
	USART_InitTypedef_t Init;
	USART_BusStatus_t Bus_TxStatus;
	uint8_t* pTxdata;
	uint16_t TxDataSize;
	void(*TxISRfunc)(struct __USART_HandleTypedef_t* handle);
	USART_BusStatus_t Bus_RxStatus;
	uint8_t* pRxbuf;
	uint16_t RxDataSize;
	void(*RxISRfunc)(struct __USART_HandleTypedef_t* handle);
}USART_HandleTypedef_t;


void USART_Init(USART_HandleTypedef_t* handle);
void USART_Periph_Cmd(USART_HandleTypedef_t* handle, FunctionalState_t state);
void USART_TransmitData(USART_HandleTypedef_t* handle, uint8_t *pdata, uint16_t dataSize);
void USART_ReceiveData(USART_HandleTypedef_t* handle, uint8_t *buf, uint16_t dataSize);
void USART_TransmitData_IT(USART_HandleTypedef_t* handle, uint8_t* pdata, uint16_t dataSize);
void USART_ReceiveData_IT(USART_HandleTypedef_t* handle, uint8_t *buf, uint16_t dataSize);

void USART_InterruptHandler(USART_HandleTypedef_t* handle);
USART_FlagStatus USART_GetFlagStatus(USART_HandleTypedef_t* handle, uint16_t FlagStatus);







#endif /* INC_USART_H_ */
