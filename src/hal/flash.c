#include "hal/flash.h"
#include "hal/bootrom.h"

//---- CONSTANTS -------------------------------------------------------------------------------------------------------------------------------------------------

#define FLASH_BLOCK_ERASE_CMD 0xd8

#define BOOT2_SIZE_WORDS 64

//---- INTERNAL DATA ---------------------------------------------------------------------------------------------------------------------------------------------

static uint32_t boot2_ram_copy[BOOT2_SIZE_WORDS];
static bool boot2_ram_copy_valid = false;

//---- INTERNAL FUNCTIONS ----------------------------------------------------------------------------------------------------------------------------------------

static void SRAM_FUNC flash_init_boot2_ram_copy(void) {

    if (boot2_ram_copy_valid) return;

    const volatile uint32_t *copy_from = (uint32_t *)XIP_BASE;

    for (int i = 0; i < BOOT2_SIZE_WORDS; ++i) boot2_ram_copy[i] = copy_from[i];

    asm("" : : : "memory");
    boot2_ram_copy_valid = true;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

void flash_enable_xip_via_boot2(void) {

    ((void (*)(void))((intptr_t)boot2_ram_copy+1))();
}

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// flash_offset must be aligned to 4096 sector and size must be a multiple of 4096
void SRAM_FUNC flash_range_erase(uint32_t flash_offset, uint32_t count) {

    __disable_irq();

    rom_connect_internal_flash_fn connect_internal_flash_func = (rom_connect_internal_flash_fn)rom_func_lookup(ROM_FUNC_CONNECT_INTERNAL_FLASH);
    rom_flash_exit_xip_fn flash_exit_xip_func = (rom_flash_exit_xip_fn)rom_func_lookup(ROM_FUNC_FLASH_EXIT_XIP);
    rom_flash_range_erase_fn flash_range_erase_func = (rom_flash_range_erase_fn)rom_func_lookup(ROM_FUNC_FLASH_RANGE_ERASE);
    rom_flash_flush_cache_fn flash_flush_cache_func = (rom_flash_flush_cache_fn)rom_func_lookup(ROM_FUNC_FLASH_FLUSH_CACHE);

    flash_init_boot2_ram_copy();

    // No flash accesses after this point
    // prevent compiler memory access reordering
    asm("" : : : "memory");     

    connect_internal_flash_func();
    flash_exit_xip_func();
    flash_range_erase_func(flash_offset, count, FLASH_BLOCK_SIZE, FLASH_BLOCK_ERASE_CMD);
    flash_flush_cache_func();
    flash_enable_xip_via_boot2();

    __enable_irq();
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// flash_offset must be aligned to 256 byte page and count must be a multiple of 256
void SRAM_FUNC flash_range_program(uint32_t flash_offset, const uint8_t *data, uint32_t count) {

    __disable_irq();

    rom_connect_internal_flash_fn connect_internal_flash_func = (rom_connect_internal_flash_fn)rom_func_lookup(ROM_FUNC_CONNECT_INTERNAL_FLASH);
    rom_flash_exit_xip_fn flash_exit_xip_func = (rom_flash_exit_xip_fn)rom_func_lookup(ROM_FUNC_FLASH_EXIT_XIP);
    rom_flash_range_program_fn flash_range_program_func = (rom_flash_range_program_fn)rom_func_lookup(ROM_FUNC_FLASH_RANGE_PROGRAM);
    rom_flash_flush_cache_fn flash_flush_cache_func = (rom_flash_flush_cache_fn)rom_func_lookup(ROM_FUNC_FLASH_FLUSH_CACHE);

    flash_init_boot2_ram_copy();

    // No flash accesses after this point
    // prevent compiler memory access reordering
    asm("" : : : "memory");

    connect_internal_flash_func();
    flash_exit_xip_func();
    flash_range_program_func(flash_offset, data, count);
    flash_flush_cache_func();
    flash_enable_xip_via_boot2();

    __enable_irq();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
