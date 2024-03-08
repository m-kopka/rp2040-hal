#ifndef _REG_TIMER_H_
#define _REG_TIMER_H_

/*
 *  RP2040 Timer register definitions
 *  Martin Kopka 2022
 * 
 *  The system timer peripheral on RP2040 provides a global microsecond timebase for the system, and generates interrupts based on this timebase.
 *  It supports the following features:
 *  • A single 64-bit counter, incrementing once per microsecond
 *  • This counter can be read from a pair of latching registers, for race-free reads over a 32-bit bus.
 *  • Four alarms: match on the lower 32 bits of counter, IRQ on match.
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t TIMEHW;      // Write to bits 63:32 of time. always write TIMELW before TIMEHW
    reg_t TIMELW;      // Write to bits 31:0 of time. writes do not get copied to time until timehw is written
    reg_t TIMEHR;      // Read from bits 63:32 of time always read TIMELR before TIMEHR
    reg_t TIMELR;      // Read from bits 31:0 of time
    reg_t ALARM[4];    // Arm alarm 0, and configure the time it will fire. Once armed, the alarm fires when TIMER_ALARM0 == TIMELR
    reg_t ARMED;       // Indicates the armed/disarmed status of each alarm
    reg_t TIMERAWH;    // Raw read from bits 63:32 of time (no side effects)
    reg_t TIMERAWL;    // Raw read from bits 31:0 of time (no side effects)
    reg_t DBGPAUSE;    // Set bits high to enable pause when the corresponding debug ports are active
    reg_t PAUSE;       // Set high to pause the timer
    reg_t INTR;        // Raw Interrupts
    reg_t INTE;        // Interrupt Enable
    reg_t INTF;        // Interrupt Force
    reg_t INTS;        // Interrupt status after masking & forcing

} TIMER_t;

#define TIMER ((TIMER_t*)TIMER_BASE)        // TIMER register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// TIMER: DBGPAUSE register
// Set bits high to enable pause when the corresponding debug ports are active
#define TIMER_DBGPAUSE_DBG1     _BIT(2)     // Pause when processor 1 is in debug mode
#define TIMER_DBGPAUSE_DBG0     _BIT(1)     // Pause when processor 0 is in debug mode

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// TIMER: INTR, INTE, INTF and INTS registers
#define TIMER_INT_ALARM3        _BIT(3)
#define TIMER_INT_ALARM2        _BIT(2)
#define TIMER_INT_ALARM1        _BIT(1)
#define TIMER_INT_ALARM0        _BIT(0)

//================================================================================================================================================================

#endif /* _REG_TIMER_H_ */