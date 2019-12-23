This is a follow up on the previous [02_led_blinking example](./../02_led_blinking/) by making the led switchable with a button.

The switch button connected to pin A1 (GPIO A PORT PIN 1) on STM32 development board. On the program this pin configured to INPUT MODE: when it reads HIGH then sets the C13 pin output to LOW (turn on led), when A1 reads LOW it sets the C13 pin to HIGH (turn off led).

Setting a GPIO pin into INPUT MODE is almost the same as setting into output mode, the following additional changes required to the previous example:

- Enable GPIO PORT A by setting RCC_APB2ENR register's 2nd bit to HIGH

- Enable GPIO PORT A pin 1 to INPUT mode by setting Pin 1 into Input mode in GPIOA_CRL register.

  `GPIOC_CRL = GPIOA + 0x00`

  First set mode (bit 4,5) to '0b00', 00: Input mode (reset state)

  Then set speed (bit 6, 7) to '0b10': Input with pull-up / pull-down