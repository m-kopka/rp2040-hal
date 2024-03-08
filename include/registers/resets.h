#ifndef _REG_RESETS_H_
#define _REG_RESETS_H_

/*
 *  Subsystem resets register definitions
 *  Martin Kopka 2022
 *
 *  The reset controller allows software control of the resets to all of the peripherals that are not critical to boot the processor in RP2040. This includes:
 *  • USB Controller
 *  • PIO
 *  • Peripherals such as UART, I2C, SPI, PWM, Timer, ADC
 *  • PLLs
 *  • IO and Pad registers
 * 
 *  Every peripheral reset by the reset controller is held in reset at power-up. It is up to software to deassert the reset of peripherals it intends to use.
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t RESET;           // Reset control. If a bit is set it means the peripheral is in reset. 0 means the peripheral’s reset is deasserted.
    reg_t WDSEL;           // Watchdog select. If a bit is set then the watchdog will reset this peripheral when the watchdog fires.
    reg_t RESET_DONE;      // Reset done. If a bit is set then a reset done signal has been returned by the peripheral. This indicates that the peripheral’s registers are ready to be accessed.

} RESETS_t;

#define RESETS ((RESETS_t*)RESETS_BASE)       // RESETS register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

#define RESETS_USBCTRL      _BIT(24)
#define RESETS_UART1        _BIT(23)
#define RESETS_UART0        _BIT(22)
#define RESETS_TIMER        _BIT(21)
#define RESETS_TBMAN        _BIT(20)
#define RESETS_SYSINFO      _BIT(19)
#define RESETS_SYSCFG       _BIT(18)
#define RESETS_SPI1         _BIT(17)
#define RESETS_SPI0         _BIT(16)
#define RESETS_RTC          _BIT(15)
#define RESETS_PWM          _BIT(14)
#define RESETS_PLL_USB      _BIT(13)
#define RESETS_PLL_SYS      _BIT(12)
#define RESETS_PIO1         _BIT(11)
#define RESETS_PIO0         _BIT(10)
#define RESETS_PADS_QSPI    _BIT( 9)
#define RESETS_PADS_BANK0   _BIT( 8)
#define RESETS_JTAG         _BIT( 7)
#define RESETS_IO_QSPI      _BIT( 6)
#define RESETS_IO_BANK0     _BIT( 5)
#define RESETS_I2C1         _BIT( 4)
#define RESETS_I2C0         _BIT( 3)
#define RESETS_DMA          _BIT( 2)
#define RESETS_BUSCTRL      _BIT( 1)
#define RESETS_ADC          _BIT( 0)

//================================================================================================================================================================

#endif /* _REG_RESETS_H_ */