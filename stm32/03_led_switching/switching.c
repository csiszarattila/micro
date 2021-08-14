#define uint32_t int

extern int _estack;

int main(void);

uint32_t (* const vector_table[])
__attribute__ ((section(".vector_table"))) = {
	(uint32_t *) &_estack,         /* 0x000 Stack Pointer                   */
	(uint32_t *) main,              /* 0x004 Reset                           */
	0,                              /* 0x008 Non maskable interrupt          */
};

#define RCC ((RCC_type *) 0x40021000)
#define GPIO_A ((GPIO_type *) 0x40010800)
#define GPIO_C ((GPIO_type *) 0x40011000)

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

#define INPUT_PIN 4 // A5
#define LED_PIN 13 // ONBOARD LED

int main(void)
{
    // ENABLE GPIO A PORT 
    RCC->APB2ENR |= (1 << 2);
    // ENABLE GPIO PORT C
    RCC->APB2ENR |= (1 << 4);

    // GPIO A PORT PIN 3 INPUT MODE
    GPIO_A->CRL |= (1 << ((INPUT_PIN * 4) + 2));

    // GPIO C PORT PIN 13 OUTPUT MODE
    GPIO_C->CRH = (0x00 << (((LED_PIN - 8) * 4) + 2));
    GPIO_C->CRH = (0x02 << (((LED_PIN - 8) * 4)));

    while(1) {
        uint32_t input = GPIO_A->IDR;
        if (input & (1 << (INPUT_PIN + 1))) {
            GPIO_C->BRR = (1 << 13);
        } else {
            GPIO_C->BSRR = (1 << 13);
        }
    }
}