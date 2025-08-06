/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../timer/timer.h"

#define N 8

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;
extern char led_value;

extern int i;
extern uint32_t VETT[N];
extern uint32_t var;

extern unsigned int avg_vett(unsigned int VETT[], unsigned int dim, char* flag);

volatile uint32_t val; 
char flag;

void RIT_IRQHandler (void)
{			
	
/*************JOYSTICK***************/
//	static int J_select=0,
//							J_down = 0,
//							J_left = 0,
//							J_right = 0,
//							J_up = 0;
	
	
//	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){
//		/* Joytick J_Select pressed p1.25*/
//		
//		J_select++;
//		switch(J_select){
//			case 1:
//				//your code for J_select here
//			
//				break;
//			default:
//				break;
//		}
//		return;
//	}
//	else if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
//		/* Joytick J_Down pressed p1.26 --> using J_DOWN due to emulator issues*/
//		
//		J_down++;
//		switch(J_down){
//			case 1:
//				//your code for J_down here				

//				break;
//			default:
//				break;
//		}
//		return;
//	}
//	else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
//		/* Joytick J_left pressed p1.27*/
//		
//		J_left++;
//		switch(J_left){
//			case 1:
//				//your code for J_left here				

//				break;
//			default:
//				break;
//		}
//		return;
//	}
//	else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
//		/* Joytick J_Right pressed p1.28*/
//		
//		J_right++;
//		switch(J_right){
//			case 1:
//				//your code for J_right here				

//				break;
//			default:
//				break;
//		}
//		return;
//	}
//	else if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
//		/* Joytick J_Up pressed p1.29*/
//		
//		J_up++;
//		switch(J_up){
//			case 1:
//				//your code for J_up here				

//				break;
//			default:
//				break;
//		}
//		return;
//	}
//	else {
//			J_select = 0;
//			J_down = 0;
//			J_left = 0;
//			J_right = 0;
//			J_up = 0;
//	} 










	if(down_0!=0){  // INT0
		down_0 ++;  
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){

			switch(down_0){
				case 2: {
					
					
					if(i!=0) {
						if(VETT[i-1] != var) {
							VETT[i] = var;
							i++;
						}
					} else {
						VETT[i] = var;
						i++;
					}
					
					
					
				
					
					if(i >= N) {
						disable_timer(0);
						LED_Out(0);
						
						val = avg_vett(VETT,N,&flag);
						
						if(flag == 0) {
							LED_Out(~(val & 0xFF));
						}
						else {
							enable_timer(0);
							LED_Out(1<<6);
							
						}
						
						for(i = 0; i < N; i++) {
								VETT[i] = 0;
						}
						
						i=0;
					}
					
				}	break;
				default:  // pressione continua
					break;
			}
		}
		else {	/* button released */
			down_0=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}



















	if(down_1!=0){  // KEY1
			down_1 ++;  
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){

			switch(down_1){
			case 2:
				
				break;
			default:  // pressione continua
					
				break;
			}
		}
		else {	/* button released */
			down_1=0;			
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 1 pin selection */
		}
	}
	if(down_2!=0){  // KEY2
			down_2 ++;  
			if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
				switch(down_2){
				case 2:
					
					break;
				default:  // pressione continua
					
					break;
			}
		}
		else {	/* button released */
			down_2=0;			
			NVIC_EnableIRQ(EINT2_IRQn); 							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 2 pin selection */
		}
	}
		
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
