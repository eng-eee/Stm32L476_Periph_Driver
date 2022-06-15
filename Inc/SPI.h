
#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32l476xx.h"

/*
 * @def_group SPI_BaudRates
 *
 *
 */

#define SPI_BAUDRATE_DIV_2				( (uint32_t)(0x00000000) )
#define SPI_BAUDRATE_DIV_4				( (uint32_t)(0x00000008) )
#define SPI_BAUDRATE_DIV_8				( (uint32_t)(0x00000010) )
#define SPI_BAUDRATE_DIV_16				( (uint32_t)(0x00000018) )
#define SPI_BAUDRATE_DIV_32				( (uint32_t)(0x00000020) )
#define SPI_BAUDRATE_DIV_64				( (uint32_t)(0x00000028) )
#define SPI_BAUDRATE_DIV_128			( (uint32_t)(0x00000030) )
#define SPI_BAUDRATE_DIV_256			( (uint32_t)(0x00000038) )

/*
 * @def_group SPI_CPHA
 *
 *
 */

#define SPI_CPHA_FIRST_EDGE				( (uint32_t)(0x00000000) )
#define SPI_CPHA_SECOND_EDGE			( (uint32_t)(0x00000001) )

/*
 * @def_group SPI_CPOL
 *
 *
 */

#define SPI_CPOL_LOW					( (uint32_t)(0x00000000) )
#define SPI_CPOL_HIGH					( (uint32_t)(0x00000002) )


/*
 * @def_group SPI_DFF
 *
 *
 */


#define SPI_DFF_8BITS					( (uint32_t)(0x00000000) )
#define SPI_DFF_16BITS					( (uint32_t)(0x00000800) )


/*
 * @def_group SPI_MODE
 *
 *
 */

#define SPI_MODE_MASTER					( (uint32_t)(0x00000004) )
#define SPI_MODE_SLAVE					( (uint32_t)(0x00000000) )


/*
 *	@def_group SPI_Frame_Format
 *
 *
 */

#define SPI_FRAME_FORMAT_MSB			( (uint32_t)(0x00000000) )
#define SPI_FRAME_FORMAT_LSB			( (uint32_t)(0x00000080) )


/*
 *	@def_group SPI_Management
 *
 *
 */


#define SPI_SSM_DISABLE				( (uint32_t)(0x00000000) )
#define SPI_SSM_ENABLE				( (uint32_t)(0x00000300) )




/*
 *	@def_group SPI_Duplex Config *
 *
 */


#define SPI_Bus_FullDuplex			( (uint32_t)(0x00000000) )
#define SPI_Bus_FullDuplex_R		( (uint32_t)(0x00000400) )

#define SPI_Bus_HalfDuplex_T		( (uint32_t)(0x0000C000) )
#define SPI_Bus_HalfDuplex_R		( (uint32_t)(0x00008000) )



typedef enum
{
	SPI_FLAG_RESET = 0x0U,
	SPI_FLAG_SET = !SPI_FLAG_RESET

}SPI_FlagStatus_t;

typedef struct
{
	uint32_t Mode;			/*!> Mode Values for SPI @def_group SPI_MODE */
	uint32_t CPHA;			/*!> CPHA Values for SPI @def_group SPI_CPHA */
	uint32_t CPOL;			/*!> CPOL Values for SPI @def_group SPI_CPOL */
	uint32_t BaudRate;		/*!> BaudRate Values for SPI @def_group SPI_BaudRates */
	uint32_t SSM_Cmd;		/*!> Software slave management Values for SPI @def_group SPI_Management */
	uint32_t DFF_Format;	/*!> DFF Format Values for SPI @def_group SPI_DFF */
	uint32_t Bus_Config;	/*!> Bus Config Values for SPI @def_group SPI_Duplex Config */
	uint32_t FrameFormat;	/*!> FRAME Format Values for SPI @def_group SPI_Frame_Format */

}SPI_InitTypedef_t;



typedef struct
{
	SPI_Typedef_t* Instance;
	SPI_InitTypedef_t Init;

}SPI_HandleTypedef_t;

void SPI_Init(SPI_HandleTypedef_t *handle);
void SPI_PeriphCmd(SPI_HandleTypedef_t* handle, FunctionalState_t state);
void SPI_TransmitData(SPI_HandleTypedef_t* handle, uint8_t* buf, uint16_t sizeOfData);
SPI_FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypedef_t* handle, uint16_t SPI_Flag);

#endif /* INC_SPI_H_ */
