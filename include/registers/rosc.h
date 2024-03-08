#ifndef _REG_ROSC_H_
#define _REG_ROSC_H_

/*
 *  RP2040 ROSC register definitions
 *  Martin Kopka 2024
 * 
 *  The Ring Oscillator (ROSC) is an on-chip oscillator built from a ring of inverters. 
 *  It requires no external components and is started automatically during RP2040 power up.
 *  It provides the clock to the cores during boot. 
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t CTRL;                 // Ring Oscillator control
    reg_t FREQA;                // Ring Oscillator frequency control A
    reg_t FREQB;                // Ring Oscillator frequency control B
    reg_t DORMANT;              // Ring Oscillator pause control
    reg_t DIV;                  // Controls the output divider
    reg_t PHASE;                // Controls the phase shifted output
    reg_t STATUS;               // Ring Oscillator Status
    reg_t RANDOMBIT;            // Returns a 1 bit random value
    reg_t COUNT;                // A down counter running at the ROSC frequency which counts to zero and stops.

} ROSC_t;

#define ROSC ((ROSC_t*)ROSC_BASE)       // ROSC register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// ROSC: CTRL register
// Ring Oscillator Control

/* On power-up this field is initialised to ENABLE
 * The system clock must be switched to another source before setting this field to DISABLE otherwise the chip will lock up
 * The 12-bit code is intended to give some protection against accidental writes. An invalid setting will enable the oscillator.*/
#define ROSC_CTRL_ENABLE_LSB                12
#define ROSC_CTRL_ENABLE_MASK               0x00fff000
#define ROSC_CTRL_ENABLE_VALUE_DISABLE      0xd1e
#define ROSC_CTRL_ENABLE_VALUE_ENABLE       0xfab

// TODO

//================================================================================================================================================================

#endif /* _REG_ROSC_H_ */