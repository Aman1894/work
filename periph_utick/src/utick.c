/*
 * @brief Micro Tick timer example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include <stdlib.h>
#include <string.h>
#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* uTick interrupt handler */
void UTICK_IRQHandler(void)
{
	Chip_UTICK_ClearInterrupt(LPC_UTICK);
	Board_LED_Toggle(0);
}

/* main function (C entry point) */
int main(void)
{
	int loop = 1;	/* prevents unreachable statement warning */
	/* Setup SystemCoreClock and any needed board code */
	SystemCoreClockUpdate();
	Board_Init();

	/* Enable the power to the Watchdog Oscillator,
	   UTick timer ticks are driven by watchdog oscillator */
	Chip_SYSCON_PowerUp(SYSCON_PDRUNCFG_PD_WDT_OSC);

	/* Initialize UTICK driver */
	Chip_UTICK_Init(LPC_UTICK);

	/* Clear UTICK interrupt status */
	Chip_UTICK_ClearInterrupt(LPC_UTICK);

	/* Set the UTick for a delay of 1000mS and in repeat mode */
	Chip_UTICK_SetDelayMs(LPC_UTICK, 1000, true);

	/* Enable Wake up from deep sleep mode due to UTick */
	Chip_SYSCON_EnableWakeup(SYSCON_STARTER_UTICK);

	/* Enable UTICK interrupt */
	NVIC_EnableIRQ(UTICK_IRQn);

	while (loop) {
		__WFI();
	}

	return 0;
}
