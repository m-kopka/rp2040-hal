#ifndef _REG_PADS_BANK0_H_
#define _REG_PADS_BANK0_H_

/*
 *  PADS_Bank0 register definitions
 *  Martin Kopka 2022
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#define IO_BANK0_GPIO_COUNT 30

typedef struct {

    reg_t VOLTAGE_SELECT;
    reg_t GPIO[IO_BANK0_GPIO_COUNT];
    reg_t SWCLK;
    reg_t SWD;

} PADS_BANK0_t;

#define PADS_BANK0 ((PADS_BANK0_t*)PADS_BANK0_BASE)       // PADS_BANK0 register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// PADS_BANK0: GPIOx registers
// Pad control register
#define PADS_BANK0_GPIO_OD      _BIT(7)     // Output disable. Has priority over output enable from peripherals
#define PADS_BANK0_GPIO_IE      _BIT(6)     // Input enable

// Drive strength
#define PADS_BANK0_GPIO_DRIVE_LSB           4 
#define PADS_BANK0_GPIO_DRIVE_MASK          0x000000030
#define PADS_BANK0_GPIO_DRIVE_VALUE_2MA     0x0
#define PADS_BANK0_GPIO_DRIVE_VALUE_4MA     0x1
#define PADS_BANK0_GPIO_DRIVE_VALUE_8MA     0x2
#define PADS_BANK0_GPIO_DRIVE_VALUE_12MA    0x3

#define PADS_BANK0_GPIO_PUE         _BIT(3)     // Pull up enable
#define PADS_BANK0_GPIO_PDE         _BIT(2)     // Pull down enable
#define PADS_BANK0_GPIO_SCHMITT     _BIT(1)     // Enable schmitt trigger
#define PADS_BANK0_GPIO_SLEWFAST    _BIT(0)     // Slew rate control. 1 = Fast, 0 = Slow

//================================================================================================================================================================

#endif /* _REG_PADS_BANK0_H_ */