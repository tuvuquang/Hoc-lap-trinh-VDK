#include <stdint.h>
#include <stm32f401re_adc.h>
#include <stm32f401re_usart.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_rcc.h>
#include <timer.h>

#include <typedefs.h>

/******************************************************************************/
/*                     PRIVATE TYPES and DEFINITIONS                         */
/******************************************************************************/


/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define ADC_GPIO_PIN							GPIO_Pin_0
#define ADC_GPIO_PORT							GPIOA
#define GPIO_PIN_SET				1
#define GPIO_PIN_RESET				0
#define GPIO_PIN_LOW				0
#define GPIO_PIN_HIGH				1

#define Led							GPIO_Pin_0
#define Pin_Led						0
#define Pin_Button					13
#define Button						GPIO_Pin_13

#define USART6_TX					GPIO_Pin_6
#define USART6_GPIO					GPIOC
#define USART6_GPIO_Clock			RCC_AHB1Periph_GPIOC
#define USART6_CLOCK				RCC_APB2Periph_USART6

#define USART1_RX					GPIO_Pin_10
#define USART1_GPIO					GPIOA
#define USART1_GPIO_Clock			RCC_AHB1Periph_GPIOA
#define USART1_CLOCK				RCC_APB2Periph_USART1

#define USARTx_Baud					9600

#define Check_Data					0x10
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

static void_t USART6_TX_Init(void_t);
void delayms(void);

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/

int main(void_t)
{
	SystemCoreClockUpdate();
	USART6_TX_Init();

	while(1)
	{

		USART_SendData(USART6, 0x10);
		delayms();

	}
}

/*
 * @func   USART2_Init
 * @brief  Initialize USART2
 * @param  None
 * @retval None
 */
static
void USART6_TX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;


	RCC_AHB1PeriphClockCmd(USART6_GPIO_Clock, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = USART6_TX;
	GPIO_Init(USART6_GPIO, &GPIO_InitStructure);

	GPIO_PinAFConfig(USART6_GPIO, GPIO_PinSource6, GPIO_AF_USART6);

// Configure USART
	RCC_APB2PeriphClockCmd(USART6_CLOCK, ENABLE);

	USART_InitStructure.USART_BaudRate = USARTx_Baud;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;

	USART_Init(USART6, &USART_InitStructure);
	USART_Cmd(USART6, ENABLE);

}
void delayms() {
	for (u32_t i = 0; i < 500000; i++);
}

