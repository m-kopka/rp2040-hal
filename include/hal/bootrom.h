#ifndef _HAL_BOOTROM_H_
#define _HAL_BOOTROM_H_

/*
 *  RP2040 BOOTROM LL Driver
 *  Martin Kopka 2025
*/

#include "rp2040.h"

//---- CONSTANTS -------------------------------------------------------------------------------------------------------------------------------------------------

#define BOOTROM_MAGIC_OFFSET        0x10
#define BOOTROM_FUNC_TABLE_OFFSET   0x14
#define BOOTROM_DATA_TABLE_OFFSET   0x16

#define BOOTROM_VTABLE_OFFSET           0x00
#define BOOTROM_TABLE_LOOKUP_OFFSET     0x18

//---- ROM FUNCTION LOOKUP CODES ---------------------------------------------------------------------------------------------------------------------------------

#define ROM_TABLE_CODE(c1, c2) ((c1) | ((c2) << 8))

// TODO: other functions

#define ROM_FUNC_CONNECT_INTERNAL_FLASH     ROM_TABLE_CODE('I', 'F')
#define ROM_FUNC_FLASH_EXIT_XIP             ROM_TABLE_CODE('E', 'X')
#define ROM_FUNC_FLASH_FLUSH_CACHE          ROM_TABLE_CODE('F', 'C')
#define ROM_FUNC_FLASH_RANGE_ERASE          ROM_TABLE_CODE('R', 'E')
#define ROM_FUNC_FLASH_RANGE_PROGRAM        ROM_TABLE_CODE('R', 'P')

//---- ROM FUNCTION TYPEDEF --------------------------------------------------------------------------------------------------------------------------------------

typedef void *(*rom_table_lookup_fn)(uint16_t *table, uint32_t code);

// TODO: other functions

typedef void (*rom_connect_internal_flash_fn)(void);

typedef void (*rom_flash_exit_xip_fn)(void);

typedef void (*rom_flash_flush_cache_fn)(void);

typedef void (*rom_flash_range_erase_fn)(uint32_t addr, uint32_t count, uint32_t block_size, uint8_t block_cmd);

typedef void (*rom_flash_range_program_fn)(uint32_t addr, const uint8_t *data, uint32_t count);

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

static inline void *rom_get_table_ptr(uint16_t rom_address) {

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Warray-bounds"

    return (void*)(uint32_t)*(uint16_t*)(uint32_t)rom_address;

    #pragma GCC diagnostic pop
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static inline void *rom_func_lookup(uint32_t code) {

    rom_table_lookup_fn rom_table_lookup = (rom_table_lookup_fn)rom_get_table_ptr(BOOTROM_TABLE_LOOKUP_OFFSET);
    uint16_t *func_table = (uint16_t *)rom_get_table_ptr(BOOTROM_FUNC_TABLE_OFFSET);

    return rom_table_lookup(func_table, code);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_BOOTROM_H_ */