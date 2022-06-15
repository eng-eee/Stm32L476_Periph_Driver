#include "EXTI.h"


/**
 * @brief		GPIO_Init for valid GIO port and Line number
 * @param		EXTI_InitStruct = User Config structure
 *
 * retval  void
 *
 */


void EXTI_Init(EXTI_InitTypedef_t* EXTI_InitStruct)
{
	uint32_t temp = 0;
	temp = (uint32_t)EXTI_BASE_ADDR;

	EXTI->IMR1 &= ~(0x01U << EXTI_InitStruct->EXTI_LineNumber);
	EXTI->EMR1 &= ~(0x01U << EXTI_InitStruct->EXTI_LineNumber);


	if(EXTI_InitStruct->EXTI_LineCmd != DISABLE )
	{
		temp += EXTI_InitStruct->EXTI_Mode;

		*((__IO uint32_t*)temp) |= (0x1U<< EXTI_InitStruct->EXTI_LineNumber);

		temp = (uint32_t)EXTI_BASE_ADDR;
		EXTI->RTSR1 &= ~(0x01U << EXTI_InitStruct->EXTI_LineNumber);
		EXTI->FTSR1 &= ~(0x01U << EXTI_InitStruct->EXTI_LineNumber);

		if(EXTI_InitStruct->TriggerSelection == EXTI_Trigger_RF)
		{
			EXTI->RTSR1 |= (0x01U << EXTI_InitStruct->EXTI_LineNumber);
			EXTI->FTSR1 |= (0x01U << EXTI_InitStruct->EXTI_LineNumber);
		}
		else
		{
			temp += EXTI_InitStruct->TriggerSelection;
			*((__IO uint32_t*)temp) |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}
	}

	else
	{
		temp = (uint32_t)EXTI_BASE_ADDR;
		temp += EXTI_InitStruct->EXTI_Mode;
		*((__IO uint32_t*)temp) &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);

	}
}




/**
 * @brief		GPIO_LineConfig, Configures the port and pin for SYSCFG
 * @param		PortSource = Port Value A - F @def_group PORT_Values
 *
 * @param		EXTI_LineSource = Pin Numbers & Line Numbers  @def group EXTI_Line_Values
 *
 * retval  void
 *
 */



void EXTI_LineConfig(uint8_t Port_Source, uint8_t EXTI_LineSource)
{
	uint32_t temp ;
	temp = SYSCFG->EXTICR[EXTI_LineSource >> 2U]; /* EXTIx bul oku */
	temp = ~(0xFU << ((EXTI_LineSource & 0x3U) << 2)); /*	EXTIx içinde uygun bitleri temizle mod3 * 4 ile	*/
	temp = (Port_Source << ((EXTI_LineSource & 0x3U) << 2 ) );	/* kullanıcının değerini uygun bitlere yaz */
	SYSCFG->EXTICR[EXTI_LineSource >> 2U] = temp;	/* temp değeri register a yaz */
}



/**
 * @brief		NVIC_EnableInterrupt,
 * @param		IRQnumber = IRQnumber of line
 *
 *
 * retval  void
 *
 */


void NVIC_EnableInterrupt(IRQNumber_Typedef_t IRQnumber)
{
	uint32_t temp = 0;
	temp = *( (IRQnumber >> 5U) + NVIC_ISER0 );
	temp &= ~(0x1U << (IRQnumber & 0x1FU) );
	temp |= (0x1U << (IRQnumber & 0x1FU) );
	*( (IRQnumber >> 5U) + NVIC_ISER0 ) = temp;
}

void EXTI_Clear_Interrupt(uint8_t EXTI_LineSource)
{
	EXTI->PR1 |= (1 << EXTI_LineSource);
}

uint8_t EXTI_Status_Interrupt(uint8_t EXTI_LineSource)
{
	uint8_t ret = 0;
	ret = ( EXTI->PR1 & (1 << EXTI_LineSource) );
	return ret;
}
