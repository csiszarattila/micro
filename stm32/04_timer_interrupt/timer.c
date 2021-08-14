#define uint32_t int
#define uint32_t int
#define uint8_t char

extern int _estack;

int main(void);

void TIM2_IRQ_Handler();
void delay();

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
	0,                             /* 0x078 DMA1 Channel4 global interrupt            */
	0,                             /* 0x07C DMA1 Channel5 global interrupt            */
	0,                             /* 0x080 DMA1 Channel6 global interrupt            */
	0,                             /* 0x084 DMA1 Channel7 global interrupt            */
	0,                             /* 0x088 ADC1 and ADC2 global interrupt            */
    0,                             /* 0x08C CAN1 TX interrupts                        */
    0,                             /* 0x090 CAN1 RX0 interrupts                       */
	0,                             /* 0x094 CAN1 RX1 interrupts                       */
    0,                             /* 0x098 CAN1 SCE interrupt                        */
    0,                             /* 0x09C EXTI Line[9:5] interrupts                 */
    0,                             /* 0x0A0 TIM1 Break interrupt                      */
    0,                             /* 0x0A4 TIM1 Update interrupt                     */
    0,                             /* 0x0A8 TIM1 Trigger and Commutation interrupts   */
    0,                             /* 0x0AC TIM1 Capture Compare interrupt            */
    (uint32_t *) TIM2_IRQ_Handler, /* 0x0B0 TIM2 global interrupt                     */
    0,                             /* 0x0B4 TIM3 global interrupt                     */
    0,                             /* 0x0B8 TIM4 global interrupt                     */
};

#define TIM2 ((TIMx_type *)    0x40000000)
#define RCC ((RCC_type *)       0x40021000)
#define GPIO_A ((GPIO_type *) 	0x40010800)
#define GPIO_C ((GPIO_type *)   0x40011000)
#define AFIO ((AFIO_type *)		0x40010000)
#define EXTI ((EXTI_type *)     0x40010400)
#define NVIC_ISERx ((NVIC_ISER_type *)     0xE000E100)
#define NVIC_ICERx ((NVIC_ICER_type *)     0xE000E100 + 0x080)
#define NVIC_ISPRx ((NVIC_ISPR_type *)     0xE000E100 + 0x100)
#define NVIC_IPRx  ((NVIC_IPR_type *)      0xE000E100 + 0x300)

typedef struct
{
	uint32_t CR;       /* RCC clock control register,                Address offset: 0x00 */
	uint32_t CFGR;     /* RCC clock configuration register,          Address offset: 0x04 */
	uint32_t CIR;      /* RCC clock interrupt register,              Address offset: 0x08 */
	uint32_t APB2RSTR; /* RCC APB2 peripheral reset register,        Address offset: 0x0C */
	uint32_t APB1RSTR; /* RCC APB1 peripheral reset register,        Address offset: 0x10 */
	uint32_t AHBENR;   /* RCC AHB peripheral clock enable register,  Address offset: 0x14 */
	uint32_t APB2ENR;  /* RCC APB2 peripheral clock enable register, Address offset: 0x18 */
	uint32_t APB1ENR;  /* RCC APB1 peripheral clock enable register, Address offset: 0x1C */
	uint32_t BDCR;     /* RCC backup domain control register,        Address offset: 0x20 */
	uint32_t CSR;      /* RCC control/status register,               Address offset: 0x24 */
	uint32_t AHBRSTR;  /* RCC AHB peripheral clock reset register,   Address offset: 0x28 */
	uint32_t CFGR2;    /* RCC clock configuration register 2,        Address offset: 0x2C */
} RCC_type;

typedef struct {
    uint32_t CRL;      /* GPIO port configuration register low,      Address offset: 0x00 */
	uint32_t CRH;      /* GPIO port configuration register high,     Address offset: 0x04 */
	uint32_t IDR;      /* GPIO port input data register,             Address offset: 0x08 */
	uint32_t ODR;      /* GPIO port output data register,            Address offset: 0x0C */
	uint32_t BSRR;     /* GPIO port bit set/reset register,          Address offset: 0x10 */
	uint32_t BRR;      /* GPIO port bit reset register,              Address offset: 0x14 */
	uint32_t LCKR;     /* GPIO port configuration lock register,     Address offset: 0x18 */
} GPIO_type;

typedef struct {
    uint32_t CR1;      /* TIMx control register 1,                   Address offset: 0x00 */
	uint32_t CR2;      /* TIMx control register 2,                   Address offset: 0x04 */
	uint32_t SMCR;     /* TIMx slave mode control register,          Address offset: 0x08 */
	uint32_t DIER;     /* TIMx DMA/Interrupt enable register,        Address offset: 0x0C */
	uint32_t SR;       /* TIMx status register,                      Address offset: 0x10 */
	uint32_t EGR;      /* TIMx event generation register,            Address offset: 0x14 */
	uint32_t CCMR1;    /* TIMx capture/compare mode register 1,      Address offset: 0x18 */
	uint32_t CCMR2;    /* TIMx capture/compare mode register 2,      Address offset: 0x1C */
	uint32_t CCER;     /* TIMx capture/compare enable register,      Address offset: 0x20 */
	uint32_t CNT;      /* TIMx_CNT,                                  Address offset: 0x24 */
	uint32_t PSC;      /* TIMx_PSC,                                  Address offset: 0x28 */
	uint32_t ARR;      /* TIMx auto-reload register,                 Address offset: 0x2C */
	uint32_t RESERVED1;
    uint32_t CCR1;     /* TIMx capture/compare register 1,           Address offset: 0x34 */
	uint32_t CCR2;     /* TIMx capture/compare register 2,           Address offset: 0x38 */
	uint32_t CCR3;     /* TIMx capture/compare register 3,           Address offset: 0x3C */
	uint32_t CCR4;     /* TIMx capture/compare register 4,           Address offset: 0x40 */
    uint32_t RESERVED2;
    uint32_t DCR;      /* TIMx DMA control register,                 Address offset: 0x48 */
	uint32_t DMAR;     /* TIMx DMA address for full transfer,        Address offset: 0x4C */
} TIMx_type;

