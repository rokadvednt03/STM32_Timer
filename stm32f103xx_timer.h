/**
  ******************************************************************************
  * @file		     stm32f103xx_timer.h
  * @author 		 Vedant A. Rokad
  * @Processor	 ARM Cortex - M3
  * @date    		 28-November-2022
  * @brief   		 TIMER_Peripheral Driver 
  ******************************************************************************
 **/
 
#include "stm32f10x.h"

/****************************************************************************************
*                                                                                       *
*                                     TIMER_MACROS                                      *
*                                                                                       *
/***************************************************************************************/

#define TIMER_COUNTER_UP 	  	0
#define TIMER_COUNTER_DOWN	  1

#define TIMER_CLK_FACTOR_1	1
#define TIMER_CLK_FACTOR_2	2
#define TIMER_CLK_FACTOR_4	4

#define TIMER_ARR_BUFFERED				0
#define TIMER_ARR_NOT_BUFFERED		1

#define TIMER_DELAY_SET_FLAG 			1
#define TIMER_DELAY_RESET_FLAG 		0

#define TIMER_PWM_CHANNEL_1			1
#define TIMER_PWM_CHANNEL_2			2
#define TIMER_PWM_CHANNEL_3			3
#define TIMER_PWM_CHANNEL_4			4

#define TIMER_PWM_MODE_1			6
#define TIMER_PWM_MODE_2			7

/***********************************TIMER_BASE_INIT**************************************
*                                                                                       *
*                                   TIMER_BASE_Init                                     *
*                                                                                       *
/***************************************************************************************/
typedef struct
{
		uint16_t counter_mode ;
		uint16_t clock_div_factor ;
		//uint16_t counter_factor;
		uint16_t ARR_buffer ;
		uint16_t prescalar_value ;
		uint16_t ARR_value ;
		uint16_t counter_freq ;
		
	
}TIM_BASE_Init;


typedef struct
{
	uint16_t pwm_mode;
	uint16_t pwm_duty_cycle;
	uint16_t pwm_freq;
	uint16_t pwm_direction;
	uint16_t pwm_channel ;
}TIM_PWM_BASE_Init;


/********************************TIMER_HANDLE_STRUCTURE**********************************
*                                                                                       *
*                                    TIMER_Handle_t                                     *
*                                                                                       *
/***************************************************************************************/
typedef struct
{
	TIM_TypeDef *ptimer_x;
	TIM_BASE_Init timebase ;
	TIM_PWM_BASE_Init pwmbase;
}TIMER_Handle_t;





/****************************************************************************************
*                                                                                       *
*                              TIMER_APIs_&_HELPING_FUNCTION                            *
*                                                                                       *
/***************************************************************************************/
void TIMER_PERICLK_Enable( TIM_TypeDef *ptimer_x , uint16_t Enordi );
void TIMER_BASE_Init(TIMER_Handle_t *ptimer_handle);
void TIMER_BASE_Deinit(TIMER_Handle_t *ptimer_handle);
void TIMER_PWM_Init(TIMER_Handle_t *ptimer_handle , TIM_PWM_BASE_Init *pwm_base );
void TIMER_Counter_Enable(TIM_TypeDef *ptimerx , uint16_t Enordi );

void TIMER_SET_COUNTER_Delay(TIM_TypeDef *ptimerx , uint16_t delay_ms );
void TIMER_DELAY_FLAG(TIM_TypeDef *ptimer);
void TIM_DELAY_RESET_FLAG(TIM_TypeDef *ptimer);

void TIMER_PWM_PULSE(TIMER_Handle_t *ptimer_handle , TIM_PWM_BASE_Init timer_pwm);
