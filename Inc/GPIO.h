
#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stm32l476xx.h"

/*
 * @def_group GPIO_Pins
 *
 */

#define GPIO_PIN_0					(uint16_t)(0x0001)  /*<	GPIO Pin 0  Selected	*/
#define GPIO_PIN_1					(uint16_t)(0x0002)	/*<	GPIO Pin 1  Selected	*/
#define GPIO_PIN_2					(uint16_t)(0x0004) 	/*<	GPIO Pin 2  Selected	*/
#define GPIO_PIN_3					(uint16_t)(0x0008) 	/*<	GPIO Pin 3  Selected	*/
#define GPIO_PIN_4					(uint16_t)(0x0010) 	/*<	GPIO Pin 4  Selected	*/
#define GPIO_PIN_5					(uint16_t)(0x0020) 	/*<	GPIO Pin 5  Selected	*/
#define GPIO_PIN_6					(uint16_t)(0x0040) 	/*<	GPIO Pin 6  Selected	*/
#define GPIO_PIN_7					(uint16_t)(0x0080) 	/*<	GPIO Pin 7  Selected	*/
#define GPIO_PIN_8					(uint16_t)(0x0100) 	/*<	GPIO Pin 8  Selected	*/
#define GPIO_PIN_9					(uint16_t)(0x0200) 	/*<	GPIO Pin 9  Selected	*/
#define GPIO_PIN_10					(uint16_t)(0x0400)  /*<	GPIO Pin 10 Selected	*/
#define GPIO_PIN_11					(uint16_t)(0x0800) 	/*<	GPIO Pin 11 Selected	*/
#define GPIO_PIN_12					(uint16_t)(0x1000) 	/*<	GPIO Pin 12 Selected	*/
#define GPIO_PIN_13 				(uint16_t)(0x2000) 	/*<	GPIO Pin 13 Selected	*/
#define GPIO_PIN_14					(uint16_t)(0x4000) 	/*<	GPIO Pin 14 Selected	*/
#define GPIO_PIN_15					(uint16_t)(0x8000) 	/*<	GPIO Pin 15 Selected	*/
#define GPIO_PIN_ALL				(uint16_t)(0xFFFF) 	/*<	GPIO Pin 16 Selected	*/



/*
 * @def_group GPIO_Pins_Modes
 *
 *
 */

#define GPIO_MODE_INPUT				(0x0U)
#define GPIO_MODE_OUTPUT			(0x1U)
#define GPIO_MODE_AF				(0x2U)
#define GPIO_MODE_ANALOG			(0x3U)


/*
 * @def_group GPIO_Pins_OTYPE_Modes
 *
 *
 */

#define GPIO_OTYPE_PP				(0x0U)		/*!< 0: Output push-pull (reset state) */
#define GPIO_OTYPE_OD				(0x1U)		/*!< 1: Output open-drain 			   */


/*
 * @def_group GPIO_Pins_PUPDR_Modes
 *
 *
 */

#define GPIO_PUPD_NOPULL			(0x0U)		/*!< 00: No pull-up, pull-down */
#define GPIO_PUPD_PULL_UP			(0x1U)		/*!< 01: Pull-up			   */
#define GPIO_PUPD_PULL_DOWN			(0x2U)		/*!< 10: Pull-down			   */

/*
 * @def_group GPIO_Pins_SPEED_Modes
 *
 *
 */


#define GPIO_SPEED_LOW				(0x0U)		/*!< 00: Low speed 		*/
#define GPIO_SPEED_MEDIUM			(0x1U)		/*!< 01: Medium speed	*/
#define GPIO_SPEED_HIGH				(0x2U)		/*!< 10: High speed	    */
#define GPIO_SPEED_VERY				(0x3U)		/*!< 11: Very high speed*/


/*
 * @def_group GPIO_Pins_ALTERNATE_Modes
 *
 *
 */

#define GPIO_AFSEL_0				(0x0U)
#define GPIO_AFSEL_1				(0x1U)
#define GPIO_AFSEL_2				(0x2U)
#define GPIO_AFSEL_3				(0x3U)
#define GPIO_AFSEL_4				(0x4U)
#define GPIO_AFSEL_5				(0x5U)
#define GPIO_AFSEL_6				(0x6U)
#define GPIO_AFSEL_7				(0x7U)
#define GPIO_AFSEL_8				(0x8U)
#define GPIO_AFSEL_9				(0x9U)
#define GPIO_AFSEL_10				(0xAU)
#define GPIO_AFSEL_11				(0xBU)
#define GPIO_AFSEL_12				(0xCU)
#define GPIO_AFSEL_13				(0xDU)
#define GPIO_AFSEL_14				(0xFU)


typedef enum{

	GPIO_Pin_Reset = 0x0U,
	GPIO_Pin_Set = !GPIO_Pin_Reset

}GPIO_PinState_t;

typedef struct{

	uint32_t pinNumber; 	/*!> GPIO Pin Numbers @def_group GPIO_Pins */
	uint32_t Mode;			/*!> GPIO Pin Numbers @def_group GPIO_Pin_Modes */
	uint32_t Otype;			/*!> GPIO Pin Numbers @def_group GPIO_OTYPE_Modes */
	uint32_t PuPd;			/*!> GPIO Pin Numbers @def_group GPIO_PUPDR_Modes */
	uint32_t Speed;			/*!> GPIO Pin Numbers @def_group GPIO_SPEED_Modes */
	uint32_t Alternate;		/*!> GPIO Pin Numbers @def_group GPIO_ALTERNATE_Modes */

}GPIO_InitTypedef_t;

void GPIO_Init(GPIO_Typedef_t* GPIOx, GPIO_InitTypedef_t* GPIO_Config);
void GPIO_WritePin(GPIO_Typedef_t *GPIOx, uint16_t pinNumber, GPIO_PinState_t pinState );
GPIO_PinState_t GPIO_ReadPin(GPIO_Typedef_t* GPIOx, uint16_t pinNumber);
void GPIO_LockPin(GPIO_Typedef_t* GPIOx, uint16_t pinNumber);
void GPIO_TogglePin(GPIO_Typedef_t* GPIOx, uint16_t pinNumber);

#endif /* INC_GPIO_H_ */
