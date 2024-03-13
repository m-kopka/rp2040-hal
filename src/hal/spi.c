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

    // calculate the minimum required prescaler to achieve SSPCLK lower than the specified baud rate
    // The prescaler must be an even number, division by an odd number is not possible which ensures that a symmetrical, equal mark space ratio, clock is generated
    for (prescale = 2; prescale <= 254; prescale += 2) {

        if (freq_in / (prescale * (256)) <= baudrate_hz) break;
    }

    // calculate the required postdiv to achieve the specified baud rate
    postdiv = freq_in / (baudrate_hz * prescale);
    if (postdiv > 256) postdiv = 256;
    if (postdiv == 0) postdiv = 1;

    spi->SSPCPSR = prescale;                                                            // clock prescale divisor
    write_masked(spi->SSPCR0, postdiv - 1, SPI_SSPCR0_SCR_MASK, SPI_SSPCR0_SCR_LSB);    // serial clock rate

    write_masked(spi->SSPCR0, data_width - 1, SPI_SSPCR0_DSS_MASK, SPI_SSPCR0_DSS_LSB);     // data width
    clear_bits(spi->SSPCR0, SPI_SSPCR0_SPO);    // SPI clock polarity
    clear_bits(spi->SSPCR0, SPI_SSPCR0_SPH);    // SPI clock phase
    set_bits(spi->SSPCR1, SPI_SSPCR1_SSE);      // SPI enable
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
