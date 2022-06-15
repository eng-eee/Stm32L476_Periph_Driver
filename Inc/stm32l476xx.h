
#ifndef INC_STM32L476XX_H_
#define INC_STM32L476XX_H_

#include <stdint.h>
#include <stddef.h>

/*
 * 	Microprocessor Defines
 *
 */

#define NVIC_ISER0					( (uint32_t*)(0xE000E100) )


#define __IO						volatile

#define SET_BIT(REG, BIT)			( (REG) |=  (BIT) )
#define CLEAR_BIT(REG, BIT)			( (REG) &= ~(BIT) )
#define READ_BIT(REG, BIT)			( (REG) &   (BIT) )
#define UNUSED(x)					(void)x


typedef enum
{
	DISABLE = 0x1U,
	ENABLE = !DISABLE

}FunctionalState_t;


typedef enum
{
	EXTI0_IRQNumber = 6,
	EXTI1_IRQNumber = 7,
	EXTI2_IRQNumber = 8,
	EXTI3_IRQNumber = 9,
	EXTI4_IRQNumber = 10,
	EXTI9_5IRQNumber = 23,
	SPI1_IRQNumber = 35,
	SPI2_IRQNumber = 36,
	SPI3_IRQNumber = 51,
	EXTI15_10_IRQNumber = 40

}IRQNumber_Typedef_t;

/*
 *  Memory Base Address
 *
 */
//->Prep_processor ()
#define FLASH_BASE_ADDR				(0x08000000UL) 					/* Flash Base Address (up to 1MB) */
#define SRAM1_BASE_ADDR				(0x20000000UL) 					/* SRAM Base Address (up to 96Kbyte) */
#define SRAM2_BASE_ADDR				(0x10000000UL) 					/* SRAM2 Base Address (up to 32Kbyte) */



/*
 * Peripheral Base Addresses
 *
 */

#define PERIPH_BASE_ADDR			(0x40000000UL)					 /* Base address for all peripherals	*/

#define APB1_BASE_ADDR				PERIPH_BASE_ADDR 				 /* APB1 Bus Domain Base Address		*/
#define APB2_BASE_ADDR				(PERIPH_BASE_ADDR + 0x10000UL)	 /* APB2 Bus Domain Base Address		*/
#define AHB1_BASE_ADDR				(PERIPH_BASE_ADDR + 0x20000UL)	 /* AHB1 Bus Domain Base Address		*/
#define AHB2_BASE_ADDR				(PERIPH_BASE_ADDR + 0x8000000UL) /* AHB2 Bus Domain Base Address		*/


/*
 * 	APB1 Peripherals Base Address
 *
 */

#define TIM2_BASE_ADDR				(APB1_BASE_ADDR + 0x0000UL)		/* Timer 2 Base Address	*/
#define TIM3_BASE_ADDR				(APB1_BASE_ADDR + 0x0400UL)		/* Timer 3 Base Address	*/
#define TIM4_BASE_ADDR				(APB1_BASE_ADDR + 0x0800UL)		/* Timer 4 Base Address	*/
#define TIM5_BASE_ADDR				(APB1_BASE_ADDR + 0x0C00UL)		/* Timer 5 Base Address	*/
#define TIM6_BASE_ADDR				(APB1_BASE_ADDR + 0x0100UL)		/* Timer 6 Base Address	*/
#define TIM7_BASE_ADDR				(APB1_BASE_ADDR + 0x1400UL)		/* Timer 7 Base Address	*/

#define SPI2_BASE_ADDR				(APB1_BASE_ADDR + 0X03800UL)	/* SPI 2 Base Address	*/
#define SPI3_BASE_ADDR				(APB1_BASE_ADDR + 0X03C00UL)	/* SPI 3 Base Address	*/

#define USART2_BASE_ADDR			(APB1_BASE_ADDR + 0x04400UL)	/* USART 2 Base Address	*/
#define USART3_BASE_ADDR			(APB1_BASE_ADDR + 0x04800UL)	/* USART 3 Base Address	*/

#define UART4_BASE_ADDR  			(APB1_BASE_ADDR + 0x04C00UL)	/* UART 4 Base Address	*/
#define UART5_BASE_ADDR  			(APB1_BASE_ADDR + 0x05000UL)	/* UART 5 Base Address	*/

#define I2C1_BASE_ADDR				(APB1_BASE_ADDR + 0x05400UL)	/* I2C 1 Base Address	*/
#define I2C2_BASE_ADDR				(APB1_BASE_ADDR + 0x05800UL)	/* I2C 2 Base Address	*/
#define I2C3_BASE_ADDR				(APB1_BASE_ADDR + 0x05C00UL)	/* I2C 3 Base Address	*/

