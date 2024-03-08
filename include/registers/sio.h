#ifndef _REG_SIO_H_
#define _REG_SIO_H_

/*
 *  RP2040 Single-cycle IO block register definitions
 *  Martin Kopka 2022
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// interpolator instances
typedef struct {

    reg_t ACCUM0;              // Read/write access to accumulator 0
    reg_t ACCUM1;              // Read/write access to accumulator 1
    reg_t BASE0;               // Read/write access to BASE0 register.
    reg_t BASE1;               // Read/write access to BASE1 register.
    reg_t BASE2;               // Read/write access to BASE2 register.
    reg_t POP_LANE0;           // Read LANE0 result, and simultaneously write lane results to both accumulators (POP).
    reg_t POP_LANE1;           // Read LANE1 result, and simultaneously write lane results to both accumulators (POP).
    reg_t POP_FULL;            // Read FULL result, and simultaneously write lane results to both accumulators (POP).
    reg_t PEEK_LANE0;          // Read LANE0 result, without altering any internal state (PEEK).
    reg_t PEEK_LANE1;          // Read LANE1 result, without altering any internal state (PEEK).
    reg_t PEEK_FULL;           // Read FULL result, without altering any internal state (PEEK)
    reg_t CTRL_LANE0;          // Control register for lane 0
    reg_t CTRL_LANE1;          // Control register for lane 1
    reg_t ACCUM0_ADD;          // Values written here are atomically added to ACCUM0
    reg_t ACCUM1_ADD;          // Values written here are atomically added to ACCUM1
    reg_t BASE_1AND0;          // On write, the lower 16 bits go to BASE0, upper bits to BASE1 simultaneously.

} SIO_INTERP_t;

typedef struct {

    reg_t CPUID;               // Processor core identifier
    reg_t GPIO_IN;             // Input value for GPIO pins
    reg_t GPIO_HI_IN;          // Input value for QSPI pins

    uint32_t _RESERVED_0;

    reg_t GPIO_OUT;            // GPIO output value
    reg_t GPIO_OUT_SET;        // GPIO output value set
    reg_t GPIO_OUT_CLR;        // GPIO output value clear
    reg_t GPIO_OUT_XOR;        // GPIO output value XOR
    reg_t GPIO_OE;             // GPIO output enable
    reg_t GPIO_OE_SET;         // GPIO output enable set
    reg_t GPIO_OE_CLR;         // GPIO output enable clear
    reg_t GPIO_OE_XOR;         // GPIO output enable XOR

    reg_t GPIO_HI_OUT;         // QSPI output value
    reg_t GPIO_HI_OUT_SET;     // QSPI output value set
    reg_t GPIO_HI_OUT_CLR;     // QSPI output value clear
    reg_t GPIO_HI_OUT_XOR;     // QSPI output value XOR
    reg_t GPIO_HI_OE;          // QSPI output enable
    reg_t GPIO_HI_OE_SET;      // QSPI output enable set
    reg_t GPIO_HI_OE_CLR;      // QSPI output enable clear
    reg_t GPIO_HI_OE_XOR;      // QSPI output enable XOR

    reg_t FIFO_ST;             // Status register for inter-core FIFOs (mailboxes).
    reg_t FIFO_WR;             // Write access to this core’s TX FIFO
    reg_t FIFO_RD;             // Read access to this core’s RX FIFO

    reg_t SPINLOCK_ST;         // Spinlock state

    reg_t DIV_UDIVIDEND;       // Divider unsigned dividend
    reg_t DIV_UDIVISOR;        // Divider unsigned divisor
    reg_t DIV_SDIVIDEND;       // Divider signed dividend
    reg_t DIV_SDIVISOR;        // Divider signed divisor
    reg_t DIV_QUOTIENT;        // Divider result quotient
    reg_t DIV_REMAINDER;       // Divider result remainder
    reg_t DIV_CSR;             // Control and status register for divider.

    SIO_INTERP_t INTERP[2];

    reg_t SPINLOCK[32];        // Spinlock register

} SIO_t;

#define SIO ((SIO_t*)SIO_BASE)       // SIO register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// SIO: FIFO_ST register
// Status register for inter-core FIFOs (mailboxes).
#define SIO_FIFO_ST_ROE         _BIT(3)     // Sticky flag indicating the RX FIFO was read when empty. This read was ignored by the FIFO.
#define SIO_FIFO_ST_WOF         _BIT(2)     // Sticky flag indicating the TX FIFO was written when full. This write was ignored by the FIFO.
#define SIO_FIFO_ST_RDY         _BIT(1)     // Value is 1 if this core’s TX FIFO is not full (i.e. if FIFO_WR is ready for more data)
#define SIO_FIFO_ST_VLD         _BIT(0)     // Value is 1 if this core’s RX FIFO is not empty (i.e. if FIFO_RD is valid)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// SIO: DIV_CSR register
// Control and status register for divider.
#define SIO_DIV_CSR_DIRTY       _BIT(1)     // Changes to 1 when any register is written, and back to 0 when QUOTIENT is read.
#define SIO_DIV_CSR_READY       _BIT(0)     // Reads as 0 when a calculation is in progress, 1 otherwise.

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// SIO: INTERPx_CTRL_LANEx register
// Lane control register
#define SIO_INTERP_CTRL_LANE_OVERF              _BIT(25)
#define SIO_INTERP_CTRL_LANE_OVERF1             _BIT(24)
#define SIO_INTERP_CTRL_LANE_OVERF0             _BIT(23)
#define SIO_INTERP_CTRL_LANE_BLEND              _BIT(21)

#define SIO_INTERP_CTRL_LANE_FORCE_MSB_LSB      19
#define SIO_INTERP_CTRL_LANE_FORCE_MSB_MASK     0x00180000

#define SIO_INTERP_CTRL_LANE_ADD_RAW            _BIT(18)
#define SIO_INTERP_CTRL_LANE_CROSS_RESULT       _BIT(17)
#define SIO_INTERP_CTRL_LANE_CROSS_INPUT        _BIT(16)
#define SIO_INTERP_CTRL_LANE_SIGNED             _BIT(15)

#define SIO_INTERP_CTRL_LANE_MASK_MSB_LSB       10
#define SIO_INTERP_CTRL_LANE_MASK_MSB_MASK      0x00007c00

#define SIO_INTERP_CTRL_LANE_MASK_LSB_LSB       5
#define SIO_INTERP_CTRL_LANE_MASK_LSB_MASK      0x000003e0

#define SIO_INTERP_CTRL_LANE_SHIFT_LSB          0
#define SIO_INTERP_CTRL_LANE_SHIFT_MASK         0x0000001f

//================================================================================================================================================================

#endif /* _REG_SIO_H_ */