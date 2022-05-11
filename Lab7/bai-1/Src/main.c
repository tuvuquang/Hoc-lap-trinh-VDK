
#include <stdint.h>
#include <stm32f401re_rcc.h>
#include <stm32f401re_tim.h>
#include <stm32f401re_gpio.h>


#define LED_GREEN_PORT							GPIOA
#define LED_GREEN_PIN							GPIO_Pin_0

static void AppInitCommont(void);
void Led_Init(void);
void Timer_init(void);
void delay(uint32_t ms);
int main(void)
{
	AppInitCommont();

	while(1)
		{
			GPIO_SetBits(LED_GREEN_PORT, LED_GREEN_PIN);
			delay(1000);

			GPIO_ResetBits(LED_GREEN_PORT, LED_GREEN_PIN);

			delay(1000);
		}
}

static void AppInitCommont(void)
{
	SystemCoreClockUpdate();
	Led_Init();
	Timer_init();
}

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;

	GPIO_InitStruct.GPIO_Pin = LED_GREEN_PIN;
	GPIO_Init(LED_GREEN_PORT, &GPIO_InitStruct);

}

void Timer_init(void)
{
	TIM_TimeBaseInitTypeDef Timer_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	Timer_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	Timer_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;

	Timer_InitStructure.TIM_Period = 999;

	Timer_InitStructure.TIM_Prescaler = 83;

	Timer_InitStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM1, &Timer_InitStructure);
	TIM_Cmd(TIM1, ENABLE);

}

void delay(uint32_t ms)
{
	while(ms !=  0 )
	{
		TIM_SetCounter(TIM1, 0);
		while(TIM_GetCounter(TIM1) != 999){};
			ms--;
	}
}
