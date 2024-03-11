#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_

/*
 *  RP2040 SPI LL Driver
 *  Martin Kopka 2024
*/

#include "rp2040.h"

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the SPI block
void spi_init(SPI_t *spi, uint32_t baudrate_hz, uint8_t data_width);

// reads the SPI RX data buffer
static inline uint16_t spi_read(SPI_t *spi) {return (spi->SSPDR);}

// writes to the SPI TX data buffer
static inline void spi_write(SPI_t *spi, uint16_t data) {spi->SSPDR = data;}

// returns the SPI busy flag
static inline bool spi_busy(SPI_t *spi) {return (bit_is_set(spi->SSPSR, SPI_SSPSR_BSY));}

// returns the SPI TX buffer empty flag
static inline bool spi_tx_empty(SPI_t *spi) {return (bit_is_set(spi->SSPSR, SPI_SSPSR_TFE));}

// retutns the SPI RX buffer not empty flag
static inline bool spi_rx_not_empty(SPI_t *spi) {return (bit_is_set(spi->SSPSR, SPI_SSPSR_RNE));}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// returns true if there is no data in the SPI TX buffer and the transmission is finished
static inline bool spi_tx_done(SPI_t *spi) {

    // there is a delay between a write operation to SSPDR and the BSY bit setting. As a consequence, it is mandatory
    // to wait first until TFE = 1 and then until BSY = 0 after writing the last data.
    return (spi_tx_empty(spi) && !spi_busy(spi));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// writes to the SPI data register and waits while the data is being sent
static inline void spi_write_blocking(SPI_t *spi, uint16_t data) {

    spi_write(spi, data);

    while (!spi_tx_done(spi));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_SPI_H_ */