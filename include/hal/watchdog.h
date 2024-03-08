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

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_WATCHDOG_H_ */