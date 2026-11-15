#ifndef _HAL_WATCHDOG_H_
#define _HAL_WATCHDOG_H_

/*
 *  RP2040 Watchdog LL driver
 *  Martin Kopka 2022
 */

#include "rp2040.h"

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// starts the Watchdog tick; clk_ref source needs to be configured first (ideally XOSC for accurate 1us tick)
static inline void watchdog_start_tick(uint32_t f_xosc_hz) {

    WATCHDOG->TICK = (f_xosc_hz / 1000000) | WATCHDOG_TICK_ENABLE;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// enables the Watchdog timer; the chip will reboot if the WDT times out
void watchdog_enable(uint32_t timeout_ms);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// updates the Watchdog timer
static inline void watchdog_update(void) {

    extern uint32_t load_value;
    WATCHDOG->LOAD = load_value;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// writes a value to the Watchdog scratch register; index 0-7; the value persists through soft reset of the chip
static inline void watchdog_write_scratch(uint8_t index, uint32_t value) {

    if (index < 8) WATCHDOG->SCRATCH[index] = value;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// reads a value from the Watchdog scratch register; index 0-7
static inline uint32_t watchdog_read_scratch(uint8_t index) {

    if (index < 8) return WATCHDOG->SCRATCH[index];
    else return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_WATCHDOG_H_ */