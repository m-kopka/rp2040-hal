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

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// resets specified hardware block (or multiple blocks) and then brings it out of reset
static inline void resets_reset_and_unreset_block(uint32_t block) {

    resets_reset_block(block);
    resets_unreset_block(block);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// returns true if specified hardware block (or multiple blocks) is in reset, false otherwise
static inline bool resets_is_get_block_reset(uint32_t block) {

    return bit_is_set(RESETS->RESET, block);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// enables the watchdog to reset specified hardware block (or multiple blocks)
static inline void resets_enable_block_watchdog_reset(uint32_t block) {

    set_bits(RESETS->WDSEL, block);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static inline void resets_disable_block_watchdog_reset(uint32_t block) {

    clear_bits(RESETS->WDSEL, block);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static inline uint32_t resets_block_pointer_to_resets_bit(void *block_pointer) {

    // if (block_pointer == USBCTRL) return RESETS_USBCTRL; // not implemented yet
    if (block_pointer == UART1) return RESETS_UART1;
    if (block_pointer == UART0) return RESETS_UART0;
    if (block_pointer == TIMER) return RESETS_TIMER;
    // if (block_pointer == TBMAN) return RESETS_TBMAN; // not implemented yet
    // if (block_pointer == SYSINFO) return RESETS_SYSINFO; // not implemented yet
    // if (block_pointer == SYSCFG) return RESETS_SYSCFG; // not implemented yet
    if (block_pointer == SPI1) return RESETS_SPI1;
    if (block_pointer == SPI0) return RESETS_SPI0;
    // if (block_pointer == RTC) return RESETS_RTC; // not implemented yet
    if (block_pointer == PWM) return RESETS_PWM;
    if (block_pointer == PLL_USB) return RESETS_PLL_USB;
    if (block_pointer == PLL_SYS) return RESETS_PLL_SYS;
    // if (block_pointer == PIO1) return RESETS_PIO1; // not implemented yet
    // if (block_pointer == PIO0) return RESETS_PIO0; // not implemented yet
    // if (block_pointer == PADS_QSPI) return RESETS_PADS_QSPI; // not implemented yet
    if (block_pointer == PADS_BANK0) return RESETS_PADS_BANK0;
    // if (block_pointer == JTAG) return RESETS_JTAG;       // JTAG is not a register block
    // if (block_pointer == IO_QSPI) return RESETS_IO_QSPI; // not implemented yet
    if (block_pointer == IO_BANK0) return RESETS_IO_BANK0;
    if (block_pointer == I2C1) return RESETS_I2C1;
    if (block_pointer == I2C0) return RESETS_I2C0;
    if (block_pointer == DMA) return RESETS_DMA;
    //if (block_pointer == BUSCTRL) return RESETS_BUSCTRL; // not implemented yet
    if (block_pointer == ADC) return RESETS_ADC;

    return (1 << 31);   // unknown block pointer
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// resets the specified peripheral by its pointer
static inline void resets_reset_peripheral(void *peripheral_pointer) {

    resets_reset_block(resets_block_pointer_to_resets_bit(peripheral_pointer));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// brings the specified peripheral out of reset by its pointer
static inline void resets_unreset_peripheral(void *peripheral_pointer) {

    resets_unreset_block(resets_block_pointer_to_resets_bit(peripheral_pointer));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// resets and brings the specified peripheral out of reset by its pointer
static inline void resets_reset_and_unreset_peripheral(void *peripheral_pointer) {

    resets_reset_and_unreset_block(resets_block_pointer_to_resets_bit(peripheral_pointer));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_RESETS_H_ */