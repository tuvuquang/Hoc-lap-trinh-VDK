
#include <stdint.h>
#include <stm32f401re_rcc.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_spi.h>
#include <misc.h>

//Define Macro******************************************************************
#define GPIO_PIN_SET											1
#define GPIO_PIN_RESET											0
#define GPIO_PIN_LOW											0
#define GPIO_PIN_HIGH											1

#define Led_Board												GPIO_Pin_1
#define Led														GPIO_Pin_0
#define Pin_Led													0
#define Button													GPIO_Pin_13
#define Pin_Button												13
#define Pin_NSS													12

#define SPI_Master_GPIO_Clock									RCC_AHB1Periph_GPIOB
#define SPI_Master_Clock										RCC_APB1Periph_SPI2
#define SPI_Master_GPIO											GPIOB
#define SPI_Master												SPI2
#define NSS_Master												GPIO_Pin_12
#define SCK_Master												GPIO_Pin_13
#define MISO_Master												GPIO_Pin_14
#define MOSI_Master												GPIO_Pin_15

#define SPI_Slave_GPIO_Clock									RCC_AHB1Periph_GPIOA
#define SPI_Slave_Clock											RCC_APB2Periph_SPI1
#define SPI_Slave_GPIO											GPIOA
#define SPI_Slave												SPI1
#define NSS_Slave												GPIO_Pin_4
#define SCK_Slave												GPIO_Pin_5
#define MISO_Slave												GPIO_Pin_6
#define MOSI_Slave												GPIO_Pin_7

#define Check_DataSlave											0xB1



//Private Variable*******************************************************
uint8_t Recive_Data = 0;
uint16_t Recive_Data_Master = 0;
static void AppInitCommon(void);
static void SPI2_Master_Init(void);
static void SPI1_Slave_Init(void);
static uint8_t GPIO_Read_Pin(GPIO_TypeDef * GPIOx, uint32_t GPIO_PIN);
static void Led_init(void);
static void Button_init(void);
static uint8_t Revice_Data_Slave(SPI_TypeDef *SPIx);
static void Send_Data(SPI_TypeDef *SPIx, uint8_t data);
//static uint8_t GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint32_t GPIO_PIN);
static void GPIO_PinControl(GPIO_TypeDef *GPIOx, uint8_t GPIO_PIN, uint8_t Status);
static void Delay(uint32_t ms);
static void Revice_Data_Master(SPI_TypeDef *SPIx, uint16_t *My_Data);

int main(void)
{
	AppInitCommon();
	while(1)
	{
	//Send data when Button pressed-----------------------------------------
		if(GPIO_Read_Pin(GPIOC, Pin_Button) == 0)
		{
			Send_Data(SPI2, 0xB1);
		}
		//Turn on led when data = 0x20------------------------------------------
		if (Recive_Data == Check_DataSlave)
		{
			for (int i = 0; i<5; i++)
			{
				GPIO_PinControl(GPIOA, Pin_Led, GPIO_PIN_SET);
				Delay(1000);
				GPIO_PinControl(GPIOA, Pin_Led, GPIO_PIN_RESET);
				Delay(1000);
			}
			Recive_Data = 0;

			Send_Data(SPI1, 0x43);

			Revice_Data_Master(SPI2, &Recive_Data_Master);
			if(Recive_Data_Master == 0x43)
			{
				GPIO_SetBits(GPIOA, Led_Board);
				Recive_Data_Master = 0;
			}

		}
		GPIO_PinControl(GPIOA, Pin_Led, GPIO_PIN_RESET);

	}
}

/**
 * @func   Delay Time
 * @brief  Delay
 * @param  None
 * @retval None
 */
static
void Delay(uint32_t ms)
{
	uint32_t i,j;
	for (i = 0 ; i < ms ; i ++)
	{
		for (j = 0; j<5000; j++){;}
	}
}
/**
 * @func   Initializes SPI Master
 * @brief  SPI_InitMaster
 * @param  None
 * @retval None
 */
static void SPI2_Master_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef	 SPI_InitStructure;


	// Connect Clock to GPIOB--------------------------------------------------
	RCC_AHB1PeriphClockCmd(SPI_Master_GPIO_Clock, ENABLE);

	// Initialization GPIO use for SPI-----------------------------------------

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	GPIO_InitStructure.GPIO_Pin = SCK_Master| MISO_Master | MOSI_Master;
	GPIO_Init(SPI_Master_GPIO, &GPIO_InitStructure);

	// Connect SPI1 pins to SPI Alternate function

	GPIO_PinAFConfig(SPI_Master_GPIO, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI_Master_GPIO, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI_Master_GPIO, GPIO_PinSource15, GPIO_AF_SPI2);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = NSS_Master;
	GPIO_Init(SPI_Master_GPIO, &GPIO_InitStructure);

	//Enable peripheral clock----------------------------------------------
	RCC_APB1PeriphClockCmd(SPI_Master_Clock, ENABLE);

	//Set to full duplex mode, seperate MOSI and MISO----------------------
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;

	//Transmit in master mode----------------------------------------------
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

	//one packet of data 8 bits wide---------------------------------------
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

	//Clock is low when idle-----------------------------------------------
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;

	//Data sampled at first edge-------------------------------------------
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;

	//Set NSS Software-----------------------------------------------------
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	//SPI frequency	is APB2 frequency/4 -----------------------------------
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;

	//Data is transmitted LSB first----------------------------------------
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;

	SPI_Init(SPI_Master, &SPI_InitStructure);

	//Enable SPI2----------------------------------------------------------
	SPI_Cmd(SPI_Master, ENABLE);

}

