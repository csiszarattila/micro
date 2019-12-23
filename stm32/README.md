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

#GNU Assembler Reference 
https://ftp.gnu.org/old-gnu/Manuals/gas-2.9.1/html_chapter/as_7.html

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