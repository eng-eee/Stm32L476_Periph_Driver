
#ifndef SRC_RCC_C_
#define SRC_RCC_C_

#include "RCC.h"

static const uint8_t AHB_Prescaler[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2 ,3, 4, 5, 6, 7, 8, 9};
static const uint8_t APB_Prescaler[] = {0, 0, 0, 0, 1, 2, 3, 4};

uint32_t RCC_GetSystemClock(void)
{
	uint32_t SystemCoreClock = 0;
	uint8_t clock_source = 0;
	clock_source = ( (RCC->CFGR >> 2U ) & 0X3U);

	switch(clock_source)
	{
		case 0: SystemCoreClock = 16000000; break;
		case 1: SystemCoreClock =  8000000; break;

		default : SystemCoreClock = 16000000;
	}

	return SystemCoreClock;
}

uint32_t RCC_GetHClock(void)
{
	uint32_t AHB_PeriphClock = 0;
	uint32_t SystemCoreClock = RCC_GetSystemClock();

	uint8_t prescaler = ( ( RCC->CFGR >> 4U ) & 0xFU);

	AHB_PeriphClock = (SystemCoreClock >> AHB_Prescaler[prescaler]);

	return AHB_PeriphClock;
}

uint32_t RCC_GetAPB1_Clock(void)
{
	uint32_t APB1_Clock = 0;
	uint8_t temp = ( ( RCC->CFGR >> 8U ) & 0x7U );
	APB1_Clock = ( RCC_GetHClock() >> APB_Prescaler[temp] );
	return APB1_Clock;
}

uint32_t RCC_GetAPB2_Clock(void)
{
	uint32_t APB2_Clock = 0;
	uint8_t temp = ( ( RCC->CFGR >> 11U ) & 0x7U );
	APB2_Clock = ( RCC_GetHClock() >> APB_Prescaler[temp] );
	return APB2_Clock;
}

#endif /* SRC_RCC_C_ */
