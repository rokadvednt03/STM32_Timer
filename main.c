#include "stm32f10x.h"
#include "stm32f103xx_gpio_driver.h"
//#include "stm32f103xx_timer.h"
#include <stdint.h>
#include <stdio.h>

int main()
 {
	 int i ; 
		RCC->APB2ENR |= (1<<4);
		RCC->APB2ENR |= (1<<11);
		GPIOC->CRH |= (2<<20) ;
		GPIOC->CRH |= (1<<22) ;
	  
		TIM1->PSC = 65535;
		TIM1->ARR = 2200;
		TIM1->CR1 |= (1<<0);
				 
			 while(1)
				 {
					// for(i = 0 ; i < 100000 ; i++);
					 while(! (TIM1->SR & (1<<0)) );
					 GPIOC->ODR	^= (1<<13);
					 TIM1->SR = 0;
				 }
	 
}

