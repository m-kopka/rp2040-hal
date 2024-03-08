#ifndef _HAL_ADC_H_
#define _HAL_ADC_H_

/*
 *  RP2040 ADC LL Driver
 *  Martin Kopka 2022
*/

#include "rp2040.h"
#include "hal/resets.h"
#include "hal/clocks.h"

enum adc_channel_t {

    ADC0 = 0,
    ADC1 = 1,
    ADC2 = 2,
    ADC3 = 3,
    ADC4 = 4    // temperature sensor
};

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the ADC; pll_usb needs to be setup beforehand
static inline void adc_init() {

    clocks_set_aux_source(clk_adc, 0);
	clocks_enable(clk_adc);

	resets_reset_block(RESETS_ADC);
    resets_unreset_block(RESETS_ADC);

	set_bits(ADC->CS, ADC_CS_EN);
	while(bit_is_clear(ADC->CS, ADC_CS_READY));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// reads a sample from the specified ADC channel, waits for the result, then returns it
static volatile uint32_t adc_read(enum adc_channel_t channel) {

    write_masked(ADC->CS, channel, ADC_CS_AINSEL_MASK, ADC_CS_AINSEL_LSB);

	set_bits(ADC->CS, ADC_CS_START_ONCE);
	while(bit_is_clear(ADC->CS, ADC_CS_READY));

    return ADC->RESULT;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_ADC_H_ */