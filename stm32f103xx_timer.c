#include "stm32f10x.h"
#include "stm32f103xx_timer.h"

void TIMER_Enable(TIM_TypeDef *ptimx ,uint8_t Enordi)
{
	if(Enordi == ENABLE)
	{
			if(ptimx == TIM1)
			{
				RCC->APB2ENR |= (1 << 11 );
			}
			else if(ptimx == TIM2)
			{
				RCC->APB2ENR |= (1 << 11 );
			}
			else if(ptimx == TIM3)
			{
				RCC->APB2ENR |= (1 << 11 );
			}
			else if(ptimx == TIM4)
			{
				RCC->APB2ENR |= (1 << 11 );
			}
			else if(ptimx == TIM6)
			{
				RCC->APB2ENR |= (1 << 11 );
			}
			else if(ptimx == TIM7)
			{
				RCC->APB2ENR |= (1 << 11 );
			}
	}
	else
	{
			if(ptimx == TIM1)
			{
				RCC->APB2ENR &= ~(1 << 11 );
			}
			else if(ptimx == TIM2)
			{
				RCC->APB2ENR &= ~(1 << 11 );
			}
			else if(ptimx == TIM3)
			{
				RCC->APB2ENR &= ~(1 << 11 );
			}
			else if(ptimx == TIM4)
			{
				RCC->APB2ENR &= ~(1 << 11 );
			}
			else if(ptimx == TIM6)
			{
				RCC->APB2ENR &= ~(1 << 11 );
			}
			else if(ptimx == TIM7)
			{
				RCC->APB2ENR &= ~(1 << 11 );
			}
	
	}
}



void TIMER_Init(timer_handle_t *ptimer_handle_t)
{
	
	//upcounter or downcounter
	if(ptimer_handle_t->timconfig.TIMER_DIR == TIMER_DIR_DOWN)
	{
		ptimer_handle_t->ptimx->CR1 |= (1<<4);
	}
	else
	{
		ptimer_handle_t->ptimx->CR1 &= ~(1<<4);
	}
	
	
	//timer division factor
	if(ptimer_handle_t->timconfig.TIMER_DIV == TIMER_DIV_1)
	{
		ptimer_handle_t->ptimx->CR1 &= ~( 1 << 8 );
	}
	else if(ptimer_handle_t->timconfig.TIMER_DIV == TIMER_DIV_2)
	{
		ptimer_handle_t->ptimx->CR1 |= ( 1 << 8 );
	}
	else if(ptimer_handle_t->timconfig.TIMER_DIV == TIMER_DIV_4)
	{
		ptimer_handle_t->ptimx->CR1 |= ( 2 << 8 );
	}
}



void TIMER_COUNTER_Enable(TIM_TypeDef *ptimx ,uint8_t Enordi)
{
	if(Enordi == ENABLE )
	{
		ptimx->CR1 |= (1<<0);
	}
	else
	{
		ptimx->CR1 &= ~(1<<0);
	}
}

