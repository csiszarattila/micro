ENTRY(main)

/* End of RAM/Start of stack */
/* (20KB SRAM) */
_estack = 0x20005000;

MEMORY
{
    FLASH ( rx )      : ORIGIN = 0x08000000, LENGTH = 64K
    RAM ( rxw )       : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text :
    {
            KEEP(*(.vector_table))  /* Vector table */
            *(.text*)          /* Program code */
            *(.rodata*)        /* Read only data */
            . = ALIGN(4);
    } >FLASH

	.data :
	{
		*(.data*)      /* Read-write initialized data */
		. = ALIGN(4);
	} >RAM
}