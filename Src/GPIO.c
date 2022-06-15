
#include "GPIO.h"


/*
 *
 * @brief	GPIO_Init, Configures the port and pin
 * @param	GPIOx = GPIO Port Base Address
 *
 * @param	GPIO_InitTypedef_t = User Configuration Structures
 *
 * @retval  Void
 */


void GPIO_Init(GPIO_Typedef_t* GPIOx, GPIO_InitTypedef_t* GPIO_Config)
{
	uint32_t pos;
	uint32_t fake;

	for ( pos = 0; pos < 16 ; pos++)
	{
		fake = (0x1 << pos);
		if(fake & GPIO_Config->pinNumber)
		{
			/* Mode Config */

			uint32_t tempValue = GPIOx->MODER;

			tempValue &= ~(0x3U << (pos * 2) );
			tempValue |= (GPIO_Config->Mode << (pos * 2) );

			GPIOx->MODER = tempValue;

			if((GPIO_Config->Mode & GPIO_MODE_OUTPUT) || (GPIO_Config->Mode & GPIO_MODE_AF) )
			{
				/* OTYPE Config */
				tempValue = GPIOx->OTYPE;
				tempValue &= ~(0x1U << pos);
				tempValue |= (GPIO_Config->Otype << pos );
				GPIOx->OTYPE = tempValue;

				/* OSPEED Config */
				tempValue = GPIOx->OSPEEDR;
				tempValue &= ~(0x3U) << (pos * 2);
				tempValue |= (GPIO_Config->Speed << (pos * 2) );
				GPIOx->OSPEEDR = tempValue;
			}

			/* PUPDR Config */
			tempValue = GPIOx->PUPDR;
			tempValue &= ~(0x3U) << (pos * 2);
			tempValue |= (GPIO_Config->PuPd << (pos * 2) );
			GPIOx->PUPDR = tempValue;

			/* ALTERNATE Func Config */
			tempValue = GPIOx->AFR[pos >> 3];
			tempValue &= ~(0x0FU << (pos & 0x7U) * 4 );
			tempValue |= (GPIO_Config->Alternate << ( (pos & 0x7U) * 4 ));
			GPIOx->AFR[pos >> 3] = tempValue;

		}
	}
}




/*
 *
 * @brief	GPIO_WritePin, makes pin High or Low
 * @param	GPIOx = GPIO Port Base Address
 *
 * @param	pinNumber = GPIO Pin Numbers 0 - 15
 * @param 	pinState = GPIO_Pin_Set OR GPIO_Pin_Reset
 * @retval  Void
 */

void GPIO_WritePin(GPIO_Typedef_t *GPIOx, uint16_t pinNumber, GPIO_PinState_t pinState )
{

	if(pinState == GPIO_Pin_Set)
		GPIOx->BSRR = pinNumber;
	else
		GPIOx->BSRR = (pinNumber << 16);

}

/*
 *
 * @brief	GPIO_ReadPin, reads the pin of GPIOx Port
 * @param	GPIOx = GPIO Port Base Address
 *
 * @param	pinNumber = GPIO Pin Numbers 0 - 15
 * @retval  pinState = GPIO_PinState
 */

GPIO_PinState_t GPIO_ReadPin(GPIO_Typedef_t* GPIOx, uint16_t pinNumber)
{
	GPIO_PinState_t bitStatus = GPIO_Pin_Reset;

	if(	(GPIOx->IDR & pinNumber) != GPIO_Pin_Reset)
		bitStatus = GPIO_Pin_Set;

	return bitStatus;
}

/*
 *
 * @brief	GPIO_LockPin, Locks the pins of GPIOx Port
 * @param	GPIOx = GPIO Port Base Address
 *
 * @param	pinNumber = GPIO Pin Numbers 0 - 15
 * @retval  Void
 */



void GPIO_LockPin(GPIO_Typedef_t* GPIOx, uint16_t pinNumber)
{
	uint32_t tempValue = (0x01 << 16) | pinNumber;		//1 0000 0000 1101 0000

	GPIOx->LCKR = tempValue; //LCKR[16] = '1' LCKR[15:0] = DATA
 	GPIOx->LCKR = pinNumber; //LCKR[16] = '0' LCKR[15:0] = DATA
	GPIOx->LCKR = tempValue; //LCKR[16] = '1' LCKR[15:0] = DATA
	tempValue = GPIOx->LCKR; //Read Lock Register

}


/*
 *
 * @brief	GPIO_TogglePin, Toggles the pins of GPIOx Port
 * @param	GPIOx = GPIO Port Base Address
 *
 * @param	pinNumber = GPIO Pin Numbers 0 - 15
 * @retval  Void
 */



void GPIO_TogglePin(GPIO_Typedef_t* GPIOx, uint16_t pinNumber)
{
	uint32_t temp = GPIOx->ODR;
	GPIOx->BSRR = ( (temp & pinNumber) << 16 ) | ( ~temp & pinNumber );
}


