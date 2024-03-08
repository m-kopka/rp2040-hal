#ifndef _REG_XOSC_H_
#define _REG_XOSC_H_

/*
 *  RP2040 XOSC register definitions
 *  Martin Kopka 2022
 * 
 *  The Crystal Oscillator (XOSC) uses an external crystal to produce an accurate reference clock. 
 *  The RP2040 supports 1MHz to 15MHz crystals.
 *  The reference clock is distributed to the PLLs, which can be used to multiply the XOSC frequency to provide accurate high speed clocks.
 *  For example, they can generate a 48MHz clock which meets the frequency accuracy requirement of the USB interface and a 133MHz maximum speed system clock.
 *  The XOSC clock is also a clock source for the clock generators, so can be used directly if required.
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t CTRL;                // Crystal Oscillator Control
    reg_t STATUS;              // Crystal Oscillator Status
    reg_t DORMANT;             // Crystal Oscillator pause control
    reg_t STARTUP;             // Controls the startup delay
    uint32_t _reserved_0[3];
    reg_t COUNT;               // A down counter running at the XOSC frequency which counts to zero and stops.

} XOSC_t;

#define XOSC ((XOSC_t*)XOSC_BASE)       // XOSC register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// XOSC: CTRL register
// Crystal Oscillator Control

/* On power-up this field is initialised to DISABLE and the chip runs from the ROSC.
 * If the chip has subsequently been programmed to run from the XOSC then setting this field to DISABLE may lock-up the chip. If this is a concern then run the clk_ref from the ROSC and enable the clk_sys RESUS feature.
 * The 12-bit code is intended to give some protection against accidental writes. An invalid setting will enable the oscillator.
 * 0xd1e → DISABLE 0xfab → ENABLE
*/ 
#define XOSC_CTRL_ENABLE_LSB                12
#define XOSC_CTRL_ENABLE_MASK               0x00fff000
#define XOSC_CTRL_ENABLE_VALUE_DISABLE      0xd1e
#define XOSC_CTRL_ENABLE_VALUE_ENABLE       0xfab

// Frequency range. This resets to 0xAA0 and cannot be changed.
#define XOSC_CTRL_FREQ_RANGE_LSB                0
#define XOSC_CTRL_FREQ_RANGE_MASK               0x00000fff
#define XOSC_CTRL_FREQ_RANGE_VALUE_1_15_MHZ     0xaa0

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// XOSC: STATUS register
// Crystal Oscillator Status
#define XOSC_STATUS_STABLE      _BIT(31)    // Oscillator is running and stable
#define XOSC_STATUS_BADWRITE    _BIT(24)    // An invalid value has been written to CTRL_ENABLE or CTRL_FREQ_RANGE or DORMANT
#define XOSC_STATUS_ENABLED     _BIT(31)    // Oscillator is enabled but not necessarily running and stable, resets to 0
#define XOSC_STATUS_FREQ_RANGE  _BIT( 0)    // The current frequency range setting, always reads 0 0x0 → 1_15MHZ

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// XOSC: DORMANT register
// Crystal Oscillator pause control
#define XOSC_DORMANT_VALUE_DORMANT      0x636f6d61
#define XOSC_DORMANT_VALUE_WAKE         0x77616b65

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// XOSC: STARTUP register
// Controls the startup delay
#define XOSC_STARTUP_X4        _BIT(20)     // Multiplies the startup_delay by 4. This is of little value to the user given that the delay can be programmed directly

// in multiples of 256*xtal_period. The reset value of 0xc4 corresponds to approx 50 000 cycles.
#define XOSC_STARTUP_DELAY_LSB      0
#define XOSC_STARTUP_DELAY_MASK     0x00003fff

//================================================================================================================================================================

#endif /* _REG_XOSC_H_ */