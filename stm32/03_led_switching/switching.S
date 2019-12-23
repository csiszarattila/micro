.cpu cortex-m3
.thumb

.global start

@ Vector table
  .word _estack
  .word start

.equ RCC_BASE, 0x40021000
.equ GPIOA_BASE, 0x40010800
.equ GPIOC_BASE, 0x40011000

.type start, %function
start:
  // ENABLE GPIO A PORT & GPIO PORT C
  LDR r0, =(RCC_BASE + 0x18) // RCC_APB2ENR
  LDR r1, =0x14
  STR r1, [r0]

  // GPIO A PORT PIN 1 INPUT MODE
  LDR r0, =GPIOA_BASE
  LDR r1, =0x80
  STR r1, [r0]

  // GPIO C PORT PIN 13 OUTPUT
  LDR r0, =(GPIOC_BASE + 0x04)
  LDR r1, =0x00600000
  STR r1, [r0]

read_pin:
  LDR r0, =(GPIOA_BASE + 0x08) // GPIOA_IDR
  LDR r1, [r0]
  // Only value of PIN 1
  LDR r2, =0x2
  AND r1, r1, r2
  // It is HIGH (equal to 1) ?
  CMP r2, r1
  BNE light_off

light_on:
  LDR r0, =(GPIOC_BASE + 0x14) // GPIOC_BRR
  LDR r1, =(1 << 13)
  STR r1, [r0]
  b read_pin

light_off:
  LDR r0, =(GPIOC_BASE + 0x10) // GPIOC_BSRR
  LDR r1, =(1 << 13)
  STR r1, [r0]
  b read_pin