/*
 * 	APB2 Peripherals Base Address
 *
 */

#define SYSCFG_BASE_ADDR			(APB2_BASE_ADDR + 0x0000UL)		/* System Configuration Controller	*/
#define EXTI_BASE_ADDR				(APB2_BASE_ADDR + 0x00400UL)	/* External Interrupt Register		*/

#define TIM1_BASE_ADDR				(APB2_BASE_ADDR + 0x02C00UL)	/* Timer 1 Base Address				*/
#define TIM8_BASE_ADDR				(APB2_BASE_ADDR + 0x03400UL)	/* Timer 8 Base Address				*/
#define TIM15_BASE_ADDR				(APB2_BASE_ADDR + 0x04000UL)	/* Timer 15 Base Address			*/
#define TIM16_BASE_ADDR				(APB2_BASE_ADDR + 0x04400UL)	/* Timer 16 Base Address			*/
#define TIM17_BASE_ADDR				(APB2_BASE_ADDR + 0x04800UL)	/* Timer 17 Base Address			*/

#define SPI1_BASE_ADDR				(APB2_BASE_ADDR + 0X03000UL)	/* SPI 1 Base Address				*/

#define USART1_BASE_ADDR			(APB2_BASE_ADDR + 0x03800UL)	/* USART 2 Base Address				*/



/*
 * 	AHB1 High Bus
 *
 */


#define RCC_BASE_ADDR				(AHB1_BASE_ADDR + 0x01000UL)	/*	RCC Base Address	*/


/*
 * 	AHB2 HIGH BUS
 *
 */


#define GPIOA_BASE_ADDR				(AHB2_BASE_ADDR + 0x00000UL)	/* GPIOA Base Address	*/
#define GPIOB_BASE_ADDR				(AHB2_BASE_ADDR + 0x00400UL)	/* GPIOB Base Address	*/
#define GPIOC_BASE_ADDR				(AHB2_BASE_ADDR + 0x00800UL)	/* GPIOC Base Address	*/
#define GPIOD_BASE_ADDR				(AHB2_BASE_ADDR + 0x00C00UL)	/* GPIOD Base Address	*/
#define GPIOE_BASE_ADDR				(AHB2_BASE_ADDR + 0x01000UL)	/* GPIOE Base Address	*/



/*
 * 	Peripheral Structure Definitions
 *
 */

typedef struct{

	__IO uint32_t MODER;	/*!< GPIO Mode Register 				Address Offset == 0x0000 */
	__IO uint32_t OTYPE;	/*!< GPIO Output Type Register 			Address Offset == 0x0004 */
	__IO uint32_t OSPEEDR;	/*!< GPIO Output speed Register 		Address Offset == 0x0008 */
	__IO uint32_t PUPDR;	/*!< GPIO Pull-up/pull-down Register 	Address Offset == 0x000c */
	__IO uint32_t IDR;		/*!< GPIO input Data Register 			Address Offset == 0x0010 */
	__IO uint32_t ODR;		/*!< GPIO output Data Register 			Address Offset == 0x0014 */
	__IO uint32_t BSRR;		/*!< GPIO bit-set-reset Register 		Address Offset == 0x0018 */
	__IO uint32_t LCKR;		/*!< GPIO Lock Configuration Register 	Address Offset == 0x001c */
	__IO uint32_t AFR[2];	/*!< GPIO Alternate Function Register 	Address Offset == 0x0020 */

}GPIO_Typedef_t;

