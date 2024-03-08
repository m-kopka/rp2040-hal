#ifndef _REG_ADC_H_
#define _REG_ADC_H_

/* 
 *  RP2040 ADC register definitions
 *  Martin Kopka 2022
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t CS;          // ADC Control and Status
    reg_t RESULT;      // Result of most recent ADC conversion
    reg_t FCS;         // FIFO control and status
    reg_t FIFO;        // Conversion result FIFO
    reg_t DIV;         // Clock divider. If non-zero, CS_START_MANY will start conversions at regular intervals rather than back-to-back.
    reg_t INTR;        // Raw Interrupts
    reg_t INTE;        // Interrupt Enable
    reg_t INTF;        // Interrupt Force
    reg_t INTS;        // Interrupt status after masking & forcing

} ADC_t;

#define ADC ((ADC_t*)ADC_BASE)      // ADC register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// ADC: CS register
// ADC Control and Status

/* Round-robin sampling. 1 bit per channel. Set all bits to 0 to disable.
 * Otherwise, the ADC will cycle through each enabled channel in a round-robin fashion.
 * The first channel to be sampled will be the one currently indicated by AINSEL.
 * AINSEL will be updated after each conversion with the newly-selected channel.
*/
#define ADC_CS_RROBIN_LSB       16
#define ADC_CS_RROBIN_MASK      0x001f0000
#define ADC_CD_RROBIN_VAL_ADC4  _BIT(20)
#define ADC_CD_RROBIN_VAL_ADC3  _BIT(19)
#define ADC_CD_RROBIN_VAL_ADC2  _BIT(18)
#define ADC_CD_RROBIN_VAL_ADC1  _BIT(17)
#define ADC_CD_RROBIN_VAL_ADC0  _BIT(16)

// Select analog mux input. Updated automatically in round- robin mode.
#define ADC_CS_AINSEL_LSB       12
#define ADC_CS_AINSEL_MASK      0x00007000
#define ADC_CS_AINSEL_VAL_ADC4  (0x4 << ADC_CS_AINSEL_LSB)
#define ADC_CS_AINSEL_VAL_ADC3  (0x3 << ADC_CS_AINSEL_LSB)
#define ADC_CS_AINSEL_VAL_ADC2  (0x2 << ADC_CS_AINSEL_LSB)
#define ADC_CS_AINSEL_VAL_ADC1  (0x1 << ADC_CS_AINSEL_LSB)
#define ADC_CS_AINSEL_VAL_ADC0  (0x0 << ADC_CS_AINSEL_LSB)

#define ADC_CS_ERRSTICKY        _BIT(10)    // Some past ADC conversion encountered an error. Write 1 to clear.
#define ADC_CS_ERR              _BIT( 9)    // The most recent ADC conversion encountered an error; result is undefined or noisy.
#define ADC_CS_READY            _BIT( 8)    // 1 if the ADC is ready to start a new conversion. Implies any previous conversion has completed. 0 whilst conversion in progress.
#define ADC_CS_START_MANY       _BIT( 3)    // Continuously perform conversions whilst this bit is 1. A new conversion will start immediately after the previous finishes.
#define ADC_CS_START_ONCE       _BIT( 2)    // Start a single conversion. Self-clearing. Ignored if start_many is asserted.
#define ADC_CS_TS_EN            _BIT( 1)    // Power on temperature sensor. 1 - enabled. 0 - disabled.
#define ADC_CS_EN               _BIT( 0)    // Power on ADC and enable its clock. 1 - enabled. 0 - disabled.

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// ADC: FCS register
// FIFO control and status

// DREQ/IRQ asserted when level >= threshold
#define ADC_FCS_THRESH_LSB          24
#define ADC_FCS_THRESH_MASK         0x0f000000

// The number of conversion results currently waiting in the FIFO
#define ADC_FCS_LEVEL_LSB           16
#define ADC_FCS_LEVEL_MASK          0x000f0000

#define ADC_FCS_OVER        _BIT(11)    // 1 if the FIFO has been overflowed. Write 1 to clear.
#define ADC_FCS_UNDER       _BIT(10)    // 1 if the FIFO has been underflowed. Write 1 to clear.
#define ADC_FCS_FULL        _BIT( 9)
#define ADC_FCS_EMPTY       _BIT( 8)
#define ADC_FCS_DREQ_EN     _BIT( 3)    // If 1: assert DMA requests when FIFO contains data
#define ADC_FCS_ERR         _BIT( 2)    // If 1: conversion error bit appears in the FIFO alongside the result
#define ADC_FCS_SHIFT       _BIT( 1)    // If 1: FIFO results are right-shifted to be one byte in size. Enables DMA to byte buffers.
#define ADC_FCS_EN          _BIT( 0)    // If 1: write result to the FIFO after each conversion.

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// ADC: FIFO register
// Conversion result FIFO
#define ADC_FIFO_ERR            _BIT(15)        // 1 if this particular sample experienced a conversion error. Remains in the same location if the sample is shifted.

#define ADC_FIFO_VAL_LSB        0
#define ADC_FIFO_VAL_MASK       0x00000fff

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// ADC: DIV register
/* Clock divider. If non-zero, CS_START_MANY will start conversions at regular intervals rather than back-to-back.
 * The divider is reset when either of these fields are written.
 * Total period is 1 + INT + FRAC / 256
*/

// Integer part of clock divisor.
#define ADC_DIV_INT_LSB         8
#define ADC_DIV_INT_MASK        0x00ffff00

// Fractional part of clock divisor. First-order delta-sigma.
#define ADC_DIV_FRAC_LSB        0
#define ADC_DIV_FRAC_MASK       0x000000ff

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// ADC: INTR,INTE,INTF and INTS registers
#define ADC_INT_FIFO        _BIT(0)     // Triggered when the sample FIFO reaches a certain level. This level can be programmed via the FCS_THRESH field.

//================================================================================================================================================================

#endif /* _REG_ADC_H_ */