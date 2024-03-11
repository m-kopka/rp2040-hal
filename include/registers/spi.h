#ifndef _REG_SPI_H_
#define _REG_SPI_H_

/*
 *  RP2040 SPI register definitions
 *  Martin Kopka 2023
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t SSPCR0;          // Control register 0
    reg_t SSPCR1;          // Control register 1
    reg_t SSPDR;           // Data register
    reg_t SSPSR;           // Status register
    reg_t SSPCPSR;         // Clock prescale register
    reg_t SSPIMSC;         // Interrupt mask set or clear register
    reg_t SSPRIS;          // Raw interrupt status register
    reg_t SSPMIS;          // Masked interrupt status register
    reg_t SSPICR;          // Interrupt clear register
    reg_t SSPDMACR;        // DMA control register
    
} SPI_t;

#define SPI0 ((SPI_t*)SPI0_BASE)       // SPI0 register block
#define SPI1 ((SPI_t*)SPI1_BASE)       // SPI1 register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// SPI: SSPCR0 register
// Control register 0

#define SPI_SSPCR0_SCR_LSB      8
#define SPI_SSPCR0_SCR_MASK     0x0000ff00

#define SPI_SSPCR0_SPH          _BIT(7)
#define SPI_SSPCR0_SPO          _BIT(6)

#define SPI_SSPCR0_FRF1         _BIT(5)
#define SPI_SSPCR0_FRF0         _BIT(4)
#define SPI_SSPCR0_FRF_LSB      4
#define SPI_SSPCR0_FRF_MASK     (SPI_SSPCR0_FRF1 | SPI_SSPCR0_FRF0)
#define SPI_SSPCR0_FRF_VAL_MOTOROLA             (0)
#define SPI_SSPCR0_FRF_VAL_TI                   (SPI_SSPCR0_FRF0)
#define SPI_SSPCR0_FRF_VAL_NATIONAL_MICROWIRE   (SPI_SSPCR0_FRF1)

#define SPI_SSPCR0_DSS_LSB      0
#define SPI_SSPCR0_DSS_MASK     0x0000000f

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// SPI: SSPCR1 register
// Control register 1

#define SPI_SSPCR1_SOD      _BIT(3)
#define SPI_SSPCR1_MS       _BIT(2)
#define SPI_SSPCR1_SSE      _BIT(1)
#define SPI_SSPCR1_LBM      _BIT(0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// SPI: SSPSR register
// Status register

#define SPI_SSPSR_BSY       _BIT(4)
#define SPI_SSPSR_RFF       _BIT(3)
#define SPI_SSPSR_RNE       _BIT(2)
#define SPI_SSPSR_TNF       _BIT(1)
#define SPI_SSPSR_TFE       _BIT(0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// SPI: SSPIMSC register
// Interrupt mask set or clear register

#define SPI_SSPIMSC_TXIM    _BIT(3)
#define SPI_SSPIMSC_RXIM    _BIT(2)
#define SPI_SSPIMSC_RTIM    _BIT(1)
#define SPI_SSPIMSC_RORIM   _BIT(0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// SPI: SSPRIS register
// Raw interrupt status register

#define SPI_SSPRIS_TXRIS    _BIT(3)
#define SPI_SSPRIS_RXRIS    _BIT(2)
#define SPI_SSPRIS_RTRIS    _BIT(1)
#define SPI_SSPRIS_RORRIS   _BIT(0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// SPI: SSPMIS register
// Masked interrupt status register

#define SPI_SSPMIS_TXMIS    _BIT(3)
#define SPI_SSPMIS_RXMIS    _BIT(2)
#define SPI_SSPMIS_RTMIS    _BIT(1)
#define SPI_SSPMIS_RORMIS   _BIT(0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// SPI: SSPICR register
// Interrupt clear register

#define SPI_SSPICR_RTIC     _BIT(1)
#define SPI_SSPICR_RORIC    _BIT(0)

//================================================================================================================================================================

#endif /* _REG_SPI_H_ */