/**
 * @func   Initializes SPI Slave
 * @brief  SPI_InitSlave
 * @param  None
 * @retval None
 */
static void SPI1_Slave_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef	 SPI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// Connect Clock to GPIOB--------------------------------------------------
	RCC_AHB1PeriphClockCmd(SPI_Slave_GPIO_Clock, ENABLE);

	// Initialization GPIO use for SPI-----------------------------------------

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = SCK_Slave | MISO_Slave | MOSI_Slave;
	GPIO_Init(SPI_Slave_GPIO, &GPIO_InitStructure);

	// Connect SPI1 pins to SPI Alternate function

	GPIO_PinAFConfig(SPI_Slave_GPIO, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(SPI_Slave_GPIO, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(SPI_Slave_GPIO, GPIO_PinSource7, GPIO_AF_SPI1);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = NSS_Slave;
	GPIO_Init(SPI_Slave_GPIO, &GPIO_InitStructure);

	//Enable peripheral clock----------------------------------------------
	RCC_APB2PeriphClockCmd(SPI_Slave_Clock, ENABLE);

	//Set to full duplex mode, seperate MOSI and MISO----------------------
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;

	//Transmit in Slave mode----------------------------------------------
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;

	//one packet of data 8 bits wide---------------------------------------
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

	//Clock is low when idle-----------------------------------------------
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;

	//Data sampled at first edge-------------------------------------------
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;

	//Set NSS Software-----------------------------------------------------
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	//SPI frequency	is APB2 frequency/4 -----------------------------------
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;

	//Data is transmitted LSB first----------------------------------------
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;

	SPI_Init(SPI_Slave, &SPI_InitStructure);

	//Enable SPI1----------------------------------------------------------
	SPI_Cmd(SPI_Slave, ENABLE);

	SPI_I2S_ITConfig(SPI_Slave, SPI_I2S_IT_RXNE, ENABLE);
	//NVIC configuration---------------------------------------------------
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init( &NVIC_InitStructure);

	SPI_I2S_ITConfig(SPI_Slave, SPI_I2S_IT_RXNE, ENABLE);
}

/**
 * @func   Control Led Turn_On or Turn_Off
 * @brief  Led_Control
 * @param  None
 * @retval None
 */

static void GPIO_PinControl(GPIO_TypeDef *GPIOx, uint8_t GPIO_PIN,
		uint8_t Status) {
	// SET bit in BSRR Registers

	if (Status == GPIO_PIN_SET) {
		GPIOx->BSRRL |= 1 << GPIO_PIN;
	}
	if (Status == GPIO_PIN_RESET) {
		GPIOx->BSRRH |= 1 << GPIO_PIN;
	}
}
static
void Send_Data(SPI_TypeDef * SPIx, uint8_t data)
{
	//Allow Send Data to Slave--------------------------------------------------
	GPIO_PinControl (SPI_Master_GPIO, Pin_NSS, GPIO_PIN_RESET);

	SPI_I2S_SendData(SPIx,data);

	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET){;}

	//Allow Send Data to Slave--------------------------------------------------
	GPIO_PinControl (SPI_Master_GPIO, Pin_NSS, GPIO_PIN_SET);
}



/**
 * @func   Recive Data From Master
 * @brief  Revice_Data
 * @param  None
 * @retval None
 */
static
uint8_t Revice_Data_Slave(SPI_TypeDef * SPIx)
{
	uint8_t Data_Revice = 0;

	Data_Revice = SPI_I2S_ReceiveData(SPIx);

	return Data_Revice;
}

static void Revice_Data_Master(SPI_TypeDef *SPIx, uint16_t *My_Data)
{
	SPI2->DR &= 0xff;
	Delay(10);
	*My_Data = SPI_I2S_ReceiveData(SPIx);

	while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY)== SET)
		{;}
}

/**
 * @func   Read Logic On GPIO
 * @brief  GPIO_READ_PIN
 * @param  None
 * @retval None
 */
static
uint8_t GPIO_Read_Pin(GPIO_TypeDef * GPIOx, uint32_t GPIO_PIN)
{
	uint32_t Read_Pin;

	//Read bit in IDR Registers-------------------------------------------------
	Read_Pin = (GPIOx->IDR) >> GPIO_PIN;
	Read_Pin = Read_Pin & 0x01;

	return Read_Pin;
}

/**
 * @func   The Function Executes The Interrupt
 * @brief  SPI1_IRQHandler
 * @param  None
 * @retval None
 */
void SPI1_IRQHandler(void)
{
	if(SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) == SET)
	{
		Recive_Data = Revice_Data_Slave(SPI1);
	}
	SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_RXNE);
}


/**
 * @func   Initializes GPIO Use Led
 * @brief  Led_Init
 * @param  None
 * @retval None
 */
static void Led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = Led | Led_Board ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

}


/**
 * @func   Initializes GPIO Use Button
 * @brief  Button_Init
 * @param  None
 * @retval None
 */
static void Button_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = Button;

	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

static
void AppInitCommon(void)
{
	SystemCoreClockUpdate();

	Button_init();

	Led_init();

	SPI2_Master_Init();

	SPI1_Slave_Init();


}

