#include "hal/spi.h"
#include "hal/resets.h"
#include "hal/clocks.h"
#include "hal/fc0.h"

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the SPI block
void spi_init(SPI_t *spi, uint32_t baudrate_hz, uint8_t data_width) {

    resets_reset_block((spi == SPI0) ? RESETS_SPI0 : RESETS_SPI1);
    resets_unreset_block((spi == SPI0) ? RESETS_SPI0 : RESETS_SPI1);

    uint32_t freq_in = fc0_get_hz(fc0_clk_peri);        // get a peripheral clock frequency
    uint32_t prescale, postdiv;

    for (prescale = 2; prescale <= 254; prescale += 2) {

        if (freq_in < (prescale + 2) * 256 * (uint64_t) baudrate_hz) break;
    }

    for (postdiv = 256; postdiv > 1; --postdiv) {

        if (freq_in / (prescale * (postdiv - 1)) > baudrate_hz) break;
    }

    spi->SSPCPSR = prescale;                                                            // clock prescale divisor
    write_masked(spi->SSPCR0, postdiv - 1, SPI_SSPCR0_SCR_MASK, SPI_SSPCR0_SCR_LSB);    // serial clock rate

    write_masked(spi->SSPCR0, data_width - 1, SPI_SSPCR0_DSS_MASK, SPI_SSPCR0_DSS_LSB);     // data width
    clear_bits(spi->SSPCR0, SPI_SSPCR0_SPO);    // SPI clock polarity
    clear_bits(spi->SSPCR0, SPI_SSPCR0_SPH);    // SPI clock phase
    set_bits(spi->SSPCR1, SPI_SSPCR1_SSE);      // SPI enable
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