typedef struct{

	__IO uint32_t CR;				/*!< Clock control Register 									Address Offset == 0x0000 */
	__IO uint32_t ICSCR;			/*!< Internal clock sources calibration Register 				Address Offset == 0x0004 */
	__IO uint32_t CFGR;				/*!< Clock configuration Register 								Address Offset == 0x0008 */
	__IO uint32_t PLL_CFGR;			/*!< PLL configuration Register 								Address Offset == 0x000c */
	__IO uint32_t PLLSAI_CFGR[2];	/*!< PLLSAI 1-2 configuration Register 							Address Offset == 0x0010-14 */
	__IO uint32_t CIER;				/*!< Clock interrupt enable Register 							Address Offset == 0x0018 */
	__IO uint32_t CIFR;				/*!< Clock interrupt flag Register 								Address Offset == 0x001c */
	__IO uint32_t CICR;				/*!< Clock interrupt clear Register 							Address Offset == 0x0020 */
	__IO uint32_t RESERVED;			/*!< RESERVED Register				 							Address Offset == 0x0024 */
	__IO uint32_t AHB1RSTR;			/*!< AHB1 peripheral reset Register 							Address Offset == 0x0028 */
	__IO uint32_t AHB2RSTR;			/*!< AHB2 peripheral reset Register 							Address Offset == 0x002C */
	__IO uint32_t AHB3RSTR;			/*!< AHB3 peripheral reset Register 							Address Offset == 0x0030 */
	__IO uint32_t RESERVED2;		/*!< RESERVED2 Register 										Address Offset == 0x0034 */
	__IO uint32_t APB1RSTR1;		/*!< APB1 peripheral reset 1 Register 							Address Offset == 0x0038 */
	__IO uint32_t APB1RSTR2;		/*!< APB1 peripheral reset 2 Register 							Address Offset == 0x003C */
	__IO uint32_t APB2RSTR;			/*!< APB2 peripheral reset  Register 							Address Offset == 0x0040 */
	__IO uint32_t RESERVED3;		/*!< RESERVED3 Register 										Address Offset == 0x0044 */
	__IO uint32_t AHB1ENR;			/*!< AHB1 peripheral clock enable Register 						Address Offset == 0x0048 */
	__IO uint32_t AHB2ENR;			/*!< AHB2 peripheral clock enable Register 						Address Offset == 0x004C */
	__IO uint32_t AHB3ENR;			/*!< AHB3 peripheral clock enable Register 						Address Offset == 0x0050 */
	__IO uint32_t RESERVED4;		/*!< RESERVED4 Register 										Address Offset == 0x0054 */
	__IO uint32_t APB1ENR[2];		/*!< APB1 peripheral clock enable 1-2 Register 					Address Offset == 0x0058-5C */
	__IO uint32_t APB2ENR;			/*!< APB2 peripheral clock enable Register 						Address Offset == 0x0060 */
	__IO uint32_t RESERVED5;		/*!< RESERVED5 Register 										Address Offset == 0x0064 */
	__IO uint32_t AHB1SMENR;		/*!< AHB1 peripheral clocks enable Sleep-Stop modes Register 	Address Offset == 0x0068 */
	__IO uint32_t AHB2SMENR;		/*!< AHB2 peripheral clocks enable Sleep-Stop modes Register 	Address Offset == 0x006C */
	__IO uint32_t AHB3SMENR;		/*!< AHB3 peripheral clocks enable Sleep-Stop modes Register 	Address Offset == 0x0070 */
	__IO uint32_t RESERVED6;		/*!< RESERVED6 Register 										Address Offset == 0x0074 */
	__IO uint32_t APB1SMENR[2];		/*!< APB1 peripheral clocks enable Sleep-Stop modes Register 	Address Offset == 0x0078-7C */
	__IO uint32_t APB2SMENR;		/*!< APB2 peripheral clocks enable Sleep-Stop modes Register 	Address Offset == 0x0080 */
	__IO uint32_t RESERVED7;		/*!< RESERVED7 Register 										Address Offset == 0x0084 */
	__IO uint32_t CCIPR;			/*!< Peripherals independent clock configuration Register 		Address Offset == 0x0088 */
	__IO uint32_t RESERVED8;		/*!< RESERVED8 Register 										Address Offset == 0x008C */
	__IO uint32_t BDCR;				/*!< Backup domain control Register 							Address Offset == 0x0090 */
	__IO uint32_t CSR;				/*!< Control/status Register 									Address Offset == 0x0094 */

}RCC_Typedef_t;


typedef struct
{
	__IO uint32_t MEMRMP;			/*!< SYSCFG memory remap register 							Address Offset == 0x00 */
	__IO uint32_t CFGR1;			/*!< SYSCFG configuration register 1						Address Offset == 0x04 */
	__IO uint32_t EXTICR[4];		/*!< SYSCFG external interrupt configuration register (1-4)	Address Offset == 0x08 */
	__IO uint32_t SCSR;				/*!< SYSCFG SRAM2 control and status register 				Address Offset == 0x18 */
	__IO uint32_t CFGR2;			/*!< SYSCFG configuration register 2						Address Offset == 0x1C */
	__IO uint32_t SWPR;				/*!< SYSCFG SRAM2 write protection register 				Address Offset == 0x20 */
	__IO uint32_t SKR;				/*!< SYSCFG SRAM2 key register  							Address Offset == 0x24 */


}SYSCFG_Typedef_t;

