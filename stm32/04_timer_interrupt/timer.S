.cpu cortex-m3
.syntax unified
.thumb

.global start

@ Vector table
  .word _estack
  .word start
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word TIM2_IRQHandler // position 28


.equ RCC_BASE, 0x40021000
.equ TIM2_BASE, 0x40000000
.equ NVIC_BASE, 0xE000E100
.equ GPIOC_BASE, 0x40011000
.equ LED_DELAY, 1000000

.type start, %function
start:

  @ Enable clock for GPIO Port C in RCC registers
  LDR r0, = (RCC_BASE + 0x18) // RCC_APB2ENR
  LDR r1, [r0]
  ORR r1, r1, (1 << 4) // GPIO Port C
  STR r1, [r0]

  @ Enable GPIOC pin 13 as output
  LDR r0, = (GPIOC_BASE + 0x04) // GPIOC_CRH
  ORR r1, r1, (0x00 << (((13 - 8) * 4) + 2))
  STR r1, [r0]

  @ Enable GPIOC pin 13 as output
  LDR r0, = (GPIOC_BASE + 0x04) // GPIOC_CRH
  ORR r1, r1, (0x02 << (((13 - 8) * 4)))
  STR r1, [r0]

  LDR r0, = (GPIOC_BASE + 0x10) //GPIOC_BSRR
  LDR r1, =(1 << 13)
  STR r1, [r0]

  // ENABLE TIM2 INTERRUPT IN NVIC_ISER0
  LDR r0, =NVIC_BASE // NVIC_ISER0
  ORR r1, r1, (1<<28) // TIM2 position in Vector table [see RM0008 10.1.2 Interrupt and exception vectors]
  STR r1, [r0]

  // ENABLE TIM2 TIMER
  LDR r0, =(RCC_BASE + 0x1C) // RCC_APB1ENR
  ORR r1, r1, 0x01
  STR r1, [r0]

  // OFF TIM2 TIMER
  LDR r0, =TIM2_BASE
  LDR r1, =0x0
  STR r1, [r0]

  // SET TIM2 PRESCALER
  LDR r0, =(TIM2_BASE + 0x28) // TIM2_PSC
  LDR r1, =#7999
  STR r1, [r0]

  // SET TIM2 INTERRUPT TIME AT
  LDR r0, =(TIM2_BASE + 0x2C) // TIM2_ARR
  LDR r1, =#100000
  STR r1, [r0]

  // UPDATE TIM2 TIMER SETTINGS
  LDR r0, =(TIM2_BASE + 0x14) // TIM2_EGR
  LDR r1, =0x01
  STR r1, [r0]

  // ENABLE TIM2 IRQ
  LDR r0, =(TIM2_BASE + 0x0C) // TIM2_DIER
  LDR r1, =0x01 // Bit 0 UIE: Update interrupt enable
  STR r1, [r0]

  // RESET UIF
  LDR r0, =(TIM2_BASE + 0x10) // TIM2_SR
  LDR r1, =0x01 // Bit 0 UIF: Update interrupt flag
  STR r1, [r0]

  // START TIM2 TIMER
  LDR r0, =TIM2_BASE
  LDR r1, =0x01
  STR r1, [r0]

loop:
  MOV r0, #1
  ADD r0, #1
  b loop

.thumb_func
TIM2_IRQHandler:
  toogle_led:

    LDR r0, = (GPIOC_BASE + 0x10) //GPIOC_BSRR
    LDR r1, =(1 << 13)
    STR r1, [r0]

    LDR r2, = LED_DELAY
    delay1:
      SUBS r2, 1
      BNE delay1

    LDR r0, = (GPIOC_BASE + 0x14) //GPIOC_BRR
    LDR r1, =(1 << 13)
    STR r1, [r0]

    LDR r2, = LED_DELAY
    delay2:
      SUBS r2, 1
      BNE delay2

    b toogle_led
