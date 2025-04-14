#include <stdint.h>
#include "startup/vector_table.h"

/*
 *  Universal startup file
 *  Martin Kopka 2022
*/

//---- LINKER SCRIPT SYMBOLS -------------------------------------------------------------------------------------------------------------------------------------

extern uint32_t _la_sram_text;  // start address of .sram_text segment in FLASH
extern uint32_t _s_sram_text;   // start address of .sram_text segment in SRAM
extern uint32_t _e_sram_text;   //   end address of .sram_text segment in SRAM
extern uint32_t _la_data;       // start address of .data segment in FLASH (load address)
extern uint32_t _sdata;         // start address of .data segment in SRAM
extern uint32_t _edata;         //   end address of .data segment in SRAM
extern uint32_t _sbss;          // start address of .bss segment in SRAM 
extern uint32_t _ebss;          //   end address of .bss segment in SRAM

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

extern int main();

// entry point
void Reset_Handler() {

    // copy .sram_text segment from FLASH to SRAM
    uint8_t *p_src = (uint8_t*)&_la_sram_text;

    for (uint8_t *p_dst = (uint8_t*)&_s_sram_text; p_dst < (uint8_t*)&_e_sram_text; p_dst++) {

        *p_dst = *p_src++;
    }
    
    // copy the .data segment from FLASH to SRAM
    p_src = (uint8_t*)&_la_data;

    for (uint8_t *p_dst = (uint8_t*)&_sdata; p_dst < (uint8_t*)&_edata; p_dst++) {

        *p_dst = *p_src++;
    }

    // initialize the .bss segment in SRAM to 0
    for (uint32_t *p_dst = &_sbss; p_dst < &_ebss; p_dst++) {

        *p_dst = 0x00000000;
    }

    main();     // branch to main

    while (1);
}

//---- IRQ HANDLERS ----------------------------------------------------------------------------------------------------------------------------------------------

// empty handler for unhandled exeptions
void Default_Handler() {

    return;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