typedef struct
{
	__IO uint32_t IMR1;				/*!< Interrupt mask register 1 				Address Offset == 0x00 */
	__IO uint32_t EMR1;				/*!< Event mask register 1 					Address Offset == 0x04 */
	__IO uint32_t RTSR1;			/*!< Rising trigger selection register 1 	Address Offset == 0x08 */
	__IO uint32_t FTSR1;			/*!< Falling trigger selection register 1  	Address Offset == 0x0C */
	__IO uint32_t SWIER1;			/*!< Software interrupt event register 1  	Address Offset == 0x10 */
	__IO uint32_t PR1;				/*!< Pending register 1 					Address Offset == 0x14 */
	__IO uint32_t RESERVED[2];		/*!< RESERVED					 			Address Offset == 0x00 */
	__IO uint32_t IMR2;				/*!< Interrupt mask register 2 				Address Offset == 0x20 */
	__IO uint32_t IEMR2;			/*!< Event mask register 2 					Address Offset == 0x24 */
	__IO uint32_t RTSR2;			/*!< Rising trigger selection register 2  	Address Offset == 0x28 */
	__IO uint32_t FTSR2;			/*!< Falling trigger selection register 2	Address Offset == 0x2C */
	__IO uint32_t SWIER2;			/*!< Software interrupt event register 2	Address Offset == 0x30 */
	__IO uint32_t PR2;				/*!< Pending register 2 					Address Offset == 0x34 */

}EXTI_Typedef_t;

typedef struct
{
	__IO uint32_t CR1;				/*!< SPI Control Register 1	 			Address Offset == 0x00 */
	__IO uint32_t CR2;				/*!< SPI Control Register 2 			Address Offset == 0x04 */
	__IO uint32_t SR;				/*!< SPI Status Register 				Address Offset == 0x08 */
	__IO uint32_t DR;				/*!< SPI Data Register 1 				Address Offset == 0x0C */
	__IO uint32_t CRCPR;			/*!< SPI CRC Polynomial Register 		Address Offset == 0x10 */
	__IO uint32_t RXCRCR;			/*!< SPI RX CRC Register 				Address Offset == 0x14 */
	__IO uint32_t TXCRCR;			/*!< SPI TX CRC Register 				Address Offset == 0x18 */

}SPI_Typedef_t;

#define	GPIOA						( (GPIO_Typedef_t *)(GPIOA_BASE_ADDR) )
#define	GPIOB						( (GPIO_Typedef_t *)(GPIOB_BASE_ADDR) )
#define	GPIOC						( (GPIO_Typedef_t *)(GPIOC_BASE_ADDR) )
#define	GPIOD						( (GPIO_Typedef_t *)(GPIOD_BASE_ADDR) )
#define	GPIOE						( (GPIO_Typedef_t *)(GPIOE_BASE_ADDR) )

#define RCC							( (RCC_Typedef_t* )(RCC_BASE_ADDR) )

#define SYSCFG						( (SYSCFG_Typedef_t* )(SYSCFG_BASE_ADDR) )

#define EXTI						( (EXTI_Typedef_t* )(EXTI_BASE_ADDR) )

#define SPI1						( (SPI_Typedef_t * )(SPI1_BASE_ADDR) )
#define SPI2						( (SPI_Typedef_t * )(SPI2_BASE_ADDR) )
#define SPI3						( (SPI_Typedef_t * )(SPI3_BASE_ADDR) )




/*
 * Bit Definitions
 *
 */

#define RCC_AHB2ENR_GPIOAEN_Pos		(0U)								// RCC AHB2ENR	register GPIOAEN Bit Position
#define RCC_AHB2ENR_GPIOAEN_Msk		(0x1 << RCC_AHB2ENR_GPIOAEN_Pos)	// RCC AHB2ENR	register GPIOAEN Bit Mask
#define RCC_AHB2ENR_GPIOAEN			RCC_AHB2ENR_GPIOAEN_Msk				// RCC AHB2ENR	register GPIOAEN Macro

#define RCC_AHB2ENR_GPIOBEN_Pos		(1U)								// RCC AHB2ENR	register GPIOBEN Bit Position
#define RCC_AHB2ENR_GPIOBEN_Msk		(0x1 << RCC_AHB2ENR_GPIOBEN_Pos)	// RCC AHB2ENR	register GPIOBEN Bit Mask
#define RCC_AHB2ENR_GPIOBEN			RCC_AHB2ENR_GPIOBEN_Msk				// RCC AHB2ENR	register GPIOBEN Macro

