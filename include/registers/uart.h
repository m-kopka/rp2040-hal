#ifndef _REG_UART_H_
#define _REG_UART_H_

/*  RP2040 UART register definitions
 *  Martin Kopka 2022
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t DR;                  // Data Register
    reg_t RSR;                 // Receive Status Register / Error Clear Register
     uint32_t _RESERVED_0[4];
    reg_t FR;                  // Flag Register
     uint32_t _RESERVED_1;
    reg_t ILPR;                // IrDA Low-Power Counter Register
    reg_t IBRD;                // Integer Baud Rate Register
    reg_t FBRD;                // Fractional Baud Rate Register
    reg_t LCR_H;               // Line Control Register
    reg_t CR;                  // Control Register
    reg_t IFLS;                // Interrupt FIFO Level Select Register
    reg_t IMSC;                // Interrupt Mask Set/Clear Register
    reg_t RIS;                 // Raw Interrupt Status Register
    reg_t MIS;                 // Masked Interrupt Status Register
    reg_t ICR;                 // Interrupt Clear Registe
    reg_t DMACR;               // DMA Control Register

} UART_t;

#define UART0 ((UART_t*)UART0_BASE)       // UART0 register block
#define UART1 ((UART_t*)UART1_BASE)       // UART1 register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// UART: DR register
// Data Register

#define UART_DR_OE      _BIT(11)        // Overrun error
#define UART_DR_BE      _BIT(10)        // Break error
#define UART_DR_PE      _BIT( 9)        // Parity error
#define UART_DR_FE      _BIT( 8)        // Framing error

// Receive (read) data character. Transmit (write) data character
#define UART_DR_DATA_LSB    0
#define UART_DR_DATA_MASK   0x000000ff

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// UART: RSR register
// Receive Status Register/Error Clear Register

#define UART_RSR_OE     _BIT(3)     // Overrun error
#define UART_RSR_BE     _BIT(2)     // Break error
#define UART_RSR_PE     _BIT(1)     // Parity error
#define UART_RSR_FE     _BIT(0)     // Framing error

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// UART: FR register
// Flag Register

#define UART_FR_RI      _BIT(8)     // Ring indicator
#define UART_FR_TXFE    _BIT(7)     // Transmit FIFO empty
#define UART_FR_RXFF    _BIT(6)     // Receive FIFO full
#define UART_FR_TXFF    _BIT(5)     // Transmit FIFO full
#define UART_FR_RXFE    _BIT(4)     // Receive FIFO empty
#define UART_FR_BUSY    _BIT(3)     // UART busy
#define UART_FR_DCD     _BIT(2)     // Data carrier detect
#define UART_FR_DSR     _BIT(1)     // Data set read
#define UART_FR_CTS     _BIT(0)     // Clear to send

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// UART: LCR_H register
// Line Control Register

#define UART_LCR_H_SPS      _BIT(7)     // Stick parity select

// Word length. These bits indicate the number of data bits transmitted or received in a frame as follows: b11 = 8 bits b10 = 7 bits b01 = 6 bits b00 = 5 bits.
#define UART_LCR_H_WLEN1            (_BIT(6))
#define UART_LCR_H_WLEN0            (_BIT(5))
#define UART_LCR_H_WLEN_LSB         5
#define UART_LCR_H_WLEN_MASK        0x00000060
#define UART_LCR_H_WLEN_VAL_5BITS   (0)
#define UART_LCR_H_WLEN_VAL_6BITS   (UART_LCR_H_WLEN0)
#define UART_LCR_H_WLEN_VAL_7BITS   (UART_LCR_H_WLEN1)
#define UART_LCR_H_WLEN_VAL_6BITS   (UART_LCR_H_WLEN1 | UART_LCR_H_WLEN0)

#define UART_LCR_H_FEN      _BIT(4)     // Enable FIFOs
#define UART_LCR_H_STP2     _BIT(3)     // Two stop bits select
#define UART_LCR_H_EPS      _BIT(2)     // Even parity select
#define UART_LCR_H_PEN      _BIT(1)     // Parity enable
#define UART_LCR_H_BRK      _BIT(1)     // Send break

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// UART: CR register
// Control Register

#define UART_CR_CTSEN       _BIT(15)    // CTS hardware flow control enable
#define UART_CR_RTSEN       _BIT(14)    // RTS hardware flow control enable
#define UART_CR_OUT2        _BIT(13)    // This bit is the complement of the UART Out2 (nUARTOut2) modem status output
#define UART_CR_OUT1        _BIT(12)    // This bit is the complement of the UART Out1 (nUARTOut1) modem status output
#define UART_CR_RTS         _BIT(11)    // Request to send
#define UART_CR_DTR         _BIT(10)    // Data transmit ready
#define UART_CR_RXE         _BIT( 9)    // Receive enable
#define UART_CR_TXE         _BIT( 8)    // Transmit enable
#define UART_CR_LBE         _BIT( 7)    // Loopback enable
#define UART_CR_SIRLP       _BIT( 2)    // SIR low-power IrDA mode
#define UART_CR_SIREN       _BIT( 1)    // SIR enable
#define UART_CR_UARTEN      _BIT( 0)    // UART enable

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// UART: IFLS register
// Interrupt FIFO Level Select Register

// Receive interrupt FIFO level select
#define UART_IFLS_RXIFLSEL_LSB      3
#define UART_IFLS_RXIFLSEL_MASK     0x00000038

// Transmit interrupt FIFO level select
#define UART_IFLS_TXIFLSEL_LSB      0
#define UART_IFLS_TXIFLSEL_MASK     0x00000007

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// UART: IMSC register
// Interrupt Mask Set/Clear Register

#define UART_IMSC_OEIM      _BIT(10)    // Overrun error interrupt mask
#define UART_IMSC_BEIM      _BIT( 9)    // Break error interrupt mask
#define UART_IMSC_PEIM      _BIT( 8)    // Parity error interrupt mask
#define UART_IMSC_FEIM      _BIT( 7)    // Framing error interrupt mask
#define UART_IMSC_RTIM      _BIT( 6)    // Receive timeout interrupt mask
#define UART_IMSC_TXIM      _BIT( 5)    // Transmit interrupt mask
#define UART_IMSC_RXIM      _BIT( 4)    // Receive interrupt mask
#define UART_IMSC_DSRMIM    _BIT( 3)    // nUARTDSR modem interrupt mask
#define UART_IMSC_DCDMIM    _BIT( 2)    // nUARTDCD modem interrupt mask
#define UART_IMSC_CTSMIM    _BIT( 1)    // nUARTCTS modem interrupt mask
#define UART_IMSC_RIMIM     _BIT( 0)    // nUARTRI modem interrupt mask

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// UART: RIS register
// Raw Interrupt Status Register

#define UART_RIS_OERIS          _BIT(10)    // Overrun error interrupt status
#define UART_RIS_BERIS          _BIT( 9)    // Break error interrupt status
#define UART_RIS_PERIS          _BIT( 8)    // Parity error interrupt status
#define UART_RIS_FERIS          _BIT( 7)    // Framing error interrupt status
#define UART_RIS_RTRIS          _BIT( 6)    // Receive timeout interrupt status
#define UART_RIS_TXRIS          _BIT( 5)    // Transmit interrupt status
#define UART_RIS_RXRIS          _BIT( 4)    // Receive interrupt status
#define UART_RIS_DSRRMIS        _BIT( 3)    // nUARTDSR modem interrupt status
#define UART_RIS_DCDDRMIS       _BIT( 2)    // nUARTDCD modem interrupt status
#define UART_RIS_CTSRMIS        _BIT( 1)    // nUARTCTS modem interrupt status
#define UART_RIS_RIRMIS         _BIT( 0)    // UARTRI modem interrupt status

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// UART: MIS register
// Masked Interrupt Status Register

#define UART_MIS_OEMIS          _BIT(10)    // Overrun error masked interrupt status
#define UART_MIS_BEMIS          _BIT( 9)    // Break error masked interrupt status
#define UART_MIS_PEMIS          _BIT( 8)    // Parity error masked interrupt status
#define UART_MIS_FEMIS          _BIT( 7)    // Framing error masked interrupt status
#define UART_MIS_RTMIS          _BIT( 6)    // Receive timeout masked interrupt status
#define UART_MIS_TXMIS          _BIT( 5)    // Transmit masked interrupt status
#define UART_MIS_RXMIS          _BIT( 4)    // Receive masked interrupt status
#define UART_MIS_DSRMMIS        _BIT( 3)    // nUARTDSR modem masked interrupt status
#define UART_MIS_DCDDMMIS       _BIT( 2)    // nUARTDCD modem masked interrupt status
#define UART_MIS_CTSMMIS        _BIT( 1)    // nUARTCTS modem masked interrupt status
#define UART_MIS_RIMMIS         _BIT( 0)    // nUARTRI modem masked interrupt status

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// UART: ICR register
// Interrupt Clear Register

#define UART_ICR_OEIC          _BIT(10)    // Overrun error interrupt clear
#define UART_ICR_BEIC          _BIT( 9)    // Break error interrupt clear
#define UART_ICR_PEIC          _BIT( 8)    // Parity error interrupt clear
#define UART_ICR_FEIC          _BIT( 7)    // Framing error interrupt clear
#define UART_ICR_RTIC          _BIT( 6)    // Receive timeout interrupt clear
#define UART_ICR_TXIC          _BIT( 5)    // Transmit interrupt clear
#define UART_ICR_RXIC          _BIT( 4)    // Receive interrupt clear
#define UART_ICR_DSRMIC        _BIT( 3)    // nUARTDSR modem interrupt clear
#define UART_ICR_DCDDMIC       _BIT( 2)    // nUARTDCD modem interrupt clear
#define UART_ICR_CTSMIC        _BIT( 1)    // nUARTCTS modem interrupt clear
#define UART_ICR_RIMIC         _BIT( 0)    // nUARTRI modem interrupt clear

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// UART: DMACR register
// DMA Control Register

#define UART_DMACR_DMAONERR     _BIT(2)     // DMA on error
#define UART_DMACR_TXDMAE       _BIT(1)     // Transmit DMA enable
#define UART_DMACR_RXDMAE       _BIT(0)     // Receive DMA enable

//================================================================================================================================================================

#endif /* _REG_UART_H_ */