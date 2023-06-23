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

/*
	1. Set OCxPE bit in CCMRx register 
	2. Set ARPE in CR1 Registor 
	3. Select PWM mode in OCxM bit in  CCMRx register 
	4. Set UG bit in EGR register

*/

void PWM_generate(TIM_TypeDef *pTIMx , uint16_t channel , uint16_t freq , uint16_t duty)
{
		TIMER_PeriClockControl(pTIMx,ENABLE);
		uint16_t arr ,pre , preload ;
		uint32_t clk_freq ;
		arr  = 0xFFFF;
		
		if(pTIMx == TIM1 )	pre = (142000000/(arr*freq)) & (0xffff);
		else{
			pre = (72000000/(arr *freq)) & (0xffff);
		}
		if(pTIMx == TIM1 )	arr = (14200000/((pre+1)*freq)) & (0xffff);
		else{
			arr = (72000000/((pre+1)*freq)) & (0xffff);
		}
		preload = (arr*duty)/100 ;
		pTIMx->CR1 |= TIM_CR1_CMS_0 ;
		pTIMx->CR1 &= ~TIM_CR1_CMS_0 ;
		pTIMx->PSC = pre ;
		pTIMx->ARR = arr ;
		pTIMx->CCER |= (1<<(channel*4));
		if(channel < PWM_CHANNEL_3){
				pTIMx->CCMR1 &= ~(3<<(channel*8));
				pTIMx->CCMR1 |= (1<<((channel*8)+3));
				pTIMx->CCMR1 |= (6<<((channel*8)+4));
		}
		else{
				channel = channel - 2 ;
				pTIMx->CCMR1 &= ~(3<<(channel*8));
				pTIMx->CCMR1 |= (1<<((channel*8)+3));
				pTIMx->CCMR1 |= (6<<((channel*8)+4));
				channel = channel + 2 ;
		}
		pTIMx->CR1 |= TIM_CR1_ARPE ;
		pTIMx->EGR |= TIM_EGR_UG ;
		if(channel == PWM_CHANNEL_1)	pTIMx->CCR1 = preload;
		else if(channel == PWM_CHANNEL_2)	pTIMx->CCR2 = preload;
		else if(channel == PWM_CHANNEL_3)	pTIMx->CCR3 = preload;
		else if(channel == PWM_CHANNEL_4)	pTIMx->CCR4 = preload;
}

