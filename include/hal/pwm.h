#ifndef _HAL_PWM_H_
#define _HAL_PWM_H_

/*
 *  RP2040 PWM LL Driver
 *  Martin Kopka 2022
*/

#include "rp2040.h"
#include "hal/resets.h"
#include "hal/fc0.h"

//---- ENUMERATONS -----------------------------------------------------------------------------------------------------------------------------------------------

enum pwm_channel {

    PWM_CHAN_A = 0,
    PWM_CHAN_B = 1
};

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// returns a PWM slice connected to the specified GPIO
static inline uint8_t pwm_gpio_to_slice(uint8_t gpio) {

    return (gpio >> 1) & 7;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// returns which channel of the PWM slice the specified GPIO is connected to
static inline enum pwm_channel pwm_gpio_to_channel(uint8_t gpio) {

    return (gpio & 1);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// initializes the PWM block
static inline void pwm_init() {

    resets_reset_block(RESETS_PWM);
    resets_unreset_block(RESETS_PWM);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// enables or disables a PWM slice
static inline void pwm_set_enable(uint8_t slice, bool enabled) {

    if (enabled) {
        
        set_bits(PWM->CH[slice].CSR, PWM_CSR_EN);
        PWM->CH[slice].CTR = 0;

    } else clear_bits(PWM->CH[slice].CSR, PWM_CSR_EN);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// sets the clock divider of the specified PWM slice
static inline void pwm_set_div(uint8_t slice, uint8_t int_div, uint8_t frac_div) {

    PWM->CH[slice].DIV = (int_div << 4) | frac_div;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// sets the wrap value of the specified PWM slice
static inline void pwm_set_wrap(uint8_t slice, uint16_t wrap) {

    PWM->CH[slice].TOP = wrap;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// sets the duty cycle of the specified PWM slice and channel
static inline void pwm_set_duty(uint8_t slice, enum pwm_channel channel, uint16_t duty) {

    write_masked(PWM->CH[slice].CC, duty, 0xffff << (channel * 16), channel * 16);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// sets the duty cycle of the specified GPIO
static inline void pwm_set_gpio_duty(uint8_t gpio, uint16_t duty) {

    pwm_set_duty(pwm_gpio_to_slice(gpio), pwm_gpio_to_channel(gpio), duty);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// sets the wrap value of the specified slice according to the specified resolution in bits
static inline void pwm_set_resolution(uint8_t slice, uint8_t resolution) {

    pwm_set_wrap(slice, (1 << resolution) - 2);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// calculates the clock divider value according to the specified PWM frequency (note: resolution must be set first)
static inline void pwm_set_frequency(uint8_t slice, uint32_t frequency_hz) {

    PWM->CH[slice].DIV = (16 * fc0_get_khz(fc0_clk_sys)) / (frequency_hz * (PWM->CH[slice].TOP + 1));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_PWM_H_ */