#define RCC_AHB2ENR_GPIOCEN_Pos		(2U)								// RCC AHB2ENR	register GPIOCEN Bit Position
#define RCC_AHB2ENR_GPIOCEN_Msk		(0x1 << RCC_AHB2ENR_GPIOCEN_Pos)	// RCC AHB2ENR	register GPIOCEN Bit Mask
#define RCC_AHB2ENR_GPIOCEN			RCC_AHB2ENR_GPIOCEN_Msk				// RCC AHB2ENR	register GPIOCEN Macro

#define RCC_AHB2ENR_GPIODEN_Pos		(3U)								// RCC AHB2ENR	register GPIODEN Bit Position
#define RCC_AHB2ENR_GPIODEN_Msk		(0x1 << RCC_AHB2ENR_GPIODEN_Pos)	// RCC AHB2ENR	register GPIODEN Bit Mask
#define RCC_AHB2ENR_GPIODEN			RCC_AHB2ENR_GPIODEN_Msk				// RCC AHB2ENR	register GPIODEN Macro

#define RCC_APB2ENR_SYSCFGEN_Pos	(0U)								// RCC APB2ENR	register SYSCFGEN Bit Position
#define RCC_APB2ENR_SYSCFGEN_Msk	(0x1 << RCC_APB2ENR_SYSCFGEN_Pos)	// RCC APB2ENR	register SYSCFGEN Bit Mask
#define RCC_APB2ENR_SYSCFGEN		RCC_APB2ENR_SYSCFGEN_Msk			// RCC APB2ENR	register SYSCFGEN Macro

#define RCC_APB2ENR_SPI1EN_Pos		(12U)								// RCC APB2ENR	register SPI1EN Bit Position
#define RCC_APB2ENR_SPI1EN_Mask		(0x1 << RCC_APB2ENR_SPI1EN_Pos)		// RCC APB2ENR	register SPI1EN Bit Mask
#define RCC_APB2ENR_SPI1EN			RCC_APB2ENR_SPI1EN_Mask				// RCC APB2ENR	register SPI1EN Macro

#define RCC_APB1ENR1_SPI2EN_Pos		(14U)								// RCC APB1ENR1	register SPI2EN Bit Position
#define RCC_APB1ENR1_SPI2EN_Mask	(0x1 << RCC_APB1ENR1_SPI2EN_Pos)	// RCC APB1ENR1	register SPI2EN Bit Mask
#define RCC_APB1ENR1_SPI2EN			RCC_APB1ENR1_SPI2EN_Mask			// RCC APB1ENR1	register SPI2EN Macro

#define RCC_APB1ENR1_SPI3EN_Pos		(15U)								// RCC APB1ENR1	register SPI3EN Bit Position
#define RCC_APB1ENR1_SPI3EN_Mask	(0x1 << RCC_APB1ENR1_SPI3EN_Pos)	// RCC APB1ENR1	register SPI3EN Bit Mask
#define RCC_APB1ENR1_SPI3EN			RCC_APB1ENR1_SPI3EN_Mask			// RCC APB1ENR1	register SPI3EN Macro


#define SPI_SR_Busy_Pos				(7U)			/* Bit 7 Busy flag */
#define SPI_Enable_Pos				(6U)			/* Bit 6 SPE: SPI enable */
#define SPI_SR_TxE_Pos				(1U)			/* Bit 1 TXE: Transmit buffer empty 1: Tx buffer empty */
#define SPI_SR_RxNE_Pos				(0U)			/* Bit 0 RXNE: Receive buffer not empty 1: Rx buffer not empty */

#define SPI_CR2_TXEIE				(7U)			/* SPI TX INTERRUPT ENABLE POS */
#define SPI_CR2_RXNEIE				(6U)			/* SPI RX INTERRUPT ENABLE POS */
#define SPI_CR1_DFF					(11U)			/* SPI Data Frame Format POS */

/*
 * SPI Flag Definitions
 *
 */


#define SPI_TxE_FLAG				(0x1U << SPI_SR_TxE_Pos)
#define SPI_RxNE_FLAG				(0x1U << SPI_SR_RxNE_Pos)

#define SPI_Bussy_FLAG				(0x1U << SPI_SR_Busy_Pos)


#include "GPIO.h"
#include "EXTI.h"
#include "RCC.h"
#include "SPI.h"


#endif /* INC_STM32L476XX_H_ */
