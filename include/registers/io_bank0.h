#ifndef _REG_IO_BANK0_H_
#define _REG_IO_BANK0_H_

/*
 *  RP2040 IO_Bank0 register definitions
 *  Martin Kopka 2022
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#define IO_BANK0_GPIO_COUNT 30

typedef struct {

    reg_t STATUS;      // GPIO status
    reg_t CTRL;        // GPIO control including function select and overrides.

} IO_BANK0_GPIO_t;

typedef struct {

    reg_t INTE[4];     // Interrupt Enable
    reg_t INTF[4];     // Interrupt Force
    reg_t INTS[4];     // Interrupt status after masking & forcing

} IO_BANK0_INT_t;

typedef struct {

    IO_BANK0_GPIO_t GPIO[IO_BANK0_GPIO_COUNT];      // GPIO status and control
    reg_t INTR[4];                             // Raw Interrupts
    IO_BANK0_INT_t PROC0;                           // Interrupts for proc0
    IO_BANK0_INT_t PROC1;                           // Interrupts for proc1
    IO_BANK0_INT_t DORMANT;                         // Interrupts for dormant_wake

} IO_BANK0_t;

#define IO_BANK0 ((IO_BANK0_t*)IO_BANK0_BASE)       // IO_BANK0 register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// IO_BANK0: GPIO_STATUS register
// GPIO status
#define IO_BANK0_GPIO_STATUS_IRQTOPROC       _BIT(26)        // interrupt to processors, after override is applied
#define IO_BANK0_GPIO_STATUS_IRQFROMPAD      _BIT(24)        // interrupt from pad before override is applied
#define IO_BANK0_GPIO_STATUS_INTOPERI        _BIT(19)        // input signal to peripheral, after override is applied
#define IO_BANK0_GPIO_STATUS_INTFROMPAD      _BIT(17)        // input signal from pad, before override is applied
#define IO_BANK0_GPIO_STATUS_OETOPAD         _BIT(13)        // output enable to pad after register override is applied
#define IO_BANK0_GPIO_STATUS_OEFROMPERI      _BIT(12)        // output enable from selected peripheral, before register override is applied
#define IO_BANK0_GPIO_STATUS_OUTTOPAD        _BIT( 9)        // output signal to pad after register override is applied
#define IO_BANK0_GPIO_STATUS_OUTFROMPERI     _BIT( 8)        // output signal from selected peripheral, before register override is applied

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// IO_BANK0: GPIO_CTRL register
// GPIO control including function select and overrides.
#define IO_BANK0_GPIO_CTRL_IRQOVER_LSB      28
#define IO_BANK0_GPIO_CTRL_IRQOVER_MASK     0x30000000

#define IO_BANK0_GPIO_CTRL_INOVER_LSB       16
#define IO_BANK0_GPIO_CTRL_INOVER_MASK      0x00030000

#define IO_BANK0_GPIO_CTRL_OEOVER_LSB       12
#define IO_BANK0_GPIO_CTRL_OEOVER_MASK      0x00003000

#define IO_BANK0_GPIO_CTRL_OUTOVER_LSB      8
#define IO_BANK0_GPIO_CTRL_OUTOVER_MASK     0x00000300

#define IO_BANK0_GPIO_CTRL_FUNCSEL_LSB      0
#define IO_BANK0_GPIO_CTRL_FUNCSEL_MASK     0x0000001f
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_XIP  0x00
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_SPI  0x01
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_UART 0x02
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_I2C  0x03
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_PWM  0x04
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_SIO  0x05
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_PIO0 0x06
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_PIO1 0x07
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_GPCK 0x08
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_USB  0x09
#define IO_BANK0_GPIO_CTRL_FUNCSEL_VAL_NULL 0x1f

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#define IO_BANK0_0_GPIO7_EDGE_HIGH       _BIT(31)
#define IO_BANK0_0_GPIO7_EDGE_LOW        _BIT(30)
#define IO_BANK0_0_GPIO7_LEVEL_HIGH      _BIT(29)
#define IO_BANK0_0_GPIO7_LEVEL_LOW       _BIT(28)

#define IO_BANK0_0_GPIO6_EDGE_HIGH       _BIT(27)
#define IO_BANK0_0_GPIO6_EDGE_LOW        _BIT(26)
#define IO_BANK0_0_GPIO6_LEVEL_HIGH      _BIT(25)
#define IO_BANK0_0_GPIO6_LEVEL_LOW       _BIT(24)

#define IO_BANK0_0_GPIO5_EDGE_HIGH       _BIT(23)
#define IO_BANK0_0_GPIO5_EDGE_LOW        _BIT(22)
#define IO_BANK0_0_GPIO5_LEVEL_HIGH      _BIT(21)
#define IO_BANK0_0_GPIO5_LEVEL_LOW       _BIT(20)

#define IO_BANK0_0_GPIO4_EDGE_HIGH       _BIT(19)
#define IO_BANK0_0_GPIO4_EDGE_LOW        _BIT(18)
#define IO_BANK0_0_GPIO4_LEVEL_HIGH      _BIT(17)
#define IO_BANK0_0_GPIO4_LEVEL_LOW       _BIT(16)

#define IO_BANK0_0_GPIO3_EDGE_HIGH       _BIT(15)
#define IO_BANK0_0_GPIO3_EDGE_LOW        _BIT(14)
#define IO_BANK0_0_GPIO3_LEVEL_HIGH      _BIT(13)
#define IO_BANK0_0_GPIO3_LEVEL_LOW       _BIT(12)

#define IO_BANK0_0_GPIO2_EDGE_HIGH       _BIT(11)
#define IO_BANK0_0_GPIO2_EDGE_LOW        _BIT(10)
#define IO_BANK0_0_GPIO2_LEVEL_HIGH      _BIT( 9)
#define IO_BANK0_0_GPIO2_LEVEL_LOW       _BIT( 8)

#define IO_BANK0_0_GPIO1_EDGE_HIGH       _BIT( 7)
#define IO_BANK0_0_GPIO1_EDGE_LOW        _BIT( 6)
#define IO_BANK0_0_GPIO1_LEVEL_HIGH      _BIT( 5)
#define IO_BANK0_0_GPIO1_LEVEL_LOW       _BIT( 4)

#define IO_BANK0_0_GPIO0_EDGE_HIGH       _BIT( 3)
#define IO_BANK0_0_GPIO0_EDGE_LOW        _BIT( 2)
#define IO_BANK0_0_GPIO0_LEVEL_HIGH      _BIT( 1)
#define IO_BANK0_0_GPIO0_LEVEL_LOW       _BIT( 0)

#define IO_BANK0_1_GPIO15_EDGE_HIGH      _BIT(31)
#define IO_BANK0_1_GPIO15_EDGE_LOW       _BIT(30)
#define IO_BANK0_1_GPIO15_LEVEL_HIGH     _BIT(29)
#define IO_BANK0_1_GPIO15_LEVEL_LOW      _BIT(28)

#define IO_BANK0_1_GPIO14_EDGE_HIGH      _BIT(27)
#define IO_BANK0_1_GPIO14_EDGE_LOW       _BIT(26)
#define IO_BANK0_1_GPIO14_LEVEL_HIGH     _BIT(25)
#define IO_BANK0_1_GPIO14_LEVEL_LOW      _BIT(24)

#define IO_BANK0_1_GPIO13_EDGE_HIGH      _BIT(23)
#define IO_BANK0_1_GPIO13_EDGE_LOW       _BIT(22)
#define IO_BANK0_1_GPIO13_LEVEL_HIGH     _BIT(21)
#define IO_BANK0_1_GPIO13_LEVEL_LOW      _BIT(20)

#define IO_BANK0_1_GPIO12_EDGE_HIGH      _BIT(19)
#define IO_BANK0_1_GPIO12_EDGE_LOW       _BIT(18)
#define IO_BANK0_1_GPIO12_LEVEL_HIGH     _BIT(17)
#define IO_BANK0_1_GPIO12_LEVEL_LOW      _BIT(16)

#define IO_BANK0_1_GPIO11_EDGE_HIGH      _BIT(15)
#define IO_BANK0_1_GPIO11_EDGE_LOW       _BIT(14)
#define IO_BANK0_1_GPIO11_LEVEL_HIGH     _BIT(13)
#define IO_BANK0_1_GPIO11_LEVEL_LOW      _BIT(12)

#define IO_BANK0_1_GPIO10_EDGE_HIGH      _BIT(11)
#define IO_BANK0_1_GPIO10_EDGE_LOW       _BIT(10)
#define IO_BANK0_1_GPIO10_LEVEL_HIGH     _BIT( 9)
#define IO_BANK0_1_GPIO10_LEVEL_LOW      _BIT( 8)

#define IO_BANK0_1_GPIO9_EDGE_HIGH       _BIT( 7)
#define IO_BANK0_1_GPIO9_EDGE_LOW        _BIT( 6)
#define IO_BANK0_1_GPIO9_LEVEL_HIGH      _BIT( 5)
#define IO_BANK0_1_GPIO9_LEVEL_LOW       _BIT( 4)

#define IO_BANK0_1_GPIO8_EDGE_HIGH       _BIT( 3)
#define IO_BANK0_1_GPIO8_EDGE_LOW        _BIT( 2)
#define IO_BANK0_1_GPIO8_LEVEL_HIGH      _BIT( 1)
#define IO_BANK0_1_GPIO8_LEVEL_LOW       _BIT( 0)

#define IO_BANK0_2_GPIO23_EDGE_HIGH      _BIT(31)
#define IO_BANK0_2_GPIO23_EDGE_LOW       _BIT(30)
#define IO_BANK0_2_GPIO23_LEVEL_HIGH     _BIT(29)
#define IO_BANK0_2_GPIO23_LEVEL_LOW      _BIT(28)

#define IO_BANK0_2_GPIO22_EDGE_HIGH      _BIT(27)
#define IO_BANK0_2_GPIO22_EDGE_LOW       _BIT(26)
#define IO_BANK0_2_GPIO22_LEVEL_HIGH     _BIT(25)
#define IO_BANK0_2_GPIO22_LEVEL_LOW      _BIT(24)

#define IO_BANK0_2_GPIO21_EDGE_HIGH      _BIT(23)
#define IO_BANK0_2_GPIO21_EDGE_LOW       _BIT(22)
#define IO_BANK0_2_GPIO21_LEVEL_HIGH     _BIT(21)
#define IO_BANK0_2_GPIO21_LEVEL_LOW      _BIT(20)

#define IO_BANK0_2_GPIO20_EDGE_HIGH      _BIT(19)
#define IO_BANK0_2_GPIO20_EDGE_LOW       _BIT(18)
#define IO_BANK0_2_GPIO20_LEVEL_HIGH     _BIT(17)
#define IO_BANK0_2_GPIO20_LEVEL_LOW      _BIT(16)

#define IO_BANK0_2_GPIO19_EDGE_HIGH      _BIT(15)
#define IO_BANK0_2_GPIO19_EDGE_LOW       _BIT(14)
#define IO_BANK0_2_GPIO19_LEVEL_HIGH     _BIT(13)
#define IO_BANK0_2_GPIO19_LEVEL_LOW      _BIT(12)

#define IO_BANK0_2_GPIO18_EDGE_HIGH      _BIT(11)
#define IO_BANK0_2_GPIO18_EDGE_LOW       _BIT(10)
#define IO_BANK0_2_GPIO18_LEVEL_HIGH     _BIT( 9)
#define IO_BANK0_2_GPIO18_LEVEL_LOW      _BIT( 8)

#define IO_BANK0_2_GPIO17_EDGE_HIGH      _BIT( 7)
#define IO_BANK0_2_GPIO17_EDGE_LOW       _BIT( 6)
#define IO_BANK0_2_GPIO17_LEVEL_HIGH     _BIT( 5)
#define IO_BANK0_2_GPIO17_LEVEL_LOW      _BIT( 4)

#define IO_BANK0_2_GPIO16_EDGE_HIGH      _BIT( 3)
#define IO_BANK0_2_GPIO16_EDGE_LOW       _BIT( 2)
#define IO_BANK0_2_GPIO16_LEVEL_HIGH     _BIT( 1)
#define IO_BANK0_2_GPIO16_LEVEL_LOW      _BIT( 0)

#define IO_BANK0_3_GPIO29_EDGE_HIGH      _BIT(23)
#define IO_BANK0_3_GPIO29_EDGE_LOW       _BIT(22)
#define IO_BANK0_3_GPIO29_LEVEL_HIGH     _BIT(21)
#define IO_BANK0_3_GPIO29_LEVEL_LOW      _BIT(20)

#define IO_BANK0_3_GPIO28_EDGE_HIGH      _BIT(19)
#define IO_BANK0_3_GPIO28_EDGE_LOW       _BIT(18)
#define IO_BANK0_3_GPIO28_LEVEL_HIGH     _BIT(17)
#define IO_BANK0_3_GPIO28_LEVEL_LOW      _BIT(16)

#define IO_BANK0_3_GPIO27_EDGE_HIGH      _BIT(15)
#define IO_BANK0_3_GPIO27_EDGE_LOW       _BIT(14)
#define IO_BANK0_3_GPIO27_LEVEL_HIGH     _BIT(13)
#define IO_BANK0_3_GPIO27_LEVEL_LOW      _BIT(12)

#define IO_BANK0_3_GPIO26_EDGE_HIGH      _BIT(11)
#define IO_BANK0_3_GPIO26_EDGE_LOW       _BIT(10)
#define IO_BANK0_3_GPIO26_LEVEL_HIGH     _BIT( 9)
#define IO_BANK0_3_GPIO26_LEVEL_LOW      _BIT( 8)

#define IO_BANK0_3_GPIO25_EDGE_HIGH      _BIT( 7)
#define IO_BANK0_3_GPIO25_EDGE_LOW       _BIT( 6)
#define IO_BANK0_3_GPIO25_LEVEL_HIGH     _BIT( 5)
#define IO_BANK0_3_GPIO25_LEVEL_LOW      _BIT( 4)

#define IO_BANK0_3_GPIO24_EDGE_HIGH      _BIT( 3)
#define IO_BANK0_3_GPIO24_EDGE_LOW       _BIT( 2)
#define IO_BANK0_3_GPIO24_LEVEL_HIGH     _BIT( 1)
#define IO_BANK0_3_GPIO24_LEVEL_LOW      _BIT( 0)

//================================================================================================================================================================

#endif /* _REG_IO_BANK0_H_ */