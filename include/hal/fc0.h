#ifndef _HAL_FC0_H_
#define _HAL_FC0_H_

/*
 *  RP2040 Frequency counter LL driver
 *  Martin Kopka 2022
*/

#include "rp2040.h"

//---- ENUMERATONS -----------------------------------------------------------------------------------------------------------------------------------------------

enum fc0_src {

    fc0_NULL                    = 0x00,
    fc0_pll_sys_clksrc_primary  = 0x01,
    fc0_pll_usb_clksrc_primary  = 0x02,
    fc0_rosc_clksrc             = 0x03,
    fc0_rosc_clksrc_ph          = 0x04,
    fc0_xosc_clksrc             = 0x05,
    fc0_clksrc_gpin0            = 0x06,
    fc0_clksrc_gpin1            = 0x07,
    fc0_clk_ref                 = 0x08,
    fc0_clk_sys                 = 0x09,
    fc0_clk_peri                = 0x0a,
    fc0_clk_usb                 = 0x0b,
    fc0_clk_adc                 = 0x0c,
    fc0_clk_rtc                 = 0x0d
};

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the frequency counter
static inline void fc0_init(uint32_t f_clk_ref) {

    CLOCKS->FC0.REF_KHZ = f_clk_ref / 1000;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// uses the frequency counter to measure a clock frequency [Hz]
static inline uint32_t fc0_get_hz(enum fc0_src source) {

    CLOCKS->FC0.SRC = source;

    while(bit_is_clear(CLOCKS->FC0.STATUS, FC0_STATUS_DONE))
        if (bit_is_set(CLOCKS->FC0.STATUS, FC0_STATUS_DIED)) return 0;

    return ((CLOCKS->FC0.RESULT >> 5) * 1000);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_FC0_H_ */