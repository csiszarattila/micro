#include "../cmsis/stm32f103.h"

extern int _estack;

int main(void);
void uart_tx(uint16_t *data, uint8_t len);
void dma1_channel4_interrupt(void);
uint32_t get_uart_brr_value(uint32_t baudrate);

uint32_t (* const vector_table[])
__attribute__ ((section(".vector_table"))) = {
	(uint32_t *) &_estack,         /* 0x000 Stack Pointer                             */
	(uint32_t *) main,             /* 0x004 Reset                                     */
	0,                             /* 0x008 Non maskable interrupt                    */
	0,                             /* 0x00C Hard fault                                */
	0,                             /* 0x010 Memory management fault                   */
	0,                             /* 0x014 Bus fault                                 */
	0,                             /* 0x018 Usage fault                               */
	0,                             /* 0x01C Reserved                                  */
	0,                             /* 0x020 Reserved                                  */
	0,                             /* 0x024 Reserved                                  */
	0,                             /* 0x028 Reserved                                  */
	0,                             /* 0x02C System service call via SWI instruction   */
	0,                             /* 0x030 Debug Monitor                             */
	0,                             /* 0x034 Reserved                                  */
	0,                             /* 0x038 Pendable request for system service       */
	0,                             /* 0x03C System tick timer                         */
	0,                             /* 0x040 Window Watchdog interrupt                 */
	0,                             /* 0x044 PVD through EXTI Line detection interrupt */
	0,                             /* 0x048 Tamper interrupt                          */
	0,                             /* 0x04C RTC global interrupt                      */
	0,                             /* 0x050 Flash global interrupt                    */
	0,                             /* 0x054 RCC global interrupt                      */
	0,                             /* 0x058 EXTI Line0 interrupt                      */
	0,                             /* 0x05C EXTI Line1 interrupt                      */
	0,                             /* 0x060 EXTI Line2 interrupt                      */
	0,                             /* 0x064 EXTI Line3 interrupt                      */
	0,                             /* 0x068 EXTI Line4 interrupt                      */
    0,                             /* 0x06C DMA1 Channel1 global interrupt            */
	0,                             /* 0x070 DMA1 Channel2 global interrupt            */
	0,                             /* 0x074 DMA1 Channel3 global interrupt            */
	(uint32_t *) dma1_channel4_interrupt, /* 0x078 DMA1 Channel4 global interrupt            */
	0,                             /* 0x07C DMA1 Channel5 global interrupt            */
	0,                             /* 0x080 DMA1 Channel6 global interrupt            */
	0,                             /* 0x084 DMA1 Channel7 global interrupt            */
	0, 							   /* 0x088  ADC1 and ADC2 global interrupt       */
};

int main(void)
{
	uint16_t dataA[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', '\n'};
	uint16_t dataB[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', '\n'};

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	// USART 1 CLK PA8
	// USART 1 TX PA9
	GPIOA->CRH |= GPIO_CRH_MODE9_0 // Maximum 10 MHz
		| GPIO_CRH_CNF9_0 // Alternate function
		| GPIO_CRH_CNF9_1; // Open-drain

	// USART 1 RX PA10

	// DMA
	DMA1_Channel4->CCR =
		DMA_CCR_MINC
		| DMA_CCR_DIR
		| DMA_CCR_TCIE
		| DMA_CCR_PSIZE_0 // 16 bits
		| DMA_CCR_MSIZE_0; // 16 bits

	// DMA Interrupt
	NVIC_SetPriority(DMA1_Channel4_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel4_IRQn);

	// USART
	USART1->CR1 = USART_CR1_TE;
	USART1->CR2 = USART_CR2_CLKEN;
	USART1->CR3 = USART_CR3_DMAT;
	USART1->BRR = get_uart_brr_value(115200);
	USART1->CR1 |= USART_CR1_UE;

	while(1)
	{
		uart_tx(dataA, 8);

		uart_tx(dataB, 8);
	}
}

void dma1_channel4_interrupt(void)
{
	if (DMA1->ISR & DMA_ISR_TCIF4) {
		DMA1->IFCR = DMA_IFCR_CTCIF4;
		DMA1_Channel4->CCR &= ~DMA_CCR_EN;
	}
}

uint32_t get_uart_brr_value(uint32_t baudrate)
{
	int SystemCoreClock = 8000000; // 8MHz
	
	uint16_t uartdiv = SystemCoreClock / baudrate;
	return ((uartdiv / 16) << USART_BRR_DIV_Mantissa_Pos) 
		| ((uartdiv % 16) << USART_BRR_DIV_Fraction_Pos);
}

void uart_tx(uint16_t *data, uint8_t len)
{
	DMA1_Channel4->CPAR = (uint32_t)&(USART1->DR);
	DMA1_Channel4->CMAR = (uint32_t)data;
	DMA1_Channel4->CNDTR = len;
	DMA1_Channel4->CCR |= DMA_CCR_EN;
}