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
rm-none-eabi-gdb {#example#}.elf
```

on gdb console type:

```
(gdb) target extended-remote :4242
(gdb) load
```

[Great instruction video about using gdb debugger](https://www.youtube.com/watch?v=2kLK_sdvC3Q)

# Examples

## 01_minimal_loop.S

A minimal assembly program which run an endless loop, make by this article:
https://vivonomicon.com/2018/04/02/bare-metal-stm32-programming-part-1-hello-arm/

Helps to understand basic linking, flashing, and debugging a program on an stm32 chip.
