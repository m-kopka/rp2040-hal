#ifndef _REG_CLOCKS_H_
#define _REG_CLOCKS_H_

/*
 *  RP2040 Clock register defintions
 *  Martin Kopka 2022
 * 
 *  The clocks block provides independent clocks to on-chip and external components. 
 *  It takes inputs from a variety of clock sources allowing the user to trade off performance against cost, board area and power consumption.
 *  From these sources it uses multiple clock generators to provide the required clocks.
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#define CLK_COUNT 10

enum clock_instance {

    clk_gpout0,     // GPIO Muxing 0. Clock output to GPIO. Can be used to clock external devices or debug on chip clocks with a logic analyser or oscilloscope.
    clk_gpout1,     // GPIO Muxing 1. Clock output to GPIO. Can be used to clock external devices or debug on chip clocks with a logic analyser or oscilloscope.
    clk_gpout2,     // GPIO Muxing 2. Clock output to GPIO. Can be used to clock external devices or debug on chip clocks with a logic analyser or oscilloscope.
    clk_gpout3,     // GPIO Muxing 3. Clock output to GPIO. Can be used to clock external devices or debug on chip clocks with a logic analyser or oscilloscope.
    clk_ref,        // Watchdog and timers reference clock. Reference clock that is always running unless in DORMANT mode. Runs from Ring Oscillator (ROSC) at power-up but can be switched to Crystal Oscillator (XOSC) for more accuracy. (6 - 12MHz)
    clk_sys,        // Processors, bus fabric, memory, memory mapped registers. System clock that is always running unless in DORMANT mode. Runs from clk_ref at power-up but is typically switched to a PLL. (125MHz)
    clk_peri,       // Peripheral clock for UART and SPI. Peripheral clock. Typically runs from clk_sys but allows peripherals to run at a consistent speed if clk_sys is changed by software. (12 - 125MHZ)
    clk_usb,        // USB clock. USB reference clock. Must be 48MHz.
    clk_adc,        // ADC clock. ADC reference clock. Must be 48MHz.
    clk_rtc         // RTC clock. RTC reference clock. The RTC divides this clock to generate a 1 second reference. (46875Hz)
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

typedef struct {

    reg_t CTRL;        // Clock control, can be changed on-the-fly (except for auxsrc)
    reg_t DIV;         // Clock divisor, can be changed on-the-fly
    reg_t SELECTED;    // Indicates which SRC is currently selected by the glitchless mux (one-hot).

} CLOCKS_CLOCK_t;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

typedef struct {

    reg_t CTRL;
    reg_t STATUS;

} CLOCKS_RESUS_t;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

typedef struct {

    reg_t REF_KHZ;     // Reference clock frequency in kHz
    reg_t MIN_KHZ;     // Minimum pass frequency in kHz. This is optional. Set to 0 if you are not using the pass/fail flags
    reg_t MAX_KHZ;     // Maximum pass frequency in kHz. This is optional. Set to 0x1ffffff if you are not using the pass/fail flags
    reg_t DELAY;       // Delays the start of frequency counting to allow the mux to settle Delay is measured in multiples of the reference clock period
    reg_t INTERVAL;    // The test interval is 0.98us * 2**interval, but let’s call it 1us * 2**interval
    reg_t SRC;         // Clock sent to frequency counter, set to 0 when not required Writing to this register initiates the frequency count
    reg_t STATUS;      // Frequency counter status
    reg_t RESULT;      // Result of frequency measurement, only valid when status_done=1

} CLOCKS_FC_t;

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

typedef struct {

    CLOCKS_CLOCK_t CLK[CLK_COUNT];
    CLOCKS_RESUS_t RESUS;
    CLOCKS_FC_t FC0;
    reg_t WAKE_EN0;        // enable clock in wake mode
    reg_t WAKE_EN1;        // enable clock in wake mode
    reg_t SLEEP_EN0;       // enable clock in sleep mode
    reg_t SLEEP_EN1;       // enable clock in sleep mode
    reg_t ENABLED0;        // indicates the state of the clock enable
    reg_t ENABLED1;        // indicates the state of the clock enable
    reg_t INTR;            // Raw Interrupts
    reg_t INTE;            // Interrupt Enable
    reg_t INTF;            // Interrupt Force
    reg_t INTS;            // Interrupt status after masking & forcing

} CLOCKS_t;

#define CLOCKS ((CLOCKS_t*)CLOCKS_BASE)       // CLOCKS register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// CLOCKS: CLK_CTRL register
// Clock control, can be changed on-the-fly (except for auxsrc)
#define CLOCKS_CLK_CTRL_NUDGE           _BIT(20)        // An edge on this signal shifts the phase of the output by 1 cycle of the input clock. This can be done at any time

// This delays the enable signal by up to 3 cycles of the input clock. This must be set before the clock is enabled to have any effect
#define CLK_CTRL_PHASE1         _BIT(17)
#define CLK_CTRL_PHASE0         _BIT(16)
#define CLK_CTRL_PHASE_LSB      16
#define CLK_CTRL_PHASE_MASK     (CLK_CTRL_PHASE1 | CLK_CTRL_PHASE0)

#define CLK_CTRL_DC50           _BIT(12)        // Enables duty cycle correction for odd divisors
#define CLK_CTRL_ENABLE         _BIT(11)        // Starts and stops the clock generator cleanly
#define CLK_CTRL_KILL           _BIT(10)        // Asynchronously kills the clock generator

// Selects the auxiliary clock source, will glitch when switching
#define CLK_CTRL_AUXSRC3        _BIT(8)
#define CLK_CTRL_AUXSRC2        _BIT(7)
#define CLK_CTRL_AUXSRC1        _BIT(6)
#define CLK_CTRL_AUXSRC0        _BIT(5)
#define CLK_CTRL_AUXSRC_LSB     5
#define CLK_CTRL_AUXSRC_MASK    0x000001e0
#define CLK_CTRL_AUXSRC_VAL_CLKSRC_PLL_SYS  (0x00 << CLK_CTRL_AUXSRC_LSB)
#define CLK_CTRL_AUXSRC_VAL_CLKSRC_GPIN0    (0x01 << CLK_CTRL_AUXSRC_LSB)
#define CLK_CTRL_AUXSRC_VAL_CLKSRC_GPIN1    (0x02 << CLK_CTRL_AUXSRC_LSB)
#define CLK_CTRL_AUXSRC_VAL_CLKSRC_PLL_USB  (0x03 << CLK_CTRL_AUXSRC_LSB)
#define CLK_CTRL_AUXSRC_VAL_ROSC_CLKSRC_PH  (0x04 << CLK_CTRL_AUXSRC_LSB)
#define CLK_CTRL_AUXSRC_VAL_XOSC_CLKSRC     (0x05 << CLK_CTRL_AUXSRC_LSB)
#define CLK_CTRL_AUXSRC_VAL_CLK_SYS         (0x06 << CLK_CTRL_AUXSRC_LSB)
#define CLK_CTRL_AUXSRC_VAL_CLK_USB         (0x07 << CLK_CTRL_AUXSRC_LSB)
#define CLK_CTRL_AUXSRC_VAL_CLK_ADC         (0x08 << CLK_CTRL_AUXSRC_LSB)
#define CLK_CTRL_AUXSRC_VAL_CLK_RTC         (0x09 << CLK_CTRL_AUXSRC_LSB)
#define CLK_CTRL_AUXSRC_VAL_CLK_REF         (0x0a << CLK_CTRL_AUXSRC_LSB)

// Selects the clock source glitchlessly, can be changed on-the-fly
#define CLK_CTRL_SRC1           _BIT(1)
#define CLK_CTRL_SRC0           _BIT(0)
#define CLK_CTRL_SRC_LSB        0
#define CLK_CTRL_SRC_MASK       (CLK_CTRL_SRC1 | CLK_CTRL_SRC0)
#define CLK_CTRL_SRC_VAL_ROSC_CLKSRC_PH     (0x0 << CLK_CTRL_SRC_LSB)
#define CLK_CTRL_SRC_VAL_CLKSRC_CLK_REF_AUX (0x1 << CLK_CTRL_SRC_LSB)
#define CLK_CTRL_SRC_VAL_XOSC_CLKSRC        (0x2 << CLK_CTRL_SRC_LSB)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// CLOCKS: CLK_DIV register
// Clock divisor, can be changed on-the-fly

// Integer component of the divisor, 0 → divide by 2^16
#define CLK_DIV_INT_LSB       8
#define CLK_DIV_INT_MASK      0xffffff00

// Fractional component of the divisor
#define CLK_DIV_FRAC_LSB       0
#define CLK_DIV_FRAC_MASK      0x000000ff

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// CLOCKS: RESUS_CTRL register
#define CLK_SYS_RESUS_CTRL_CLEAR    _BIT(16)        // For clearing the resus after the fault that triggered it has been corrected
#define CLK_SYS_RESUS_CTRL_FRCE     _BIT(12)        // Force a resus, for test purposes only
#define CLK_SYS_RESUS_CTRL_ENABLE   _BIT( 8)        // Enable resus

// This is expressed as a number of clk_ref cycles and must be >= 2x clk_ref_freq/min_clk_tst_freq
#define CLK_SYS_RESUS_CTRL_TIMEOUT_LSB      0
#define CLK_SYS_RESUS_CTRL_TIMEOUT_MASK     0x000000ff

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// CLOCKS: RESUS_STATUS register
#define CLK_SYS_RESUS_STATUS_RESUSSED   _BIT(0)     // Clock has been resuscitated, correct the error then send ctrl_clear = 1

//================================================================================================================================================================

// CLOCKS: FC0_SRC register
// Clock sent to frequency counter, set to 0 when not required Writing to this register initiates the frequency count
#define FC0_SRC_VAL_NULL                        (0x00)
#define FC0_SRC_VAL_PLL_SYS_CLKSRC_PRIMARY      (0x01)
#define FC0_SRC_VAL_PLL_USB_CLKSRC_PRIMARY      (0x02)
#define FC0_SRC_VAL_ROSC_CLKSRC                 (0x03)
#define FC0_SRC_VAL_ROSC_CLKSRC_PH              (0x04)
#define FC0_SRC_VAL_XOSC_CLKSRC                 (0x05)
#define FC0_SRC_VAL_CLKSRC_GPIN0                (0x06)
#define FC0_SRC_VAL_CLKSRC_GPIN1                (0x07)
#define FC0_SRC_VAL_CLK_REF                     (0x08)
#define FC0_SRC_VAL_CLK_SYS                     (0x09)
#define FC0_SRC_VAL_CLK_PERI                    (0x0a)
#define FC0_SRC_VAL_CLK_USB                     (0x0b)
#define FC0_SRC_VAL_CLK_ADC                     (0x0c)
#define FC0_SRC_VAL_CLK_RTC                     (0x0d)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// CLOCKS: FC0_STATUS register
// Frequency counter status
#define FC0_STATUS_DIED         _BIT(28)        // Test clock stopped during test
#define FC0_STATUS_FAST         _BIT(24)        // Test clock faster than expected, only valid when status_done=1
#define FC0_STATUS_SLOW         _BIT(20)        // Test clock slower than expected, only valid when status_done=1
#define FC0_STATUS_FAIL         _BIT(16)        // Test failed
#define FC0_STATUS_WAITING      _BIT(12)        // Waiting for test clock to start
#define FC0_STATUS_RUNNING      _BIT( 8)        // Test running
#define FC0_STATUS_DONE         _BIT( 4)        // Test complete
#define FC0_STATUS_PASS         _BIT( 0)        // Test passed

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// CLOCKS: FC0_RESULT register
// Result of frequency measurement, only valid when status_done=1
#define FC0_RESULT_KHZ_LSB      5
#define FC0_RESULT_KHZ_MASK     0x3fffffe0


#define FC0_RESULT_FRAC_LSB     0
#define FC0_RESULT_FRAC_MASK    0x0000001f

//================================================================================================================================================================

#define EN0_CLK_SYS_SRAM3               _BIT(31)
#define EN0_CLK_SYS_SRAM2               _BIT(30)
#define EN0_CLK_SYS_SRAM1               _BIT(29)
#define EN0_CLK_SYS_SRAM0               _BIT(28)
#define EN0_CLK_SYS_SPI1                _BIT(27)
#define EN0_CLK_PERI_SPI1               _BIT(26)
#define EN0_CLK_SYS_SPI0                _BIT(25)
#define EN0_CLK_PERI_SPI0               _BIT(24)
#define EN0_CLK_SYS_SIO                 _BIT(23)
#define EN0_CLK_SYS_RTC                 _BIT(22)
#define EN0_CLK_RTC_RTC                 _BIT(21)
#define EN0_CLK_SYS_ROSC                _BIT(20)
#define EN0_CLK_SYS_ROM                 _BIT(19)
#define EN0_CLK_SYS_RESETS              _BIT(18)
#define EN0_CLK_SYS_PWM                 _BIT(17)
#define EN0_CLK_SYS_PSM                 _BIT(16)
#define EN0_CLK_SYS_PLL_USB             _BIT(15)
#define EN0_CLK_SYS_PLL_SYS             _BIT(14)
#define EN0_CLK_SYS_PIO1                _BIT(13)
#define EN0_CLK_SYS_PIO0                _BIT(12)
#define EN0_CLK_SYS_PADS                _BIT(11)
#define EN0_CLK_SYS_VREG_AND_CHIP_RESET _BIT(10)
#define EN0_CLK_SYS_JTAG                _BIT( 9)
#define EN0_CLK_SYS_IO                  _BIT( 8)
#define EN0_CLK_SYS_I2C1                _BIT( 7)
#define EN0_CLK_SYS_I2C0                _BIT( 6)
#define EN0_CLK_SYS_DMA                 _BIT( 5)
#define EN0_CLK_SYS_BUSFABRIC           _BIT( 4)
#define EN0_CLK_SYS_BUSCTRL             _BIT( 3)
#define EN0_CLK_SYS_ADC                 _BIT( 2)
#define EN0_CLK_ADC_ADC                 _BIT( 1)
#define EN0_CLK_SYS_CLOCKS              _BIT( 0)

#define EN1_CLK_SYS_XOSC                _BIT(14)
#define EN1_CLK_SYS_XIP                 _BIT(13)
#define EN1_CLK_SYS_WATCHDOG            _BIT(12)
#define EN1_CLK_USB_USBCTRL             _BIT(11)
#define EN1_CLK_SYS_USBCTRL             _BIT(10)
#define EN1_CLK_SYS_UART1               _BIT( 9)
#define EN1_CLK_PERI_UART1              _BIT( 8)
#define EN1_CLK_SYS_UART0               _BIT( 7)
#define EN1_CLK_PERI_UART0              _BIT( 6)
#define EN1_CLK_SYS_TIMER               _BIT( 5)
#define EN1_CLK_SYS_TBMAN               _BIT( 4)
#define EN1_CLK_SYS_SYSINFO             _BIT( 3)
#define EN1_CLK_SYS_SYSCFG              _BIT( 2)
#define EN1_CLK_SYS_SRAM5               _BIT( 1)
#define EN1_CLK_SYS_SRAM4               _BIT( 0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#define INT_CLK_SYS_RESUS       _BIT(0)

//================================================================================================================================================================

#endif /* _REG_CLOCKS_H_ */