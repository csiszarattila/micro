.cpu cortex-m3
.thumb
.syntax unified

.global start

@ Vector table
  .word _estack
  .word start

.equ RCC_BASE, 0x40021000
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
