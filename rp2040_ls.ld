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

    } > FLASH

    .sram_text :
    {
        . = ALIGN(4);
        _s_sram_text = .;    /* start address of .sram_text in SRAM */
        *(.sram_text*)
        . = ALIGN(4);
        _e_sram_text = .;                        /* end address of .sram_text in SRAM */
        _la_sram_text = LOADADDR(.sram_text);     /* load address of .sram_text in FLASH */

    }> SRAM AT> FLASH

    .data : {

        . = ALIGN(4);
        _sdata = .;     /* start address of .data in SRAM */
        *(.data*)
        . = ALIGN(4);
        _edata = .;                     /* end address of .data in SRAM */
        _la_data = LOADADDR(.data);     /* load address of .data in FLASH */

    } > SRAM AT> FLASH

    .bss  : {

        . = ALIGN(4);
        _sbss = .;      /* start address of .bss in SRAM */
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;      /* end address of .bss in SRAM */

    } > SRAM
}
