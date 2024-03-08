#ifndef _REG_PSM_H_
#define _REG_PSM_H_

/*
 *  RP2040 Power-On State Machine register definitions
 *  Martin Kopka 2024
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t FRCE_ON;     // Force block out of reset (i.e. power it on)
    reg_t FRCE_OFF;    // Force into reset (i.e. power it off)
    reg_t WDSEL;       // Set to 1 if this peripheral should be reset when the watchdog fires.
    reg_t DONE;        // Indicates the peripheral’s registers are ready to access.

} PSM_t;

#define PSM ((PSM_t*)PSM_BASE)       // PSM register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

#define PSM_PROC1                   _BIT(16)
#define PSM_PROC0                   _BIT(15)
#define PSM_SIO                     _BIT(14)
#define PSM_VREG_AND_CHIP_RESET     _BIT(13)
#define PSM_XIP                     _BIT(12)
#define PSM_SRAM5                   _BIT(11)
#define PSM_SRAM4                   _BIT(10)
#define PSM_SRAM3                   _BIT( 9)
#define PSM_SRAM2                   _BIT( 8)
#define PSM_SRAM1                   _BIT( 7)
#define PSM_SRAM0                   _BIT( 6)
#define PSM_ROM                     _BIT( 5)
#define PSM_BUSFABRIC               _BIT( 4)
#define PSM_RESETS                  _BIT( 3)
#define PSM_CLOCKS                  _BIT( 2)
#define PSM_XOSC                    _BIT( 1)
#define PSM_ROSC                    _BIT( 0)

//================================================================================================================================================================

#endif /* _REG_WATCHDOG_H_ */