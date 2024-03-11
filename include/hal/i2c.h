#ifndef _HAL_I2C_H_
#define _HAL_I2C_H_

/*
 *  RP2040 I2C LL Driver
 *  Martin Kopka 2024
*/

#include "rp2040.h"
#include "hal/timer.h"

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the I2C hardware
void i2c_init(I2C_t *i2c, uint32_t baudrate, uint8_t sda_pin, uint8_t scl_pin);

// deinitializes the I2C hardware
void i2c_deinit(I2C_t *i2c);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// starts the I2C transmission by transmitting the restart sequence
static inline void i2c_start_transmission(I2C_t *i2c, uint8_t address, uint32_t timeout_us) {

    uint64_t start_time = timer_get_us();

    // wait for the TX fifo to become empty; abort if timeout reached
    while (bit_is_clear(i2c->STATUS, I2C_STATUS_TFE)) {

        if (timer_get_us() - start_time > timeout_us) return;
    }
    
    i2c->ENABLE = 0;
    i2c->TAR = I2C_CON_TAR_GC_OR_START | address;
    i2c->ENABLE = 1;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// transmits a byte via I2C
static inline void i2c_write(I2C_t *i2c, uint8_t data, bool stop, uint32_t timeout_us) {

    uint64_t start_time = timer_get_us();

    // wait for the TX fifo to become empty; abort if timeout reached
    while (bit_is_clear(i2c->STATUS, I2C_STATUS_TFE)) {

        if (timer_get_us() - start_time > timeout_us) return;
    }

    if (stop) i2c->DATA_CMD = I2C_DATA_CMD_STOP | data;
    else i2c->DATA_CMD = data;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_I2C_H_ */