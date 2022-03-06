.PHONY: 01_minimal_loop 02_led_blinking 02_led_blinking_c 03_led_switching 03_led_switching_c 04_timer_interrupt 05_button_interrupt 06_adc 07_uart

01_minimal_loop:
		arm-none-eabi-as 01_minimal_loop/loop.S -g -o 01_minimal_loop.o
		arm-none-eabi-ld 01_minimal_loop.o -Tstm32f103.ld -o 01_minimal_loop.elf

02_led_blinking:
		arm-none-eabi-as 02_led_blinking/blinking.S -g -o 02_led_blinking.o
		arm-none-eabi-ld 02_led_blinking.o -Tstm32f103.ld -o 02_led_blinking.elf

02_led_blinking_c:
		arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Wall -nostdlib -g3 -O0 -T./stm32f103.ld 02_led_blinking/blinking.c -o 02_led_blinking.elf

03_led_switching:
		arm-none-eabi-as 03_led_switching/switching.S -g -o 03_led_switching.o
		arm-none-eabi-ld 03_led_switching.o -Tstm32f103.ld -o 03_led_switching.elf

03_led_switching_c:
		arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Wall -nostdlib -g3 -O0 -T./stm32f103.ld 03_led_switching/switching.c -o 03_led_switching.elf

04_timer_interrupt:
		arm-none-eabi-as 04_timer_interrupt/timer.S -g -o 04_timer_interrupt.o
		arm-none-eabi-ld 04_timer_interrupt.o -Tstm32f103.ld -o 04_timer_interrupt.elf

04_timer_interrupt_c:
		arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Wall -nostdlib -g3 -O0 -T./stm32f103.ld 04_timer_interrupt/timer.c -o 04_timer_interrupt.elf

05_button_interrupt_c:
		arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Wall -nostdlib -g3 -O0 -T./stm32f103.ld 05_button_interrupt/interrupt.c -o 05_button_interrupt.elf

06_adc:
		arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Wall -nostdlib -g3 -O0 -T./stm32f103.ld 06_adc/adc.c -o 06_adc.elf

07_uart:
		arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Wall -nostdlib -g3 -O0 -T./stm32f103.ld 07_uart/uart.c -o 07_uart.elf

.PHONY: clean
clean:
		rm -f *.o
		rm -f *.elf
