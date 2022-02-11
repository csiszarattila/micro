#define uint32_t int
#define uint16_t unsigned short
#define uint8_t char

extern int _estack;

int main(void);

void ADC1_EOC_IRQ_handler();

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
	(uint32_t *) ADC1_EOC_IRQ_handler, /* 0x088  ADC1 and ADC2 global interrupt       */
};

#define RCC ((RCC_type *)       0x40021000)

#define GPIO_A ((GPIO_type *) 	0x40010800)

#define ADC1 ((ADC_type *) 		0x40012400)

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

typedef struct
{
	uint32_t SR;        /* Address offset: 0x00 */
	uint32_t CR1;       /* Address offset: 0x04 */
	uint32_t CR2;       /* Address offset: 0x08 */
	uint32_t SMPR1;     /* Address offset: 0x0C */
	uint32_t SMPR2;     /* Address offset: 0x10 */
	uint32_t JOFR1;     /* Address offset: 0x14 */
	uint32_t JOFR2;     /* Address offset: 0x18 */
	uint32_t JOFR3;     /* Address offset: 0x1C */
	uint32_t JOFR4;     /* Address offset: 0x20 */
	uint32_t HTR;       /* Address offset: 0x24 */
	uint32_t LTR;       /* Address offset: 0x28 */
	uint32_t SQR1;      /* Address offset: 0x2C */
	uint32_t SQR2;      /* Address offset: 0x30 */
	uint32_t SQR3;      /* Address offset: 0x34 */
	uint32_t JSQR;      /* Address offset: 0x38 */
	uint32_t JDR1;      /* Address offset: 0x3C */
	uint32_t JDR2;      /* Address offset: 0x40 */
	uint32_t JDR3;      /* Address offset: 0x44 */
	uint32_t JDR4;      /* Address offset: 0x48 */
	uint32_t DR;        /* Address offset: 0x4C */
} ADC_type;

void ADC1_EOC_IRQ_handler()
{
    
}

#define RCC_APB2ENR_ADC1EN (1 << 9)
#define RCC_APB2ENR_GPIOAEN (1 << 2)
#define RCC_APB2ENR_AFIOAEN (1 << 0)

#define GPIO_MODE_INPUT 0x00
#define GPIO_INPUT_ANALOG 0x00

#define ADC_ADON_ON (1 << 0) // A/D Converter ON
#define ADC_SWSTART (1 << 22)
#define ADC_CAL (1 << 2) // A/D Calibration
#define ADC_EOC (1 << 1) // ADC End of Conversion
#define ADC_EXTSEL_SWSTART (7 << 17) // Select SWSTART as trigger
#define ADC_EXTTRIG (1 << 20) // Enable External trigger
#define ADC_CONT (1 << 1) // Enable Continuous conversion

int main(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_GPIOAEN | RCC_APB2ENR_AFIOAEN;

    // GPIO Pin A port 0 analog input
    GPIO_A->CRL = GPIO_MODE_INPUT | GPIO_INPUT_ANALOG;

	ADC1->SQR1 = 0x00000000;
	ADC1->SQR3 = (0 << 0);

	ADC1->CR2 |= (7 << 17);  // Select SWSTART as trigger
	ADC1->CR2 |= (1 << 20);

	ADC1->CR2 |= ADC_EXTTRIG | ADC_EXTSEL_SWSTART | ADC_CONT;
	
	// Power On ADC
	ADC1->CR2 |= ADC_ADON_ON;

	// Wait for power ON
	for (int i = 0; i < 100; i++) {
		asm("NOP");
	}
	// Calibrate
	ADC1->CR2 |= ADC_CAL;
	while(ADC1->CR2 & ADC_CAL) {};

	// Start conversion
	ADC1->CR2 |= ADC_SWSTART;
	
    // End of Conversion
    while (! (ADC1->SR & ADC_EOC)) {};

  	uint16_t adc_val = ADC1->DR;

    while (1) {
    }
}