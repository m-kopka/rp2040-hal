#ifndef _HAL_CLOCKS_H_
#define _HAL_CLOCKS_H_

/*
 *  RP2040 clocks LL Driver
 *  Martin Kopka 2022
*/

#include "rp2040.h"

//---- ENUMERATIONS ----------------------------------------------------------------------------------------------------------------------------------------------

// auxiliary clock source MUX options, will glitch when switching
enum clock_auxsrc_t {

    CLOCK_AUXSRC_GPOUT_CLKSRC_PLL_SYS   = 0x00,
    CLOCK_AUXSRC_GPOUT_CLKSRC_GPIN0     = 0x01,
    CLOCK_AUXSRC_GPOUT_CLKSRC_GPIN1     = 0x02,
    CLOCK_AUXSRC_GPOUT_CLKSRC_PLL_USB   = 0x03,
    CLOCK_AUXSRC_GPOUT_ROSC_CLKSRC      = 0x04,
    CLOCK_AUXSRC_GPOUT_XOSC_CLKSRC      = 0x05,
    CLOCK_AUXSRC_GPOUT_CLK_SYS          = 0x06,
    CLOCK_AUXSRC_GPOUT_CLK_USB          = 0x07,
    CLOCK_AUXSRC_GPOUT_CLK_ADC          = 0x08,
    CLOCK_AUXSRC_GPOUT_CLK_RTC          = 0x09,
    CLOCK_AUXSRC_GPOUT_CLK_REF          = 0x0a,

    CLOCK_AUXSRC_REF_CLKSRC_PLL_USB     = 0x00,
    CLOCK_AUXSRC_REF_CLKSRC_GPIN0       = 0x01,
    CLOCK_AUXSRC_REF_CLKSRC_GPIN1       = 0x02,

    CLOCK_AUXSRC_SYS_CLKSRC_PLL_SYS     = 0x00,
    CLOCK_AUXSRC_SYS_CLKSRC_PLL_USB     = 0x01,
    CLOCK_AUXSRC_SYS_ROSC_CLKSRC        = 0x02,
    CLOCK_AUXSRC_SYS_XOSC_CLKSRC        = 0x03,
    CLOCK_AUXSRC_SYS_CLKSRC_GPIN0       = 0x04,
    CLOCK_AUXSRC_SYS_CLKSRC_GPIN1       = 0x05,

    CLOCK_AUXSRC_PERI_CLK_SYS           = 0x00,
    CLOCK_AUXSRC_PERI_CLKSRC_PLL_SYS    = 0x01,
    CLOCK_AUXSRC_PERI_CLKSRC_PLL_USB    = 0x02,
    CLOCK_AUXSRC_PERI_ROSC_CLKSRC       = 0x03,
    CLOCK_AUXSRC_PERI_XOSC_CLKSRC       = 0x04,
    CLOCK_AUXSRC_PERI_CLKSRC_GPIN0      = 0x05,
    CLOCK_AUXSRC_PERI_CLKSRC_GPIN1      = 0x06,

    CLOCK_AUXSRC_USB_CLKSRC_PLL_USB     = 0x00,
    CLOCK_AUXSRC_USB_CLKSRC_PLL_SYS     = 0x01,
    CLOCK_AUXSRC_USB_ROSC_CLKSRC        = 0x02,
    CLOCK_AUXSRC_USB_XOSC_CLKSRC        = 0x03,
    CLOCK_AUXSRC_USB_CLKSRC_GPIN0       = 0x04,
    CLOCK_AUXSRC_USB_CLKSRC_GPIN1       = 0x05,

    CLOCK_AUXSRC_ADC_CLKSRC_PLL_USB     = 0x00,
    CLOCK_AUXSRC_ADC_CLKSRC_PLL_SYS     = 0x01,
    CLOCK_AUXSRC_ADC_ROSC_CLKSRC        = 0x02,
    CLOCK_AUXSRC_ADC_XOSC_CLKSRC        = 0x03,
    CLOCK_AUXSRC_ADC_CLKSRC_GPIN0       = 0x04,
    CLOCK_AUXSRC_ADC_CLKSRC_GPIN1       = 0x05,

    CLOCK_AUXSRC_RTC_CLKSRC_PLL_USB     = 0x00,
    CLOCK_AUXSRC_RTC_CLKSRC_PLL_SYS     = 0x01,
    CLOCK_AUXSRC_RTC_ROSC_CLKSRC        = 0x02,
    CLOCK_AUXSRC_RTC_XOSC_CLKSRC        = 0x03,
    CLOCK_AUXSRC_RTC_CLKSRC_GPIN0       = 0x04,
    CLOCK_AUXSRC_RTC_CLKSRC_GPIN1       = 0x05
};

// glitchless clock source MUX options, can be changed on- the-fly
enum clock_src_t {

    CLOCK_SRC_REF_ROSC_CLKSRC           = 0x00,
    CLOCK_SRC_REF_CLKSRC_CLK_REF_AUX    = 0x01,
    CLOCK_SRC_REF_XOSC_CLKSRC           = 0x02,

    CLOCK_SRC_SYS_CLK_REF               = 0x00,
    CLOCK_SRC_SYS_CLKSRC_CLK_SYS_AUX    = 0x01,
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