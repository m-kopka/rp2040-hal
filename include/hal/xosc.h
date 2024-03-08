#ifndef _HAL_XOSC_H_
#define _HAL_XOSC_H_

/*
 *  RP2040 XOSC LL Driver
 *  Martin Kopka 2022
 */

#include "rp2040.h"

//---- MACROS ----------------------------------------------------------------------------------------------------------------------------------------------------

#define XOSC_STARTUP_DELAY          0x00c4      // XOSC startup delay

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// enables the crystal oscillator and waits for it to become stable
static inline void xosc_enable(void) {

    XOSC->CTRL = XOSC_CTRL_FREQ_RANGE_VALUE_1_15_MHZ;   // set XOSC frequency range to 1 - 15 MHz
    XOSC->STARTUP = XOSC_STARTUP_DELAY;                 // set XOSC startup delay

	// enable XOSC
    write_masked(XOSC->CTRL, XOSC_CTRL_ENABLE_VALUE_ENABLE, XOSC_CTRL_ENABLE_MASK, XOSC_CTRL_ENABLE_LSB);
	
    // wait for XOSC to become stable
    while (bit_is_clear(XOSC->STATUS, XOSC_STATUS_STABLE));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// disables the crystal oscillator and waits for it to become unstable
static inline void xosc_disable(void) {

    // disable XOSC
    write_masked(XOSC->CTRL, XOSC_CTRL_ENABLE_VALUE_DISABLE, XOSC_CTRL_ENABLE_MASK, XOSC_CTRL_ENABLE_LSB);

    // wait for XOSC to become unstable
    while (bit_is_set(XOSC->STATUS, XOSC_STATUS_STABLE));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_XOSC_H_ */