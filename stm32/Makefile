.PHONY: 01_minimal_loop 02_led_blinking 03_led_switching

01_minimal_loop:
		arm-none-eabi-as 01_minimal_loop/loop.S -g -o 01_minimal_loop.o
		arm-none-eabi-ld 01_minimal_loop.o -Tstm32f103.ld -o 01_minimal_loop.elf

02_led_blinking:
		arm-none-eabi-as 02_led_blinking/blinking.S -g -o 02_led_blinking.o
		arm-none-eabi-ld 02_led_blinking.o -Tstm32f103.ld -o 02_led_blinking.elf

03_led_switching:
		arm-none-eabi-as 03_led_switching/switching.S -g -o 03_led_switching.o
		arm-none-eabi-ld 03_led_switching.o -Tstm32f103.ld -o 03_led_switching.elf

.PHONY: clean
clean:
		rm -f *.o
		rm -f *.elf
