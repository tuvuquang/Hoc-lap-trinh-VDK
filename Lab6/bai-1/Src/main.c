

#include <stm32f401re_usart.h>
#include <stm32f401re_rcc.h>
#include <misc.h>
#include <stm32f401re_gpio.h>

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
/*Private Functions	*******************************************************/

uint16_t Data_receive ;
static void Button_init(void);
static void Led_init(void);
static void USART6_TX_Init(void);
static void USART1_RX_Init(void);
static void Delay_ms(uint32_t ms);
static void Control_LED_Received(void);
int main(void)
{
	Led_init();
	Button_init();
	USART6_TX_Init();
	USART1_RX_Init();
	while(1)
	{
		Control_LED_Received();
	}

}
static void Delay_ms(uint32_t ms)
{
	uint32_t i, j;

	for (i = 0 ; i < ms ; i ++)
	{
		for (j = 0; j < 5000; j++) {;}
	}
}
/*
 * @func	Button_init
 * @brief	Initialization Button
 * @param	None
 * @retval	None
 */
static
void Button_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_InitStructure.GPIO_Pin = Button;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*
 * @func	Led_init
 * @brief	Initialization Led
 * @param	None
 * @retval	None
 */
static
void Led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_InitStructure.GPIO_Pin = Led;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}
static void Led_Control(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN,
		uint8_t Status) {
	// SET bit in BSRR Registers

	if (Status == GPIO_PIN_SET) {
		GPIOx->BSRRL = GPIO_PIN;
	}
	if (Status == GPIO_PIN_RESET) {
		GPIOx->BSRRH = GPIO_PIN;
	}
}
static uint8_t GPIO_READ_PIN(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN) {
	uint8_t Read_Pin = 0x00;

	if ((GPIOx->IDR & GPIO_PIN) != (uint32_t) Bit_RESET) {
		Read_Pin = (uint8_t) Bit_SET;
	} else {
		Read_Pin = (uint8_t) Bit_RESET;
	}
	return Read_Pin;
}
/*
 * @func	USART6_TX_Init
 * @brief	Transfer
 * @param	None
 * @retval	None
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

/*
 * @func	USART1_RX_Init
 * @brief	Receved
 * @param	None
 * @retval	None
 */
static
void USART1_RX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	RCC_AHB1PeriphClockCmd(USART1_GPIO_Clock, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = USART1_RX;
	GPIO_Init(USART1_GPIO, &GPIO_InitStructure);

	GPIO_PinAFConfig(USART1_GPIO, GPIO_PinSource10, GPIO_AF_USART1);

// Configure USART
	RCC_APB2PeriphClockCmd(USART1_CLOCK, ENABLE);

	USART_InitStructure.USART_BaudRate = USARTx_Baud;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;

	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);

// NVIC configure
	// Enable USARTx Receive interrupts
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	// NVIC configuration
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*
 * @func	USART1_IRQHandler
 * @brief	Interrupt
 * @param	None
 * @retval	None
 */

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE)== SET)
	{
		Data_receive = USART_ReceiveData(USART1);
	}

}

static
void Control_LED_Received(void)
{
	if(GPIO_READ_PIN(GPIOC,Button)== 0)
	{
		USART_SendData(USART6, 0x10);
	}
	if(Data_receive == Check_Data)
	{
		for(int i=0;i<5;i++)
		{
			Led_Control (GPIOA,Led, GPIO_PIN_SET);
			Delay_ms(1000);
			Led_Control(GPIOA, Led, GPIO_PIN_RESET);
			Delay_ms(1000);
		}
	Data_receive = 0;
	}
	Led_Control (GPIOA, Led, GPIO_PIN_RESET);
}
