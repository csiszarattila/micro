It alternates HIGH/LOW state on GPIO Port C Pin 13. Why this pin? Most STM32 development boards have a led connected to this port.

To make this working first set GPIO Port C Pin 13 mode to output then write HIGH or LOW value in this pin.

### In order to enable a GPIO port as output:

- Must enable clock for the port in RCC registers

  GPIO Port C clock can be enabled in the RCC_APB2ENR register.

  See manual section 8.3.7 - APB2 peripheral clock enable register (RCC_APB2ENR).
  RCC_APB2ENR has an 0x18 offset to RCC.

  RCC (Reset and clock control) starts at 0x4002 1000 according to 3.3 Memory map Table 3, so:

  `RCC_APB2ENR = RCC + 0x018`

  GPIO C clock can be enabled by setting this address' 4th bit to high.

- Must change GPIOC pin 13 to output mode

  All GPIO port has 16 pin with each pin having 2 configuration and 2 mode bit. Therefore pin configuration needs 2 registers:

  Port configuration register low (GPIOx_CRL) for pins 0..7 with offset 0x00

  Port configuration register low (GPIOx_CRH) for pins 8..15 with offset 0x04

  GPIOC start at 0x4001 1000, see Memory map table at 3.3 Table 3. So:

  `GPIOC_CRH = GPIOC + 0x04`

  First set mode (bit 22,23) to '0b00': General purpose output push-pull.

  Then set speed (bit, 20, 21) to '0b10': Output mode, max speed 2 MHz.

  More info at 9.9.2 Port configuration register high (GPIOx_CRH) (x=A..G) section.

### Set the HIGH/LOW value on pin

There are number of registers to set the output value on GPIO port pins.

Note: manual refers HIGH state as SET and LOW state as RESET.

GPIOx_ODR - Section 9.2.4 Port output data register (x=A..G) (offset 0x0C)
  - Flipping bit 0..15 to 1 set the corresponding pin, so it became HIGH.
  - Flipping bit 0..15 to 0 set the corresponding pin, so it became LOW.

GPIOx_BSRR - Section 9.2.5 Port bit set/reset register (x=A..G) (offset 0x10)
  - Flipping bit 0..15 to 1 set the corresponding pin, so it became HIGH.
  - Flipping bit 16..31 to 1 reset the corresponding pin, so it became LOW.

GPIOx_BRR - Section 9.2.66 Port bit reset register (x=A..G) (offset 0x14):
  - Flipping bit 0..15 to 1 reset the corresponding pin, so it became LOW.

In the example we
 - set HIGH state by setting bit 13 on GPIOC_BSRR register to 1
 - set LOW state by setting bit 13 on GPIOC_BRR register to 1

In case of STM32 development boards the onboard leds are pulled high to 3.3VCC, so setting this pin to low turn the led on and setting high turn it off.
