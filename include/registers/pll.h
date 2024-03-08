#ifndef _REG_PLL_H_
#define _REG_PLL_H_

/*
 *  RP2040 PLL register definitions
 *  Martin Kopka 2022
 * 
 *  The PLL is designed to take a reference clock, and multiply it using a VCO (Voltage Controlled Oscillator) with a feedback loop.
 *  The VCO must run at high frequencies (between 400 and 1600 MHz), so there are two dividers, known as post dividers that can divide the VCO frequency before it is distributed to the clock generators on the chip.
 *  There are two PLLs in RP2040. They are:
 *  • pll_sys - Used to generate up to a 133 MHz system clock
 *  • pll_usb - Used to generate a 48 MHz USB reference clock
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t CS;              // Control and Status
    reg_t PWR;             // Controls the PLL power modes.
    reg_t FBDIV_INT;       // Feedback divisor
    reg_t PRIM;            // Controls the PLL post dividers for the primary output

} PLL_t;

#define PLL_SYS ((PLL_t*)PLL_SYS_BASE)       // PLL_SYS register block
#define PLL_USB ((PLL_t*)PLL_USB_BASE)       // PLL_USB register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// PLL: CS register
// Control and Status
#define PLL_CS_LOCK         _BIT(31)        // PLL is locked
#define PLL_CS_BYPASS       _BIT(8)         // Passes the reference clock to the output instead of the divided VCO

// Divides the PLL input reference clock.
#define PLL_CS_REFDIV_LSB   0
#define PLL_CS_REFDIV_MASK  0x0000001f

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// PLL: PWR register
// Controls the PLL power modes.

#define PLL_PWR_VCOPD       _BIT(5)         // PLL VCO powerdown. To save power set high when PLL output not required or bypass=1.
#define PLL_PWR_POSTDIVPD   _BIT(3)         // PLL post divider powerdown. To save power set high when PLL output not required or bypass=1.
#define PLL_PWR_DSMPD       _BIT(2)         // PLL DSM powerdown. Nothing is achieved by setting this low.
#define PLL_PWR_PD          _BIT(0)         // PLL powerdown. To save power set high when PLL output not required.

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// PLL: FBDIV_INT register [11:0] (RW)
// Feedback divisor (note: this PLL does not support fractional division)
#define PLL_FBDIV_INT   _REG(PLL_SYS_BASE + 0x08)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// PLL: PRIM register
/* Controls the PLL post dividers for the primary output (note: this PLL does not have a secondary output)
 * the primary output is driven from VCO divided by postdiv1*postdiv2
*/

// divide by 1-7
#define PLL_PRIM_POSTDIV1_LSB       16
#define PLL_PRIM_POSTDIV1_MASK      0x00070000

// divide by 1-7
#define PLL_PRIM_POSTDIV2_LSB       12
#define PLL_PRIM_POSTDIV2_MASK      0x00007000

//================================================================================================================================================================

#endif /* _REG_PLL_H_ */