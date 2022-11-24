#include "stm32f10x.h"


#define TIMER_DIR_UP 0
#define TIMER_DIR_DOWN 1

#define TIMER_DIV_1	1
#define TIMER_DIV_2	2
#define TIMER_DIV_4	4

typedef struct
{
	uint16_t TIMER_DIR;										//clock_direction
	uint16_t TIMER_DIV;										//clock_division
	uint16_t TIMER_Prescaler ;						//timer_prescaler
	uint16_t TIMER_Counter_Mode ; 				//timer_counter_mode
	uint16_t TIMER_Repetition_Counter ;		//
	

}TIMER_Config_t;


typedef struct
{

	TIM_TypeDef *ptimx;
	TIMER_Config_t timconfig;
	
}timer_handle_t;


void TIMER_Init(timer_handle_t *ptimer_handle_t);
void TIMER_Enable(TIM_TypeDef *ptimx ,uint8_t Enordi);
void TIMER_COUNTER_Enable(TIM_TypeDef *ptimx ,uint8_t Enordi);

