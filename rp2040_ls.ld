MEMORY {

    FLASH(rx) : ORIGIN = 0x10000000, LENGTH = 2048k
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 264k
}

ENTRY(Reset_Handler)

SECTIONS {

    .text : {

        KEEP(*(.boot2))             /* 256 bytes of stage 2 bootrom */
        KEEP(*(.vector_table))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);

        _la_data = .;   /* load address of .data in FLASH */
    } > FLASH

    .data : {

        . = ALIGN(4);
        _sdata = .;     /* start address of .data in SRAM */
        *(.data*)
        . = ALIGN(4);
        _edata = .;     /* end address of .data in SRAM */

    } > SRAM AT> FLASH

    .bss  : {

        . = ALIGN(4);
        _sbss = .;      /* start address of .bss in SRAM */
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;      /* end address of .bss in SRAM */

    } > SRAM
}
