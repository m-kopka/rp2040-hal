#ifndef _RP2040_H_
#define _RP2040_H_

#include <stdint.h>
#include <stdbool.h>

//---- REGISTER DEFINITIONS --------------------------------------------------------------------------------------------------------------------------------------

#include "registers/sio.h"
#include "registers/vreg.h"
#include "registers/psm.h"
#include "registers/resets.h"
#include "registers/clocks.h"
#include "registers/xosc.h"
#include "registers/rosc.h"
#include "registers/pll.h"
#include "registers/io_bank0.h"
#include "registers/pads_bank0.h"
// TODO: #include "registers/sysinfo.h"
// TODO: #include "registers/syscfg.h"
// TODO: #include "registers/tbman.h"
// TODO: #include "registers/pio.h"
// TODO: #include "registers/usb.h"
#include "registers/uart.h"
// TODO: #include "registers/i2c.h"
// TODO: #include "registers/spi.h"
#include "registers/pwm.h"
#include "registers/timer.h"
#include "registers/watchdog.h"
// TODO: #include "registers/rtc.h"
#include "registers/adc.h"
// TODO: #include "registers/ssi.h"

//---- CMSIS CONFIG ----------------------------------------------------------------------------------------------------------------------------------------------

#define __CM0PLUS_REV             0x0001        // core revision
#define __MPU_PRESENT             1             // Memory Protection Unit present
#define __NVIC_PRIO_BITS          2             // 2 NVIC priority bits
#define __Vendor_SysTickConfig    0             // SysTick configuration
#define __FPU_PRESENT             0             // Floating Point Unit not present

//---- INTERRUPTS ------------------------------------------------------------------------------------------------------------------------------------------------

typedef enum {

    // Cortex-M0+ Processor Exceptions
    NonMaskableInt_IRQn = -14,    // Non maskable interrupt
    SVCall_IRQn         = -5,     // System Service call via SWI instruction
    PendSV_IRQn         = -2,     // Pendable request for system service
    SysTick_IRQn        = -1,     // System tick timer

    // RP2040 specific Interrupts
    TIMER_IRQ0      = 0,
    TIMER_IRQ1      = 1,
    TIMER_IRQ2      = 2,
    TIMER_IRQ3      = 3,
    PWM_IRQ         = 4,
    USBCTRL_IRQ     = 5,
    XIP_IRQ         = 6,
    PIO0_IRQ0       = 7,
    PIO0_IRQ1       = 8,
    PIO1_IRQ0       = 9,
    PIO1_IRQ1       = 10,
    DMA_IRQ0        = 11,
    DMA_IRQ1        = 12,
    IO_BANK0_IRQ    = 13,
    IO_QSPI_IRQ     = 14,
    SIO_PROC_IRQ0   = 15,
    SIO_PROC_IRQ1   = 16,
    CLOCKS_IRQ      = 17,
    SPI0_IRQ        = 18,
    SPI1_IRQ        = 19,
    UART0_IRQ       = 20,
    UART1_IRQ       = 21,
    ADC_IRQ         = 22,
    I2C_IRQ0        = 23,
    I2C_IRQ1        = 24,
    RTC_IRQ         = 25

} IRQn_Type;

#include "CMSIS/core_cm0plus.h"

//---- REGISTER MANIPULATION FUNCTIONS ---------------------------------------------------------------------------------------------------------------------------

// set bits in register
#define set_bits(address, mask) ((address) |= ((uint32_t)mask))

// clear bits in register
#define clear_bits(address, mask) ((address) &= ~((uint32_t)mask))

// xor bits in register
#define xor_bits(address, mask) ((address) ^= ((uint32_t)mask))

/** write bits to a group of adjacent bits in register
 * @param address register to manipulate
 * @param value new value
 * @param mask bit mask
 * @param lsb offset to the least significant bit in a group
 *  e.g. write_masked(PORTB, 0b110, 0b111, PB2) sets PB4 and PB3, clears PB2 in PORTB
*/
#define write_masked(address, value, mask, lsb) ((address) = ((address) & (~(mask))) | ((value) << (lsb)))

// tests if a bit is set
#define bit_is_set(address, mask) ((address) & (mask))

// tests if a bit is clear
#define bit_is_clear(address, mask) (!((address) & (mask)))

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#define force_inline inline __attribute__((always_inline))

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _RP2040_H_ */
