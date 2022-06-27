

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "stm32l476xx.h"


uint32_t RCC_GetSystemClock(void);
uint32_t RCC_GetHClock(void);
uint32_t RCC_GetAPB1_Clock(void);
uint32_t RCC_GetAPB2_Clock(void);



/*
 * RCC AHB2 Peripherals Clock Control Macro Definitons
 *
 */

#define RCC_GPIOA_CLK_ENABLE()				do{	uint32_t tempValue = 0;		\
												SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);		\
												tempValue = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);		\
												UNUSED(tempValue);		\
											  }while(0)


#define RCC_GPIOB_CLK_ENABLE()				do{	uint32_t tempValue = 0;			\
												SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN); \
												tempValue = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN); \
												UNUSED(tempValue); \
											  }while(0)


#define RCC_GPIOC_CLK_ENABLE()				do{	uint32_t tempValue = 0;		\
												SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);		\
												tempValue = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);		\
												UNUSED(tempValue);		\
											  }while(0)


#define RCC_GPIOD_CLK_ENABLE()				do{	uint32_t tempValue = 0;			\
												SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN); \
												tempValue = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN); \
												UNUSED(tempValue); \
											  }while(0)





#define RCC_GPIOA_CLK_DISABLE()				CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN)
#define RCC_GPIOB_CLK_DISABLE()				CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN)
#define RCC_GPIOC_CLK_DISABLE()				CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN)
#define RCC_GPIOD_CLK_DISABLE()				CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN)



/*
 * RCC APB2 Peripherals Clock Control Macro Definitons
 *
 */

#define RCC_SYSCFG_CLK_ENABLE()				do{	uint32_t tempValue = 0;			\
												SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN); \
												tempValue = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN); \
												UNUSED(tempValue); \
											  }while(0)


#define RCC_SPI1_CLK_ENABLE()				do{	uint32_t tempValue;		\
												SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);		\
												tempValue = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);		\
												UNUSED(tempValue);	\
											}while(0)



#define RCC_SYSCFG_CLK_DISABLE()			CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN)

#define RCC_SPI1_CLK_DISABLE()				CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN)



#define RCC_USART1_CLK_ENABLE()				do{	uint32_t temp;			\
												SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);		\
												temp = READ_BIT(RCC->APB2ENR,RCC_APB2ENR_USART1EN);	\
												UNUSED(temp);			\
											}while(0)

#define RCC_USART1_CLK_DISABLE()			CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN)

/*
 * RCC APB1 Peripherals Clock Control Macro Definitons
 *
 */


#define RCC_SPI2_CLK_ENABLE()				do{	uint32_t tempValue;		\
												SET_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_SPI2EN);		\
												tempValue = READ_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_SPI2EN);		\
												UNUSED(tempValue);	\
											}while(0)


#define RCC_SPI3_CLK_ENABLE()				do{	uint32_t tempValue;		\
												SET_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_SPI3EN);		\
												tempValue = READ_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_SPI3EN);		\
												UNUSED(tempValue);	\
											}while(0)

#define RCC_SPI2_CLK_DISABLE()				CLEAR_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_SPI2EN)
#define RCC_SPI3_CLK_DISABLE()				CLEAR_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_SPI3EN)




#define RCC_USART2_CLK_ENABLE()				do{	uint32_t temp;			\
												SET_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_USART2EN);		\
												temp = READ_BIT(RCC->APB1ENR[0],RCC_APB1ENR1_USART2EN);	\
												UNUSED(temp);			\
											}while(0)


#define RCC_USART3_CLK_ENABLE()				do{	uint32_t temp;			\
												SET_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_USART3EN);		\
												temp = READ_BIT(RCC->APB1ENR[0],RCC_APB1ENR1_USART3EN);	\
												UNUSED(temp);			\
											}while(0)


#define RCC_UART4_CLK_ENABLE()				do{	uint32_t temp;			\
												SET_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_UART4EN);		\
												temp = READ_BIT(RCC->APB1ENR[0],RCC_APB1ENR1_UART4EN);	\
												UNUSED(temp);			\
											}while(0)


#define RCC_UART5_CLK_ENABLE()				do{	uint32_t temp;			\
												SET_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_UART5EN);		\
												temp = READ_BIT(RCC->APB1ENR[0],RCC_APB1ENR1_UART5EN);	\
												UNUSED(temp);			\
											}while(0)


#define RCC_USART2_CLK_DISABLE()			CLEAR_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_USART2EN)
#define RCC_USART3_CLK_DISABLE()			CLEAR_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_USART3EN)
#define RCC_UART4_CLK_DISABLE()				CLEAR_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_UART4EN)
#define RCC_UART5_CLK_DISABLE()				CLEAR_BIT(RCC->APB1ENR[0], RCC_APB1ENR1_UART5EN)


#endif /* INC_RCC_H_ */
