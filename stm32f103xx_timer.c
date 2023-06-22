/**
  ******************************************************************************
  * @file    		stm32f103xx_timer.c
  * @author  		Vedant A. Rokad
  * @processor 	ARM Cortex-M3
	* @controller STM32F103C8T8
  * @date    		22 - June - 2023
  * @brief   		Peripheral_Driver Source file
  ******************************************************************************
 **/
 
#include "stm32f103xx_timer.h"

void TIMER_PeriClockControl(TIM_TypeDef *pTIMx , uint32_t Enordi)
{
	if(Enordi == ENABLE)
	{
		if(pTIMx == TIM1)		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN ;
		if(pTIMx == TIM2)		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN ;
		if(pTIMx == TIM3)		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN ;
		if(pTIMx == TIM4)		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN ;
	}
	else
	{
		if(pTIMx == TIM1)		RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN ;
		if(pTIMx == TIM2)		RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN ;
		if(pTIMx == TIM3)		RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN ;
		if(pTIMx == TIM4)		RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN ;
	}
}

void TIMER_Init(TIMER_Handle_t *ptimerhandle)
{
	TIMER_PeriClockControl(ptimerhandle->pTIMx,ENABLE);
	/*Config Auto Reload Registor*/
	ptimerhandle->pTIMx->ARR = ptimerhandle->timer_conf.ARR ;
	/*Config Presclar registor*/
	ptimerhandle->pTIMx->PSC = ptimerhandle->timer_conf.Prescalar ;
	/*Config Counter Mode*/
	if(ptimerhandle->timer_conf.counter_mode == TIMER_COUNTER_MODE_edge_allign) ptimerhandle->pTIMx->CR1 &= ~TIM_CR1_CMS ;
	else if(ptimerhandle->timer_conf.counter_mode == TIMER_COUNTER_MODE_center_allign_1) {
			ptimerhandle->pTIMx->CR1 |= TIM_CR1_CMS_0 ;
			ptimerhandle->pTIMx->CR1 &= ~TIM_CR1_CMS_1 ;	
	}
	else if(ptimerhandle->timer_conf.counter_mode == TIMER_COUNTER_MODE_center_allign_2) {
			ptimerhandle->pTIMx->CR1 &= ~TIM_CR1_CMS_0 ;
			ptimerhandle->pTIMx->CR1 |= TIM_CR1_CMS_1 ;	
	}
	else if(ptimerhandle->timer_conf.counter_mode == TIMER_COUNTER_MODE_center_allign_3) {
			ptimerhandle->pTIMx->CR1 &= ~TIM_CR1_CMS_0 ;
			ptimerhandle->pTIMx->CR1 &= ~TIM_CR1_CMS_1 ;	
	}
}

void TIMER_Counter_enable(TIM_TypeDef *pTIMx , uint32_t Enordi)
{
		if(Enordi == ENABLE) pTIMx->CR1 |= (1<<0) ;
		else{
			pTIMx->CR1 &= ~(1<<0) ;
		}
}

void TIMER_DELAY(TIM_TypeDef *pTIMx ,uint16_t milisec)
{
	uint16_t pre,arr ;
	pre = 0x8C9F ;
	TIMER_PeriClockControl(pTIMx,ENABLE);
	if(pTIMx == TIM1 ) arr = milisec/2 ;
	else{
		arr = milisec ;
	}
	pTIMx->PSC = pre ;
	pTIMx->ARR = arr ;
}

void delay_check(TIM_TypeDef *pTIMx )
{
		pTIMx->CR1 |= (1<<0) ; // counter start 
		while(!(pTIMx->SR & (TIM_SR_UIF)));
		pTIMx->SR &= ~(1 << 0);
		pTIMx->CR1 &= ~(1<<0) ; 
}