typedef struct {
    uint32_t IMR;      /* Interrupt mask register,                   Address offset: 0x00 */
	uint32_t EMR;      /* Event mask register,                       Address offset: 0x04 */
	uint32_t RTSR;     /* Rising trigger selection register,         Address offset: 0x08 */
	uint32_t FTSR;     /* Falling trigger selection register,        Address offset: 0x0C */
	uint32_t SWIER;    /* Software interrupt event register,         Address offset: 0x10 */
	uint32_t PR;       /* Pending register,                          Address offset: 0x14 */
} EXTI_type;

typedef struct {
    uint32_t EVCR;    /* Event control register,           				Address offset: 0x00 */
	uint32_t MAPR;    /* AF remap and debug I/O configuration register,	Address offset: 0x04 */
	uint32_t EXTICR1; /* External interrupt configuration register 1,	Address offset: 0x08 */
	uint32_t EXTICR2; /* External interrupt configuration register 2,	Address offset: 0x0C */
	uint32_t EXTICR3; /* External interrupt configuration register 3,	Address offset: 0x10 */
	uint32_t EXTICR4; /* External interrupt configuration register 4,	Address offset: 0x14 */
} AFIO_type;

typedef struct {
    uint32_t ISER0;    /* Interrupt set-enable registers,           Address offset: 0x00 */
	uint32_t ISER1;    /* Interrupt set-enable registers,           Address offset: 0x04 */
	uint32_t ISER2;    /* Interrupt set-enable registers,           Address offset: 0x08 */
} NVIC_ISER_type;

typedef struct {
    uint32_t ICER0;    /* Interrupt clear-enable registers,         Address offset: 0x00 */
	uint32_t ICER1;    /* Interrupt clear-enable registers,         Address offset: 0x04 */
	uint32_t ICER2;    /* Interrupt clear-enable registers,         Address offset: 0x08 */
} NVIC_ICER_type;

typedef struct {
	uint32_t ISPR0;    /* Interrupt set-pending registers,          Address offset: 0x00 */
	uint32_t ISPR1;    /* Interrupt set-pending registers,          Address offset: 0x04 */
	uint32_t ISPR2;    /* Interrupt set-pending registers,          Address offset: 0x08 */
} NVIC_ISPR_type;

typedef struct {
	uint8_t IPR0;    /* Interrupt priority registers,             Address offset: 0x00 */
	uint8_t IPR1;    /* Interrupt priority registers,             Address offset: 0x01 */
	uint8_t IPR2;    /* Interrupt priority registers,             Address offset: 0x02 */
    uint8_t IPR4;    /* Interrupt priority registers,             Address offset: 0x03 */
	// uint8_t IPR5;    /* Interrupt priority registers,             Address offset: 0x04 */
	// uint8_t IPR6;    /* Interrupt priority registers,             Address offset: 0x14 */
} NVIC_IPR_type;

#define LED_PIN 13 // ONBOARD LED
#define INPUT_PIN 0

#define EXTI0 0
#define EXTI1 1

// TIM2 position in Vector table [see RM0008 10.1.2 Interrupt and exception vectors]
#define TIM2_IRQn 28

#define RCC_APB1ENR_TIM2EN (1<<0)

#define RCC_APB2ENR_GPIOCEN (1 << 4)

#define TIMx_CR1_CEN (1<< 0) // Counter enable
#define TIMx_DIER_UIE (1<< 0) // Update interrupt enabled
#define TIMx_SR_UIF (1<< 0) // Update interrupt flag

#define SYSCLK 8000000 //8MHz

int ledOn;

int main(void)
{
	ledOn = 0;
    // ENABLE GPIO PORT C PIN 13 OUTPUT MODE
    RCC->APB2ENR |= RCC_APB2ENR_GPIOCEN;
    GPIO_C->CRH = (0x00 << (((LED_PIN - 8) * 4) + 2));
    GPIO_C->CRH = (0x02 << (((LED_PIN - 8) * 4)));

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
	
    NVIC_ISERx->ISER0 |= (1 << TIM2_IRQn);
    // NVIC_IPRx->IPR0 = 0x01; // Set Priority

	TIM2->SR = 0;
	TIM2->PSC = (SYSCLK / 8000) -1;
	TIM2->ARR = 10000;
	TIM2->DIER |= TIMx_DIER_UIE;
	TIM2->CR1 |= TIMx_CR1_CEN;

	while (1)
	{
		if (ledOn) { 
			GPIO_C->BRR = (1 << 13);
		} else {
			GPIO_C->BSRR = (1 << 13);
		}
	}
}

void TIM2_IRQ_Handler(void) {
	ledOn = ledOn == 1 ? 0 : 1;
	
	TIM2->SR &= ~(TIMx_SR_UIF);
}