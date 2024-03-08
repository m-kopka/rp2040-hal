#ifndef _HAL_RESETS_H_
#define _HAL_RESETS_H_

/* 
 *  RP2040 Subsystem resets LL driver
 *  Martin Kopka 2022
 * 
 *  The reset controller allows software control of the resets to all of the peripherals that are not critical to boot the processor in RP2040. This includes:
 * 
 * • USB Controller
 * • PIO
 * • Peripherals such as UART, I2C, SPI, PWM, Timer, ADC
 * • PLLs
 * • IO and Pad registers
 * 
 * Every peripheral reset by the reset controller is held in reset at power-up. It is up to software to deassert the reset of peripherals it intends to use.
*/

#include "rp2040.h"

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// restets specified hardware block (or multiple blocks)
static inline void resets_reset_block(uint32_t block) {

    set_bits(RESETS->RESET, block);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// brings specified hardware block (or multiple blocks) out of reset
static inline void resets_unreset_block(uint32_t block) {

    clear_bits(RESETS->RESET, block);

	// wait for the reset to become deasserted
    while (bit_is_clear(RESETS->RESET_DONE, block));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_RESETS_H_ */