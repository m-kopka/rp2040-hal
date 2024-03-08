#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

/*
 *  RP2040 GPIO driver
 *  Martin Kopka 2022
*/

#include "rp2040.h"
#include "hal/resets.h"

//---- ENUMERATONS -----------------------------------------------------------------------------------------------------------------------------------------------

// GPIO functions
enum gpio_func {

    GPIO_FUNC_XIP  = 0x00,
    GPIO_FUNC_SPI  = 0x01,
    GPIO_FUNC_UART = 0x02,
    GPIO_FUNC_I2C  = 0x03,
    GPIO_FUNC_PWM  = 0x04,
    GPIO_FUNC_SIO  = 0x05,
    GPIO_FUNC_PIO0 = 0x06,
    GPIO_FUNC_PIO1 = 0x07,
    GPIO_FUNC_GPCK = 0x08,
    GPIO_FUNC_USB  = 0x09,
    GPIO_FUNC_NULL = 0x1f
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// GPIO data directions
enum gpio_dir {

    GPIO_DIR_INPUT = 0,
    GPIO_DIR_OUTPUT = 1
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// GPIO pull up/down resistor options
enum gpio_pull {

    GPIO_NO_PULL  = 0,
    GPIO_PULLDOWN = 1,
    GPIO_PULLUP   = 2
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// GPIO interrupt events
enum gpio_irq_event_t {

    GPIO_IRQ_LEVEL_LOW  = 0x1,  // Level Low: the GPIO pin is a logical 0
    GPIO_IRQ_LEVEL_HIGH = 0x2,  // Level High: the GPIO pin is a logical 1
    GPIO_IRQ_EDGE_LOW   = 0x4,  // Edge Low: the GPIO has transitioned from a logical 1 to a logical 0
    GPIO_IRQ_EDGE_HIGH  = 0x8,  // Edge High: the GPIO has transitioned from a logical 0 to a logical 1
    GPIO_IRQ_ALL_EVENTS = 0xf
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// GPIO output levels
#define LOW     0
#define HIGH    1

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the GPIOs
static inline void gpio_init() {

    resets_reset_block(RESETS_IO_BANK0);
    resets_unreset_block(RESETS_IO_BANK0);
    resets_reset_block(RESETS_PADS_BANK0);
    resets_unreset_block(RESETS_PADS_BANK0);

    SIO->GPIO_OE_CLR = 0xffffffff;
    SIO->GPIO_OUT_CLR = 0xffffffff;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// sets GPIO function
static inline void gpio_set_function(uint8_t gpio, enum gpio_func function) {

    write_masked(IO_BANK0->GPIO[gpio].CTRL, function, IO_BANK0_GPIO_CTRL_FUNCSEL_MASK, IO_BANK0_GPIO_CTRL_FUNCSEL_LSB);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// sets GPIO function to SIO and configures the specified data direction
static inline void gpio_set_dir(uint8_t gpio, enum gpio_dir dir) {

    gpio_set_function(gpio, GPIO_FUNC_SIO);

    if (dir == GPIO_DIR_OUTPUT) set_bits(SIO->GPIO_OE_SET, (1 << gpio));
    else set_bits(SIO->GPIO_OE_CLR, (1 << gpio));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// sets GPIO pullup/pulldown registor
static inline void gpio_set_pull(uint8_t gpio, enum gpio_pull pull) {

    write_masked(PADS_BANK0->GPIO[gpio], pull, (PADS_BANK0_GPIO_PUE | PADS_BANK0_GPIO_PDE), 2);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// sets GPIO output to HIGH or LOW
static inline void gpio_write(uint8_t gpio, bool state) {

    if (state) set_bits(SIO->GPIO_OUT_SET, (1 << gpio));
    else set_bits(SIO->GPIO_OUT_CLR, (1 << gpio));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// toggles GPIO output
static inline void gpio_toggle(uint8_t gpio) {

    set_bits(SIO->GPIO_OUT_XOR, (1 << gpio));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// reads GPIO input
static inline bool gpio_get(uint8_t gpio) {

    return (bit_is_set(SIO->GPIO_IN, (1 << gpio)));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// acknowledges GPIO interrupt request
static inline void gpio_acknowledge_irq(uint8_t gpio) {

    IO_BANK0->INTR[gpio / 8] = GPIO_IRQ_ALL_EVENTS << (((gpio % 8)) * 4);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// enables or disables GPIO interrupt
static inline void gpio_set_irq(uint8_t gpio, enum gpio_irq_event_t events, bool enabled) {

    if (enabled) {

        gpio_acknowledge_irq(gpio);

        set_bits(IO_BANK0->PROC0.INTE[gpio / 8], events << ((gpio % 8) * 4));
        NVIC_EnableIRQ(IO_BANK0_IRQ);

    } else {

        clear_bits(IO_BANK0->PROC0.INTE[gpio / 8], events << ((gpio % 8) * 4));
    }  
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_GPIO_H_ */