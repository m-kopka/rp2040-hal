#ifndef _HAL_TIMER_H_
#define _HAL_TIMER_H_

/*
 *  RP2040 ADC Timer Driver
 *  Martin Kopka 2024
*/

#include "rp2040.h"

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// returns the time since reset [us]; Watchdog tick needs to be initialized first
static inline uint64_t timer_get_us(void) {

    // we need to read the TIMELR register first to avoid corrupted values
    uint64_t low = TIMER->TIMELR;
    return ((uint64_t)TIMER->TIMEHR << 32 | low);

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_TIMER_H_ */