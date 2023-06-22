/**
  ******************************************************************************
  * @file    		stm32f103xx_timer.h
  * @author  		Vedant A. Rokad
  * @processor 	ARM Cortex-M3
	* @controller STM32F103C8T8
  * @date    		26-Feb-2022
  * @brief   		Peripheral_Driver Header file
  ******************************************************************************
 **/
 
#include "stm32f10x.h"

#define TIMER_COUNTER_MODE_edge_allign 0
#define TIMER_COUNTER_MODE_center_allign_1 1
#define TIMER_COUNTER_MODE_center_allign_2 2
#define TIMER_COUNTER_MODE_center_allign_3 3


typedef struct 
{
	uint16_t ARR ;
	uint16_t Prescalar ;
	uint32_t counter_mode ;
	
}TIMER_Conf_t ;

typedef struct 
{
	TIM_TypeDef *pTIMx ;
	TIMER_Conf_t timer_conf ;
	
}TIMER_Handle_t ;


void TIMER_PeriClockControl(TIM_TypeDef *pTIMx , uint32_t Enordi);
void TIMER_Init(TIMER_Handle_t *ptimerhandle);
void TIMER_Counter_enable(TIM_TypeDef *pTIMx , uint32_t Enordi);
void TIMER_DELAY(TIM_TypeDef *pTIMx ,uint16_t milisec);
void delay_check(TIM_TypeDef *pTIMx );

