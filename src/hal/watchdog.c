#include "hal/watchdog.h"

uint32_t load_value;     // load value for the watchdog countdown

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// enables the Watchdog timer; the chip will reboot if the WDT times out
void watchdog_enable(uint32_t timeout_ms) {

    clear_bits(WATCHDOG->CTRL, WATCHDOG_CTRL_ENABLE);

	PSM->WDSEL = ~(PSM_ROSC | PSM_XOSC);
	set_bits(WATCHDOG->CTRL, WATCHDOG_CTRL_PAUSE_DBG0 | WATCHDOG_CTRL_PAUSE_DBG1 | WATCHDOG_CTRL_PAUSE_JTAG);

	// we need to load 2x the ammount of ticks (see errata RP2040-E1)
	load_value = 2 * 1000 * timeout_ms;
	watchdog_update();
    
	set_bits(WATCHDOG->CTRL, WATCHDOG_CTRL_ENABLE);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
