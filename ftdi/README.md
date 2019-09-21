# Building on MacOS

In order to build these examples first you need to install libftdi packages. The easiest way is using homebrew:

```
brew install libftdi
```

Then running compile with make

```
make
```

# Examples

## read_eeprom.c

Read and prints FTDI chip's EEPROM content

## led_blinking.c

Turn on/off a led (blink) in 1s intervals (1Hz)
The corresponding led pin can be set using LED_PIN constant, with the following values:

Databit | Pin Number | Pin Name | Reference
--------|------------|----------|----------
D0 | 1  | TXD | 0x01 
D1 | 5  | RXD | 0x02
D2 | 3  | RTS | 0x04
D3 | 11 | CTS | 0x08
D4 | 2  | DTR | 0x10
D5 | 9  | DSR | 0x20
D6 | 10 | DCD | 0x40
D7 | 6  | RI  | 0x80

Source: [AN_373 Bit-Bang Modes for the FT-X Series](https://www.ftdichip.com/Support/Documents/AppNotes/AN_373%20Bit-Bang%20Modes%20for%20the%20FT-X%20Series.p)
see Table 2.1 Asynchronous Bit-Bang Mode I/O Configurations and [FT232R USB UART IC Datasheet](https://www.ftdichip.com/Support/Documents/DataSheets/ICs/DS_FT232R.pdf) Figure 3.1 SSOP Package Pin Out and Schematic Symbol for Pin numbering.
