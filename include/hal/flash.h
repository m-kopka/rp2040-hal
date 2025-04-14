#ifndef _HAL_FLASH_H_
#define _HAL_FLASH_H_

/*
 *  RP2040 FLASH LL Driver
 *  Martin Kopka 2025
*/

#include "rp2040.h"

//---- CONSTANTS -------------------------------------------------------------------------------------------------------------------------------------------------

#define FLASH_PAGE_SIZE (1u << 8)
#define FLASH_SECTOR_SIZE (1u << 12)
#define FLASH_BLOCK_SIZE (1u << 16)

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// flash_offset must be aligned to 4096 sector and size must be a multiple of 4096
void SRAM_FUNC flash_range_erase(uint32_t flash_offset, uint32_t count);

// flash_offset must be aligned to 256 byte page and count must be a multiple of 256
void SRAM_FUNC flash_range_program(uint32_t flash_offset, const uint8_t *data, uint32_t count);

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_FLASH_H_ */