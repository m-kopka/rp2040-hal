#ifndef _REG_VREG_H_
#define _REG_VREG_H_

/*
 *  Core supply regulator and chip reset register definitions
 *  Martin Kopka 2024
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t VREG;         // Voltage regulator control and status
    reg_t BOD;          // Brown-out detection control
    reg_t CHIP_RESET;   // Chip reset control and status

} VREG_t;

#define VREG ((RESETS_t*)VREG_AND_CHIP_RESET_BASES_BASE)       // VREG_AND_CHIP_RESET register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

#define VREG_VREG_ROK           _BIT(12)    // regulation status 0=not in regulation, 1=in regulation

/* output voltage select 
0000 to 0101 - 0.80V
0110 - 0.85V
0111 - 0.90V
1000 - 0.95V
1001 - 1.00V
1010 - 1.05V
1011 - 1.10V (default)
1100 - 1.15V
1101 - 1.20V
1110 - 1.25V
1111 - 1.30V */
#define VREG_VREG_VSEL3         _BIT(7)
#define VREG_VREG_VSEL2         _BIT(6)
#define VREG_VREG_VSEL1         _BIT(5)
#define VREG_VREG_VSEL0         _BIT(4)
#define VREG_VREG_VSEL_LSB      4
#define VREG_VREG_VSEL_MASK     (VREG_VREG_VSEL3 | VREG_VREG_VSEL2 | VREG_VREG_VSEL1 | VREG_VREG_VSEL0)
#define VREG_VREG_VSEL_VAL_0V80 (0)
#define VREG_VREG_VSEL_VAL_0V85 (VREG_VREG_VSEL2 | VREG_VREG_VSEL1)
#define VREG_VREG_VSEL_VAL_0V90 (VREG_VREG_VSEL2 | VREG_VREG_VSEL1 | VREG_VREG_VSEL0)
#define VREG_VREG_VSEL_VAL_0V95 (VREG_VREG_VSEL3)
#define VREG_VREG_VSEL_VAL_1V00 (VREG_VREG_VSEL3 | VREG_VREG_VSEL0)
#define VREG_VREG_VSEL_VAL_1V05 (VREG_VREG_VSEL3 | VREG_VREG_VSEL1)
#define VREG_VREG_VSEL_VAL_1V10 (VREG_VREG_VSEL3 | VREG_VREG_VSEL1 | VREG_VREG_VSEL0)
#define VREG_VREG_VSEL_VAL_1V15 (VREG_VREG_VSEL3 | VREG_VREG_VSEL2)
#define VREG_VREG_VSEL_VAL_1V20 (VREG_VREG_VSEL3 | VREG_VREG_VSEL2 | VREG_VREG_VSEL0)
#define VREG_VREG_VSEL_VAL_1V25 (VREG_VREG_VSEL3 | VREG_VREG_VSEL2 | VREG_VREG_VSEL1)
#define VREG_VREG_VSEL_VAL_1V30 (VREG_VREG_VSEL3 | VREG_VREG_VSEL2 | VREG_VREG_VSEL1 | VREG_VREG_VSEL0)

#define VREG_VREG_HIZ           _BIT(1)     // high impedance mode select 0=not in high impedance mode, 1=in high impedance mode
#define VREG_VREG_EN            _BIT(0)     // enable 0=not enabled, 1=enabled

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

/* threshold select
0000 - 0.473V
0001 - 0.516V
0010 - 0.559V
0011 - 0.602V
0100 - 0.645V
0101 - 0.688V
0110 - 0.731V
0111 - 0.774V
1000 - 0.817V
1001 - 0.860V (default)
1010 - 0.903V
1011 - 0.946V
1100 - 0.989V
1101 - 1.032V
1110 - 1.075V
1111 - 1.118V*/
#define VREG_BOD_VSEL3          _BIT(7)
#define VREG_BOD_VSEL2          _BIT(6)
#define VREG_BOD_VSEL1          _BIT(5)
#define VREG_BOD_VSEL0          _BIT(4)
#define VREG_BOD_VSEL_LSB       4
#define VREG_BOD_VSEL_MASK      (VREG_BOD_VSEL3 | VREG_BOD_VSEL2 | VREG_BOD_VSEL1 | VREG_BOD_VSEL0)
#define VREG_BOD_VSEL_VAL_0V473 (0)
#define VREG_BOD_VSEL_VAL_0V516 (VREG_BOD_VSEL0)
#define VREG_BOD_VSEL_VAL_0V559 (VREG_BOD_VSEL1)
#define VREG_BOD_VSEL_VAL_0V602 (VREG_BOD_VSEL1 | VREG_BOD_VSEL0)
#define VREG_BOD_VSEL_VAL_0V645 (VREG_BOD_VSEL2 | )
#define VREG_BOD_VSEL_VAL_0V688 (VREG_BOD_VSEL2 | VREG_BOD_VSEL0)
#define VREG_BOD_VSEL_VAL_0V731 (VREG_BOD_VSEL2 | VREG_BOD_VSEL1)
#define VREG_BOD_VSEL_VAL_0V774 (VREG_BOD_VSEL2 | VREG_BOD_VSEL1 | VREG_BOD_VSEL0)
#define VREG_BOD_VSEL_VAL_0V817 (VREG_BOD_VSEL3)
#define VREG_BOD_VSEL_VAL_0V860 (VREG_BOD_VSEL3 | VREG_BOD_VSEL0)
#define VREG_BOD_VSEL_VAL_0V903 (VREG_BOD_VSEL3 | VREG_BOD_VSEL1)
#define VREG_BOD_VSEL_VAL_0V946 (VREG_BOD_VSEL3 | VREG_BOD_VSEL1 | VREG_BOD_VSEL0)
#define VREG_BOD_VSEL_VAL_0V989 (VREG_BOD_VSEL3 | VREG_BOD_VSEL2 | )
#define VREG_BOD_VSEL_VAL_1V032 (VREG_BOD_VSEL3 | VREG_BOD_VSEL2 | VREG_BOD_VSEL0)
#define VREG_BOD_VSEL_VAL_1V075 (VREG_BOD_VSEL3 | VREG_BOD_VSEL2 | VREG_BOD_VSEL1)
#define VREG_BOD_VSEL_VAL_1V118 (VREG_BOD_VSEL3 | VREG_BOD_VSEL2 | VREG_BOD_VSEL1 | VREG_BOD_VSEL0)

#define VREG_BOD_EN             _BIT(0)     // enable 0=not enabled, 1=enabled

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#define VREG_CHIP_RESET_PSM_RESTART_F_LAG   _BIT(24)    // This is set by psm_restart from the debugger. Its purpose is to branch bootcode to a safe mode when the debugger has issued a psm_restart in order to recover from a boot lock-up. In the safe mode the debugger can repair the boot code, clear this flag then reboot the processor.
#define VREG_CHIP_HAD_PSM_RESTART           _BIT(20)    // Last reset was from the debug port
#define VREG_CHIP_HAD_RUN                   _BIT(16)    // Last reset was from the RUN pin
#define VREG_CHIP_HAD_POR                   _BIT( 8)    // Last reset was from the power-on reset or brown-out detection blocks

//================================================================================================================================================================

#endif /* _REG_VREG_H_ */