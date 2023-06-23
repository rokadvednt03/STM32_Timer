#include "stm32f103xx_gpio.h"
#include "stm32f103xx_timer.h"

int main(void)
{
	uint16_t t =0;
	GPIO_Handle_t led ;
	led.pGPIOx = GPIOC;
	led.GPIO_PinConfig.GPIO_ModeInOut = GPIO_OUT_50MHZ;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_PP ;
	led.GPIO_PinConfig.GPIO_PinNumber = 13 ;
	
	
	
	
	GPIO_PeriClockControl(GPIOC,ENABLE);
	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&led);
	led.pGPIOx = GPIOA;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN_OUT_PP ;
	led.GPIO_PinConfig.GPIO_PinNumber = 0 ;
	GPIO_Init(&led);
	TIMER_DELAY(TIM3,1);
	PWM_generate(TIM2,PWM_CHANNEL_1,10000,50);
	TIM2->CR1 |= (1<<0);
	while(1)
	{
			for(t = 0 ; t < 7200 ;t = t + 5)
			{
					TIM2->CCR1 = t ;
					delay_check(TIM3);
			}
			delay_check(TIM3);
			
			for(t = 7200 ; t > 0 ;t = t - 5)
			{
					TIM2->CCR1 = t ;
					delay_check(TIM3);
			}
			delay_check(TIM3);
			delay_check(TIM3);
	}	
}

