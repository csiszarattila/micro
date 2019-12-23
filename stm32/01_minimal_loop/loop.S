// https://vivonomicon.com/2018/04/02/bare-metal-stm32-programming-part-1-hello-arm/

// These instructions define attributes of our chip and
// the assembly language we'll use:
.syntax unified
.cpu cortex-m3
.thumb

// Global memory locations.
.global vtable
.global reset_handler

/*
 * The actual vector table.
 * Only the size of RAM and 'reset' handler are
 * included, for simplicity.
 */
.type vtable, %object
vtable:
    .word _estack
    .word reset_handler
.size vtable, .-vtable

/*
 * The Reset handler. Called on reset.
 */
.type start, %function
reset_handler:
  // Set the stack pointer to the end of the stack.
  // The '_estack' value is defined in our linker script.
  LDR  r0, =_estack
  MOV  sp, r0

  // Set some dummy values. When we see these values
  // in our debugger, we'll know that our program
  // is loaded on the chip and working.
  LDR  r7, =0xDEADBEEF
  MOVS r0, #0
  main_loop:
    ADDS r0, r0, 1
    B main_loop
.size reset_handler, .-reset_handler
