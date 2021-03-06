#include <stdint.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_exti.h>
#include <stm32f401re_syscfg.h>
#include <stm32f401re_rcc.h>
#include <misc.h>

// Define Logic GPIO_PIN

#define GPIO_PIN_SET						1
#define GPIO_PIN_RESET						0
#define GPIO_PIN_LOW						0
#define GPIO_PIN_HIGH						1

// Define GPIO PIN

#define LED_GPIO_PORT						GPIOA
#define LED_GPIO_PIN						GPIO_Pin_5
#define LED_PIN9							5
#define LEDControl_SetClock					RCC_AHB1Periph_GPIOA

#define BUTTON_GPIO_PORT					GPIOC
#define BUTTON_GPIO_PIN						GPIO_Pin_13
#define BUTTON_PIN3							13
#define BUTTONControl_SetClock				RCC_AHB1Periph_GPIOC

#define SYSFG_Clock							RCC_APB2Periph_SYSCFG
uint8_t Status=1;

void delay()
{
	for(uint32_t i = 0;i<500000;i++);
}
static void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(LEDControl_SetClock, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}

static void Interrupt_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


// Enable Clock Port C;
	RCC_AHB1PeriphClockCmd(BUTTONControl_SetClock, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = BUTTON_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);


//  Enable Clock Syscfg, Connect EXTI Line 13 to PC13 pin

	RCC_APB2PeriphClockCmd(SYSFG_Clock, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);


//	Configuration Interrupt

	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

// Configuration NVIC

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetFlagStatus(EXTI_Line13) == SET)
	{
		// ki???m tra s??? ki???n ng???t c?? ????ng tr??n ch??n PC13 hay kh??ng
		Status++;
	}
		//x??a c??? ng???t sau khi th???c hi???n xong ch????ng tr??nh ng???t.
		EXTI_ClearITPendingBit(EXTI_Line13);
}

static void LedControl_SetStatus(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN,
		uint8_t Status) {
	// SET bit in BSRR Registers

	if (Status == GPIO_PIN_SET) {
		GPIOx->BSRRL = GPIO_PIN;
	}
	if (Status == GPIO_PIN_RESET) {
		GPIOx->BSRRH = GPIO_PIN;
	}
}

int main(void)
{
	SystemCoreClockUpdate();
	Led_Init();
	Interrupt_Init();
	while(1)
	{
		if(Status % 2 != 0)
		{
			LedControl_SetStatus(LED_GPIO_PORT, LED_GPIO_PIN, 0);
		}
		else
		{
			LedControl_SetStatus(LED_GPIO_PORT, LED_GPIO_PIN, 1);
		}
	}
}
