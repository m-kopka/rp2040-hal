#ifndef _REG_PWM_H_
#define _REG_PWM_H_

/*
 *  RP2040 PWM register definitions
 *  Martin Kopka 2022
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#define PWM_SLICE_COUNT 8       // number of PWM slices

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

typedef struct {

    reg_t CSR;     // Control and status register
    reg_t DIV;     // INT and FRAC form a fixed-point fractional number. Counting rate is system clock frequency divided by this number.
    reg_t CTR;     // Direct access to the PWM counter
    reg_t CC;      // Counter compare values
    reg_t TOP;     // Counter wrap value

} PWM_slice_t;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

typedef struct {

    PWM_slice_t CH[PWM_SLICE_COUNT];
    reg_t EN;                          // This register aliases the CSR_EN bits for all channels. Writing to this register allows multiple channels to be enabled or disabled simultaneously, so they can run in perfect sync.
    reg_t INTR;                        // Raw Interrupts
    reg_t INTE;                        // Interrupt Enable
    reg_t INTF;                        // Interrupt Force
    reg_t INTS;                        // Interrupt status after masking & forcing

} PWM_t;

#define PWM ((PWM_t*)PWM_BASE)       // PWM register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// PWM: CSR register
// Control and status register
#define PWM_CSR_PH_ADV          _BIT(7)     // Advance the phase of the counter by 1 count, while it is running
#define PWM_CSR_PH_RET          _BIT(6)     // Retard the phase of the counter by 1 count, while it is running

#define PWM_CSR_DIVMODE_LSB     4
#define PWM_CSR_DIVMODE_MASK    0x00000030

#define PWM_CSR_B_INV           _BIT(3)     // Invert output B
#define PWM_CSR_A_INV           _BIT(2)     // Invert output A
#define PWM_CSR_PH_CORRECT      _BIT(1)     // 1: Enable phase-correct modulation. 0: Trailing-edge
#define PWM_CSR_EN              _BIT(0)     // Enable the PWM channel

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// PWM: DIV register
// INT and FRAC form a fixed-point fractional number. Counting rate is system clock frequency divided by this number.
#define PWM_DIV_INT_LSB     4
#define PWM_DIV_INT_MASK    0x00000ff0

#define PWM_DIV_FRAC_LSB    0
#define PWM_DIV_FRAC_MASK   0x0000000f

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// PWM: CC register
// Counter compare values
#define PWM_CC_B_LSB        16
#define PWM_CC_B_MASK       0xffff0000

#define PWM_CC_A_LSB        0
#define PWM_CC_A_MASK       0x0000ffff

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// PWM: EN register
// This register aliases the CSR_EN bits for all channels.
#define PWM_CH7     _BIT(7)
#define PWM_CH6     _BIT(6)
#define PWM_CH5     _BIT(5)
#define PWM_CH4     _BIT(4)
#define PWM_CH3     _BIT(3)
#define PWM_CH2     _BIT(2)
#define PWM_CH1     _BIT(1)
#define PWM_CH0     _BIT(0)

//================================================================================================================================================================

#endif /* _REG_PWM_H_ */