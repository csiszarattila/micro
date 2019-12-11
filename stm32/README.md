# Requirements on MacOS

In order to build these examples first you need to install the arm toolchain packages. The easiest way is using homebrew:

```
brew tap osx-cross/arm
brew install arm-gcc-bin
```

For flashing a program to a STM32 chip, install [stlink](https://github.com/texane/stlink).
Note: the brew package version is stable, but an old one which fails to recognise even genuine stlink v2 programmers. Installing the latest version from source through homebrew also fails with cmake errors. So [compile it manually](https://github.com/texane/stlink/blob/master/doc/compiling.md) from the source:

```
git clone https://github.com/texane/stlink.git
make release
cd build/Release; sudo make install
```

# STM32 Reference manual

https://www.st.com/content/ccc/resource/technical/document/reference_manual/59/b9/ba/7f/11/af/43/d5/CD00171190.pdf/files/CD00171190.pdf/jcr:content/translations/en.CD00171190.pdf

# Compiling and running examples

First compile it with make command:

```
make {#example#}
```

Then start the st-util program:

```
st-util
```

Start gdb debugger

```
arm-none-eabi-gdb {#example#}.elf
```

on gdb console type:

```
(gdb) target extended-remote :4242
(gdb) load
```

[Great instruction video about using gdb debugger](https://www.youtube.com/watch?v=2kLK_sdvC3Q)

# Examples

## 01_minimal_loop.S

A minimal assembly program which run an endless loop, created according to this article:
https://vivonomicon.com/2018/04/02/bare-metal-stm32-programming-part-1-hello-arm/

It helps to understand basic linking, flashing, and debugging a program on an stm32 chip.

## 02_led_blinking.S

It alternates HIGH/LOW state on GPIO PortC Pin 13. Why this pin? Most STM32 development boards have a soldered led on this port.

In order to enable a GPIO port as output:

- Must enable clock for the port in RCC registers

  GPIO Port C in RCC_APB2ENR register.
  See manual section 8.3.7 (APB2 peripheral clock enable register (RCC_APB2ENR). RCC_APB2ENR has an offset to RCC at 0x18. RCC (Reset and clock control) starts at 0x4002 1000 according to 3.3 Memory map Table 3.

  `RCC_APB2ENR = RCC + 0x018`

  GPIO C clock at Bit4.

- Must set GPIOC pin 13 as output mode
  All GPIO port has 16 pin with 2 configuration bits and 2 mode bit. So configuration has 2 registers.

  Port configuration register low (GPIOx_CRL) for pins 0..7 with offset 0x00

  Port configuration register low (GPIOx_CRH) for pins 8..15 with offset 0x04

  GPIOC start at 0x4001 1000, see Memory map table at 3.3 Table 3. So:

  `GPIOC_CRH = GPIOC + 0x04`

  Set mode (bit 22,23) to 00: General purpose output push-pull.

  Set speed to 10: Output mode, max speed 2 MHz with bit 20 and 21.

  More info at 9.9.2 Port configuration register high (GPIOx_CRH) (x=A..G) section.

Set the HIGH/LOW state on pin
There are number of registers to set the output value on GPIO port pins.

Note: manual refers HIGH state as set and LOW state to reset the pin.

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
