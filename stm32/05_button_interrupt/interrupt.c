#define uint32_t int
#define uint32_t int
#define uint8_t char

extern int _estack;

int main(void);

void EXTI0_IRQ_handler();

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
	(void *)EXTI0_IRQ_handler,     /* 0x058 EXTI Line0 interrupt                      */
	0,                             /* 0x05C EXTI Line1 interrupt                      */
	0,                             /* 0x060 EXTI Line2 interrupt                      */
	0,                             /* 0x064 EXTI Line3 interrupt                      */
	0,                             /* 0x068 EXTI Line4 interrupt                      */
};

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

// EXTIx position in Vector table [see RM0008 10.1.2 Interrupt and exception vectors]
#define EXTI0_IRQn 6
#define EXTI1_IRQn 7

int main(void)
{
    // ENABLE GPIO PORT C PIN 13 OUTPUT MODE
    RCC->APB2ENR |= (1 << 4);
    GPIO_C->CRH = (0x00 << (((LED_PIN - 8) * 4) + 2));
    GPIO_C->CRH = (0x02 << (((LED_PIN - 8) * 4)));

    // ENABLE GPIO A PORT PIN 4 INPUT MODE
    RCC->APB2ENR |= (1 << 2);
    GPIO_A->CRL |= (1 << ((INPUT_PIN * 4) + 2));

    RCC->APB2ENR |= (1<<0);  // Enable AFIO CLOCK

	// Enable EXTI0 on PORT A0
	AFIO->EXTICR1 = 0x0000 << (INPUT_PIN * 4);
	
	// Enable EXTI0
    EXTI->IMR = (1 << EXTI0);
	// Falling Edge EXTI0
	EXTI->RTSR |= (1 << EXTI0);  // Enable Rising Edge Trigger for PA1
	EXTI->FTSR &= ~(1 << EXTI0);  // Disable Falling Edge Trigger for PA1

    NVIC_ISERx->ISER0 |= (1 << EXTI0_IRQn); // Enable IRQ - 
    // NVIC_IPRx->IPR0 = 0x01; // Set Priority

	// LED OFF
	GPIO_C->BSRR = (1 << 13);

    while (1) {
    }
}

void EXTI0_IRQ_handler(void) {
	int delay;

	GPIO_C->BRR = (1 << 13);

	delay = 1000000;
	while (delay) delay--;

	GPIO_C->BSRR = (1 << 13);

	EXTI->PR |= (1 << EXTI0);
}