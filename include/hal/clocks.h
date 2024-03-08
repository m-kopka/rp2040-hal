#ifndef _HAL_CLOCKS_H_
#define _HAL_CLOCKS_H_

/*
 *  RP2040 clocks LL Driver
 *  Martin Kopka 2022
*/

#include "rp2040.h"

//---- ENUMERATIONS ----------------------------------------------------------------------------------------------------------------------------------------------

enum clock_auxsrc_t {

    CLOCK_AUXSRC_CLKSRC_PLL_SYS   = 0x00,
    CLOCK_AUXSRC_CLKSRC_GPIN0     = 0x01,
    CLOCK_AUXSRC_CLKSRC_GPIN1     = 0x02,
    CLOCK_AUXSRC_CLKSRC_PLL_USB   = 0x03,
    CLOCK_AUXSRC_ROSC_CLKSRC_PH   = 0x04,
    CLOCK_AUXSRC_XOSC_CLKSRC      = 0x05,
    CLOCK_AUXSRC_CLK_SYS          = 0x06,
    CLOCK_AUXSRC_CLK_USB          = 0x07,
    CLOCK_AUXSRC_CLK_ADC          = 0x08,
    CLOCK_AUXSRC_CLK_RTC          = 0x09,
    CLOCK_AUXSRC_CLK_REF          = 0x0a
};

enum clock_src_t {

    CLOCK_SRC_ROSC_CLKSRC_PH        = 0x00,     // Ring oscillator
    CLOCK_SRC_CLKSRC_CLK_REF_AUX    = 0x01,     // Auxiliary source
    CLOCK_SRC_XOSC_CLKSRC           = 0x02      // Crystal oscillator
};

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// enables or disables the clock
static volatile void clocks_set_enable(enum clock_instance clk, bool enabled) {

    if (enabled) set_bits(CLOCKS->CLK[clk].CTRL, CLK_CTRL_ENABLE);
    else       clear_bits(CLOCKS->CLK[clk].CTRL, CLK_CTRL_ENABLE);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// selects the glitchless mux source of a clock
static volatile void clocks_set_source(enum clock_instance clk, enum clock_src_t src) {

	write_masked(CLOCKS->CLK[clk].CTRL, src, CLK_CTRL_SRC_MASK, CLK_CTRL_SRC_LSB);
    while (CLOCKS->CLK[clk].SELECTED != (1 << src));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// selects the auxiliary mux source of a clock. Caution: make sure the glitchless mux is swicthed to other source than AUX or that the clock is disabled.
// Switching a running clock will generate glitches, that could corrupt the state of the peripheral's logic
static volatile void clocks_set_aux_source(enum clock_instance clk, enum clock_auxsrc_t auxsrc) {

    write_masked(CLOCKS->CLK[clk].CTRL, auxsrc, CLK_CTRL_AUXSRC_MASK, CLK_CTRL_AUXSRC_LSB);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_CLOCKS_H_ */