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
#include <stdio.h>


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

void TIMER_BASE_Init(TIMER_Handle_t *timer_handle)
{
	//TIMER_CLOCK_FACOR                                                                     
	if(timer_handle->timebase.clock_div_factor == TIMER_CLK_FACTOR_1)	
			timer_handle->ptimer_x->CR1 &= ~(3 << 8);
	else if(timer_handle->timebase.clock_div_factor == TIMER_CLK_FACTOR_2)	
			timer_handle->ptimer_x->CR1 |= (1 << 8);
	else if(timer_handle->timebase.clock_div_factor == TIMER_CLK_FACTOR_4)	
			timer_handle->ptimer_x->CR1 |= (2 << 8);
	
	//TIMER_COUNTER_MODE                                                                    
	if(timer_handle->timebase.counter_mode == TIMER_COUNTER_DOWN)
			timer_handle->ptimer_x->CR1 |= (1 << 4);
	else
			timer_handle->ptimer_x->CR1 &= ~(1<<4);
	
	//TIMER_Auto_Reload_Preload_Enable                                                      
	if(timer_handle->timebase.ARR_buffer == TIMER_ARR_BUFFERED)
			timer_handle->ptimer_x->CR1 |= (1 << 7);
	else
			timer_handle->ptimer_x->CR1 &= ~(1<<7);
	
	//TIMER_PRESCELAR                                                                       
	timer_handle->ptimer_x->PSC = timer_handle->timebase.prescalar_value;

	//TIMER_ARR                                                                             
	timer_handle->ptimer_x->ARR = timer_handle->timebase.ARR_value;
	
	//TIMER_CLOCK                                                                             
	if(timer_handle->timebase.counter_freq)
	{
		uint32_t arr , psc ;
		psc = 0xFFFF ;
		timer_handle->ptimer_x->PSC = (uint16_t)psc ;
		arr =  (72000000 / ((psc + 1) * (timer_handle->timebase.counter_freq))) - 1;
		timer_handle->ptimer_x->ARR = (uint16_t)arr ;
		
	}

}


/****************************************************************************************
*                                                                                       *
*                                       PWM_INIT                                        *
*                                                                                       *
/***************************************************************************************/
void TIMER_PWM_Init(TIMER_Handle_t *ptimer_handle, TIM_PWM_BASE_Init *pwm_base )
{
				
			uint16_t psc,arr,pulse;
			psc = 719;
			
			arr = (72000000 / ((psc + 1 )*(pwm_base->pwm_freq))) - 1 ;

			pulse = (arr*(pwm_base->pwm_duty_cycle)) / 100 ;
	
			if(pwm_base->pwm_channel == TIMER_PWM_CHANNEL_1)
			{
					ptimer_handle->ptimer_x->CCER |= (1<<0);
					if(pwm_base->pwm_mode == TIMER_PWM_MODE_1)
							ptimer_handle->ptimer_x->CCMR1 |= (TIMER_PWM_MODE_1 << 4);
					else if(pwm_base->pwm_mode == TIMER_PWM_MODE_2)
							ptimer_handle->ptimer_x->CCMR1 |= (TIMER_PWM_MODE_2 << 4);
					ptimer_handle->ptimer_x->CCR1 = pulse ;
			}
			else if(pwm_base->pwm_channel == TIMER_PWM_CHANNEL_2)
			{
				ptimer_handle->ptimer_x->CCER |= (1<<4);
				if(pwm_base->pwm_mode == TIMER_PWM_MODE_1)
							ptimer_handle->ptimer_x->CCMR1 |= (TIMER_PWM_MODE_1 << 12);
				else if(pwm_base->pwm_mode == TIMER_PWM_MODE_2)
							ptimer_handle->ptimer_x->CCMR1 |= (TIMER_PWM_MODE_2 << 12);
				ptimer_handle->ptimer_x->CCR2 = pulse ;
			}
			else if(pwm_base->pwm_channel == TIMER_PWM_CHANNEL_3)
			{
				ptimer_handle->ptimer_x->CCER |= (1<<8);
				if(pwm_base->pwm_mode == TIMER_PWM_MODE_1)
							ptimer_handle->ptimer_x->CCMR2 |= (TIMER_PWM_MODE_1 << 4);
				else if(pwm_base->pwm_mode == TIMER_PWM_MODE_2)
							ptimer_handle->ptimer_x->CCMR2 |= (TIMER_PWM_MODE_2 << 4);
				ptimer_handle->ptimer_x->CCR3 = pulse ;
			}
			else if(pwm_base->pwm_channel == TIMER_PWM_CHANNEL_4)
			{
				ptimer_handle->ptimer_x->CCER |= (1<<12);
				if(pwm_base->pwm_mode == TIMER_PWM_MODE_1)
							ptimer_handle->ptimer_x->CCMR2 |= (TIMER_PWM_MODE_1 << 12);
				else if(pwm_base->pwm_mode == TIMER_PWM_MODE_2)
							ptimer_handle->ptimer_x->CCMR2 |= (TIMER_PWM_MODE_2 << 12);
				ptimer_handle->ptimer_x->CCR4 = pulse ;
			}
			ptimer_handle->ptimer_x->ARR = arr ;			
			ptimer_handle->ptimer_x->PSC = psc;
}

/****************************************************************************************
*                                                                                       *
*                                 TIMER_COUNTER_ENABLE                                  *
*                                                                                       *
/***************************************************************************************/
void TIMER_PWM_PULSE(TIMER_Handle_t *ptimer_handle , TIM_PWM_BASE_Init timer_pwm)
{

}

/****************************************************************************************
*                                                                                       *
*                                 TIMER_COUNTER_ENABLE                                  *
*                                                                                       *
/***************************************************************************************/
void TIMER_Counter_Enable(TIM_TypeDef *ptimerx , uint16_t Enordi )
{
		if(Enordi == ENABLE)
		{
			ptimerx->CR1 |= (1 << 0);
		}
		else
		{
			ptimerx->CR1 &= ~(1 << 0);
		}
}

/****************************************************************************************
*                                                                                       *
*                                   TIMER_DELAY				                                  *
*                                                                                       *
/***************************************************************************************/
//TIMER_SET_COUNTER_Delay                                                               
void TIMER_SET_COUNTER_Delay(TIM_TypeDef *ptimerx , uint16_t delay_ms )
{
		uint16_t psc , arr ;
		psc = 0xFFFF ;
		ptimerx->PSC = psc  ;
			
		arr = (72000000 / ((psc + 1 )*(delay_ms))) - 1 ;
		
		ptimerx->ARR = arr ;
}

//TIMER_DELAY_FLAG                                                                      
void TIMER_DELAY_FLAG(TIM_TypeDef *ptimer)
{
	while(! (ptimer->SR & (1<<0)) );
}

//TIMER_DELAY_RESET_FLAG                                                                
void TIM_DELAY_RESET_FLAG(TIM_TypeDef *ptimer)
{
		ptimer->SR = 0x0000 ;	
}
