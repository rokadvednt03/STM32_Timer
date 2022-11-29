/**
  ******************************************************************************
  * @file		     stm32f103xx_timer.c
  * @author 		 Vedant A. Rokad
  * @Processor	 ARM Cortex - M3
  * @date    		 28-November-2022
  * @brief   		 TIMER_Peripheral Driver 
  ******************************************************************************
 **/
 
 
#include "stm32f103xx_timer.h"



/****************************************************************************************
*                                                                                       *
*                                TIMER_PERIPHERAL_CLOCK                                 *
*                                                                                       *
/***************************************************************************************/

void TIMER_PERICLK_Enable( TIM_TypeDef *ptimer_x , uint16_t Enordi )
{
		if(Enordi == ENABLE)
		{
					if(ptimer_x == TIM1)
								RCC->APB2ENR |= ( 1 << 11);
					
					else if(ptimer_x == TIM2)
							RCC->APB1ENR |= ( 1 << 0 );
			
					else if(ptimer_x == TIM3)
							RCC->APB1ENR |= ( 1 << 1 );
	
					else if(ptimer_x == TIM4)
							RCC->APB1ENR |= ( 1 << 2 );
		}
		
		else
		{
					if(ptimer_x == TIM1)
							RCC->APB2ENR &= ~( 1 << 11);
					
					else if(ptimer_x == TIM2)
							RCC->APB1ENR &= ~( 1 << 0 );
			
					else if(ptimer_x == TIM3)
							RCC->APB1ENR &= ~( 1 << 1 );
	
					else if(ptimer_x == TIM4)
							RCC->APB1ENR &= ~( 1 << 2 );
		
		}
}






/****************************************************************************************
*                                                                                       *
*                                   TIMER_INITIALIZE                                    *
*                                                                                       *
/***************************************************************************************/
void TIMER_Init(TIMER_Handle_t timer_handle)
{
	//TIMER_CLOCK_FACOR                                                                     
	if(timer_handle.timebase.clock_div_factor == TIMER_CLK_FACTOR_1)	
			timer_handle.ptimer_x->CR1 &= ~(3 << 8);
	else if(timer_handle.timebase.clock_div_factor == TIMER_CLK_FACTOR_2)	
			timer_handle.ptimer_x->CR1 |= (1 << 8);
	else if(timer_handle.timebase.clock_div_factor == TIMER_CLK_FACTOR_4)	
			timer_handle.ptimer_x->CR1 |= (2 << 8);
	
	//TIMER_COUNTER_MODE                                                                    
	if(timer_handle.timebase.counter_mode == TIMER_COUNTER_DOWN)
			timer_handle.ptimer_x->CR1 |= (1 << 4);
	else
			timer_handle.ptimer_x->CR1 &= ~(1<<4);
	
	//TIMER_Auto_Reload_Preload_Enable                                                      
	if(timer_handle.timebase.ARR_buffer == TIMER_ARR_BUFFERED)
			timer_handle.ptimer_x->CR1 |= (1 << 7);
	else
			timer_handle.ptimer_x->CR1 &= ~(1<<7);
	
	//TIMER_PRESCELAR                                                                       
	timer_handle.ptimer_x->PSC |= timer_handle.timebase.prescalar_value;

	//TIMER_ARR                                                                             
	timer_handle.ptimer_x->ARR |= timer_handle.timebase.ARR_value;
	
}






/****************************************************************************************
*                                                                                       *
*                                   TIMER_DEINITIALIZE                                  *
*                                                                                       *
/***************************************************************************************/
void TIMER_Deinit(TIMER_Handle_t timer_handle)
{

}	

void TIMER_Counter_Enable(void);

