#ifndef _REG_DMA_H_
#define _REG_DMA_H_

/*
 *  RP2040 DMA register definitions
 *  Martin Kopka 2026
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct DMA_channel_t {

    reg_t READ_ADDR;            // DMA Channel n Read Address pointer
    reg_t WRITE_ADDR;           // DMA Channel n Write Address pointer
    reg_t TRANS_COUNT;          // DMA Channel n Transfer Count
    reg_t CTRL_TRIG;            // DMA Channel n Control and Status
    reg_t AL1_CTRL;             // Alias for channel n CTRL register
    reg_t AL1_READ_ADDR;        // Alias for channel n READ_ADDR register
    reg_t AL1_WRITE_ADDR;       // Alias for channel n WRITE_ADDR register
    reg_t AL1_TRANS_COUNT_TRIG; // Alias for channel n TRANS_COUNT register. This is a trigger register (0xc). Writing a nonzero value will reload the channel counter and start the channel.
    reg_t AL2_CTRL;             // Alias for channel n CTRL register
    reg_t AL2_TRANS_COUNT;      // Alias for channel n TRANS_COUNT register
    reg_t AL2_READ_ADDR;        // Alias for channel n READ_ADDR register
    reg_t AL2_WRITE_ADDR_TRIG;  // Alias for channel n WRITE_ADDR register. This is a trigger register (0xc). Writing a nonzero value will reload the channel counter and start the channel.
    reg_t AL3_CTRL;             // Alias for channel n CTRL register
    reg_t AL3_WRITE_ADDR;       // Alias for channel n WRITE_ADDR register
    reg_t AL3_TRANS_COUNT;      // Alias for channel n TRANS_COUNT register
    reg_t AL3_READ_ADDR_TRIG;   // Alias for channel n READ_ADDR register. This is a trigger register (0xc). Writing a nonzero value will reload the channel counter and start the channel.

} DMA_channel_t;

typedef struct {

    DMA_channel_t CH[12];               // DMA Channel n register block
    DMA_channel_t _RESERVED_CH[4];      // reserved space for channels 12-15 not implemented in RP2040
    reg_t INTR;                         // Interrupt Status (raw)
    reg_t INTE0;                        // Interrupt Enables for IRQ 0
    reg_t INTF0;                        // Force Interrupts
    reg_t INTS0;                        // Interrupt Status for IRQ 0
    reg_t _RESERVED_0;
    reg_t INTE1;                        // Interrupt Enables for IRQ 1
    reg_t INTF1;                        // Force Interrupts for IRQ 1
    reg_t INTS1;                        // Interrupt Status (masked) for IRQ 1
    reg_t TIMER[4];                     // Pacing (X/Y) Fractional Timer
    reg_t MULTI_CHAN_TRIGGER;           // Trigger one or more channels simultaneously
    reg_t SNIFF_CTRL;                   // Sniffer Control
    reg_t SNIFF_DATA;                   // Data accumulator for sniff hardware
    reg_t _RESERVED_1;
    reg_t FIFO_LEVELS;                  // Debug RAF, WAF, TDF levels
    reg_t CHAN_ABORT;                   // Abort an in-progress transfer sequence on one or more channels
    reg_t N_CHANNELS;                   // Number of Channels

} DMA_t;


#define DMA ((DMA_t*)DMA_BASE)       // DMA register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// DMA channel registers: READ_ADDR and WRITE_ADDR
#define DMA_ADDR_LSB                 0
#define DMA_ADDR_MASK                0xffffffff

// DMA channel register: TRANS_COUNT
#define DMA_TRANS_COUNT_LSB          0
#define DMA_TRANS_COUNT_MASK         0xffffffff

// DMA channel register: CTRL_TRIG and CTRL aliases
#define DMA_CTRL_AHB_ERROR           _BIT(31)   // Logical OR of READ_ERROR and WRITE_ERROR (read-only)
#define DMA_CTRL_READ_ERROR          _BIT(30)   // Read bus error; write 1 to clear
#define DMA_CTRL_WRITE_ERROR         _BIT(29)   // Write bus error; write 1 to clear
#define DMA_CTRL_BUSY                _BIT(24)   // Transfer sequence active, including while paused
#define DMA_CTRL_SNIFF_EN             _BIT(23)   // Allow this channel's transfers to update the sniffer
#define DMA_CTRL_BSWAP                _BIT(22)   // Byte-swap each transfer before writing
#define DMA_CTRL_IRQ_QUIET            _BIT(21)   // Suppress block-completion IRQs in quiet mode

#define DMA_CTRL_TREQ_SEL_LSB         15
#define DMA_CTRL_TREQ_SEL_MASK        0x001f8000
#define DMA_CTRL_TREQ_SEL_VAL_DREQ0   (0x00 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO0_TX0 (0x00 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO0_TX1 (0x01 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO0_TX2 (0x02 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO0_TX3 (0x03 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO0_RX0 (0x04 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO0_RX1 (0x05 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO0_RX2 (0x06 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO0_RX3 (0x07 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO1_TX0 (0x08 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO1_TX1 (0x09 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO1_TX2 (0x0a << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO1_TX3 (0x0b << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO1_RX0 (0x0c << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO1_RX1 (0x0d << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO1_RX2 (0x0e << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PIO1_RX3 (0x0f << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_SPI0_TX  (0x10 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_SPI0_RX  (0x11 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_SPI1_TX  (0x12 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_SPI1_RX  (0x13 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_UART0_TX (0x14 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_UART0_RX (0x15 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_UART1_TX (0x16 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_UART1_RX (0x17 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PWM_WRAP0 (0x18 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PWM_WRAP1 (0x19 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PWM_WRAP2 (0x1a << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PWM_WRAP3 (0x1b << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PWM_WRAP4 (0x1c << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PWM_WRAP5 (0x1d << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PWM_WRAP6 (0x1e << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PWM_WRAP7 (0x1f << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_I2C0_TX  (0x20 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_I2C0_RX  (0x21 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_I2C1_TX  (0x22 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_I2C1_RX  (0x23 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_ADC      (0x24 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_XIP_STREAM (0x25 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_XIP_SSITX (0x26 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_XIP_SSIRX (0x27 << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_TIMER0  (0x3b << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_TIMER1  (0x3c << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_TIMER2  (0x3d << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_TIMER3  (0x3e << DMA_CTRL_TREQ_SEL_LSB)
#define DMA_CTRL_TREQ_SEL_VAL_PERMANENT (0x3f << DMA_CTRL_TREQ_SEL_LSB)

#define DMA_CTRL_CHAIN_TO_LSB         11
#define DMA_CTRL_CHAIN_TO_MASK        0x00007800
#define DMA_CTRL_RING_SEL             _BIT(10)   // 0: wrap read address, 1: wrap write address
#define DMA_CTRL_RING_SIZE_LSB        6
#define DMA_CTRL_RING_SIZE_MASK       0x000003c0
#define DMA_CTRL_INCR_WRITE           _BIT(5)    // Increment write address after each transfer
#define DMA_CTRL_INCR_READ            _BIT(4)    // Increment read address after each transfer
#define DMA_CTRL_DATA_SIZE_LSB        2
#define DMA_CTRL_DATA_SIZE_MASK       0x0000000c
#define DMA_CTRL_DATA_SIZE_VAL_BYTE   (0x0 << DMA_CTRL_DATA_SIZE_LSB)
#define DMA_CTRL_DATA_SIZE_VAL_HALFWORD (0x1 << DMA_CTRL_DATA_SIZE_LSB)
#define DMA_CTRL_DATA_SIZE_VAL_WORD   (0x2 << DMA_CTRL_DATA_SIZE_LSB)
#define DMA_CTRL_HIGH_PRIORITY        _BIT(1)    // Give this channel higher bus priority
#define DMA_CTRL_EN                   _BIT(0)    // Enable channel

// DMA: INTR, INTE0, INTF0, INTS0, INTE1, INTF1 and INTS1 registers
#define DMA_INT_CH0                   _BIT(0)
#define DMA_INT_CH1                   _BIT(1)
#define DMA_INT_CH2                   _BIT(2)
#define DMA_INT_CH3                   _BIT(3)
#define DMA_INT_CH4                   _BIT(4)
#define DMA_INT_CH5                   _BIT(5)
#define DMA_INT_CH6                   _BIT(6)
#define DMA_INT_CH7                   _BIT(7)
#define DMA_INT_CH8                   _BIT(8)
#define DMA_INT_CH9                   _BIT(9)
#define DMA_INT_CH10                  _BIT(10)
#define DMA_INT_CH11                  _BIT(11)
#define DMA_INT_CH12                  _BIT(12)   // Reserved/unimplemented on RP2040
#define DMA_INT_CH13                  _BIT(13)   // Reserved/unimplemented on RP2040
#define DMA_INT_CH14                  _BIT(14)   // Reserved/unimplemented on RP2040
#define DMA_INT_CH15                  _BIT(15)   // Reserved/unimplemented on RP2040
#define DMA_INT_MASK                  0x0000ffff

// DMA: TIMER0, TIMER1, TIMER2 and TIMER3 registers
#define DMA_TIMER_X_LSB               16
#define DMA_TIMER_X_MASK              0xffff0000
#define DMA_TIMER_Y_LSB               0
#define DMA_TIMER_Y_MASK              0x0000ffff

// DMA: MULTI_CHAN_TRIGGER register
#define DMA_MULTI_CHAN_TRIGGER_LSB    0
#define DMA_MULTI_CHAN_TRIGGER_MASK   0x0000ffff

// DMA: SNIFF_CTRL register
#define DMA_SNIFF_CTRL_OUT_INV        _BIT(11)   // Invert the result when read
#define DMA_SNIFF_CTRL_OUT_REV        _BIT(10)   // Reverse the result bits when read
#define DMA_SNIFF_CTRL_BSWAP          _BIT(9)    // Byte-swap data before checksum calculation
#define DMA_SNIFF_CTRL_CALC_LSB       5
#define DMA_SNIFF_CTRL_CALC_MASK      0x000001e0
#define DMA_SNIFF_CTRL_CALC_VAL_CRC32 (0x0 << DMA_SNIFF_CTRL_CALC_LSB)
#define DMA_SNIFF_CTRL_CALC_VAL_CRC32R (0x1 << DMA_SNIFF_CTRL_CALC_LSB)
#define DMA_SNIFF_CTRL_CALC_VAL_CRC16 (0x2 << DMA_SNIFF_CTRL_CALC_LSB)
#define DMA_SNIFF_CTRL_CALC_VAL_CRC16R (0x3 << DMA_SNIFF_CTRL_CALC_LSB)
#define DMA_SNIFF_CTRL_CALC_VAL_PARITY (0xe << DMA_SNIFF_CTRL_CALC_LSB)
#define DMA_SNIFF_CTRL_CALC_VAL_CHECKSUM (0xf << DMA_SNIFF_CTRL_CALC_LSB)
#define DMA_SNIFF_CTRL_DMACH_LSB      1
#define DMA_SNIFF_CTRL_DMACH_MASK     0x0000001e
#define DMA_SNIFF_CTRL_EN             _BIT(0)    // Enable sniffer

// DMA: SNIFF_DATA register
#define DMA_SNIFF_DATA_LSB            0
#define DMA_SNIFF_DATA_MASK           0xffffffff

// DMA: FIFO_LEVELS register (read-only)
#define DMA_FIFO_LEVELS_RAF_LVL_LSB   16
#define DMA_FIFO_LEVELS_RAF_LVL_MASK  0x00ff0000
#define DMA_FIFO_LEVELS_WAF_LVL_LSB   8
#define DMA_FIFO_LEVELS_WAF_LVL_MASK  0x0000ff00
#define DMA_FIFO_LEVELS_TDF_LVL_LSB   0
#define DMA_FIFO_LEVELS_TDF_LVL_MASK  0x000000ff

// DMA: CHAN_ABORT register
#define DMA_CHAN_ABORT_LSB            0
#define DMA_CHAN_ABORT_MASK           0x0000ffff

// DMA: N_CHANNELS register (read-only)
#define DMA_N_CHANNELS_LSB            0
#define DMA_N_CHANNELS_MASK           0x0000001f

//================================================================================================================================================================

#endif /* _REG_DMA_H_ */