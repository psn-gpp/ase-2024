/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through EINT buttons and manage the bouncing effect
 *        	- key1 switches on the led at the left of the current led on, 
 *					- it implements a circular led effect. 	
  * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
//#include "joystick/joystick.h"
#include "adc/adc.h"

#define N 8

volatile uint32_t var = 0;
volatile uint32_t VETT[N];
volatile int i;


/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in funct_led								*/
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	
	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	init_RIT(0x001312D0);									/* RIT Initialization 50 msec         */
	enable_RIT();												  /* enable RIT to count 50ms				    */
	init_timer(0, 0x010B0760);						/* enable timer 0 to 700ms */
	init_timer(1, 0x02887FA0);					  /* enable timer 1 to 1,7s on a clk of 25 MHz	*/
	init_timer(2,0x2B82EA80);							/* enable timer 2 to 14,6s on a clk of 50 MHz */
	//joystick_init();										  /* JOYSTICK initialization					  */
	//ADC_init();

	
	
	for(i = 0; i < N; i++) {
			VETT[i] = 0;
	}
	
	i=0;
	
	enable_timer(1);
	enable_timer(2);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		
  }

}
