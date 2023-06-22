#include "stm32f103xx_gpio.h"
#include "stm32f103xx_timer.h"

int main(void)
{
	GPIO_Handle_t led ;
	
	led.pGPIOx = GPIOC;
	led.GPIO_PinConfig.GPIO_ModeInOut = GPIO_OUT_50MHZ;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_PP ;
	led.GPIO_PinConfig.GPIO_PinNumber = 13 ;
	
	GPIO_PeriClockControl(GPIOC,ENABLE);
	GPIO_Init(&led);

	TIMER_DELAY(TIM2,4000);

	while(1)
	{
				GPIOC->ODR ^= (1<<13);
				delay_check(TIM2);
				
	}
}

