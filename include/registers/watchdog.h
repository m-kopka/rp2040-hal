#ifndef _REG_WATCHDOG_H_
#define _REG_WATCHDOG_H_

/*
 *  RP2040 Watchdog register definitions
 *  Martin Kopka 2022
 *  
 *  The watchdog is a countdown timer that can restart parts of the chip if it reaches zero.
 *  This can be used to restart the processor if software gets stuck in an infinite loop.
 *  The programmer must periodically write a value to the watchdog to stop it from reaching zero.
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t CTRL;        // Watchdog control
    reg_t LOAD;        // Load the watchdog timer
    reg_t REASON;      // Logs the reason for the last reset
    reg_t SCRATCH[8];  // Scratch register. Information persists through soft reset of the chip
    reg_t TICK;        // Controls the tick generator

} WATCHDOG_t;

#define WATCHDOG ((WATCHDOG_t*)WATCHDOG_BASE)       // WATCHDOG register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// WATCHDOG: CTRL register
// Watchdog control
#define WATCHDOG_CTRL_TRIGGER       _BIT(31)    // Trigger a watchdog reset
#define WATCHDOG_CTRL_ENABLE        _BIT(30)    // When not enabled the watchdog timer is paused
#define WATCHDOG_CTRL_PAUSE_DBG1    _BIT(26)    // Pause the watchdog timer when processor 1 is in debug mode
#define WATCHDOG_CTRL_PAUSE_DBG0    _BIT(25)    // Pause the watchdog timer when processor 0 is in debug mode
#define WATCHDOG_CTRL_PAUSE_JTAG    _BIT(24)    // Pause the watchdog timer when JTAG is accessing the bus fabric

// Indicates the number of ticks / 2 (see errata RP2040-E1) before a watchdog reset will be triggered
#define WATCHDOG_CTRL_TIME_LSB      0
#define WATCHDOG_CTRL_TIME_MASK     0x00000fff

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// WATCHDOG: REASON register
// Logs the reason for the last reset. Both bits are zero for the case of a hardware reset
#define WATCHDOG_REASON_FORCE       _BIT(1)
#define WATCHDOG_REASON_TIMER       _BIT(0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// WATCHDOG: TICK register
// Controls the tick generator

// Count down timer: the remaining number clk_tick cycles before the next tick is generated
#define WATCHDOG_TICK_COUNT_LSB     11
#define WATCHDOG_TICK_COUNT_MASK    0x000ff800

#define WATCHDOG_TICK_RUNNING       _BIT(10)        // Is the tick generator running?
#define WATCHDOG_TICK_ENABLE        _BIT( 9)        // start / stop tick generation

// Total number of clk_tick cycles before the next tick
#define WATCHDOG_TICK_CYCLES_LSB    0
#define WATCHDOG_TICK_CYCLES_MASK   0x00000ff

//================================================================================================================================================================

#endif /* _REG_WATCHDOG_H_ */