#include "hal/i2c.h"
#include "hal/resets.h"
#include "hal/clocks.h"
#include "hal/gpio.h"
#include "hal/fc0.h"

// returns 0 if argument is I2C0; returns 1 if argument is I2C1
#define i2c_get_index(i2c) (i2c == I2C1)

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the I2C hardware
void i2c_init(I2C_t *i2c, uint32_t baudrate, uint8_t sda_pin, uint8_t scl_pin) {

    resets_reset_block(i2c_get_index(i2c) ? RESETS_I2C1 : RESETS_I2C0);
    resets_unreset_block(i2c_get_index(i2c) ? RESETS_I2C1 : RESETS_I2C0);

    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);

    i2c->ENABLE = 0;
    i2c->CON = I2C_CON_IC_SLAVE_DISABLE | I2C_CON_IC_RESTART_EN | I2C_CON_SPEED_VAL_FAST | I2C_CON_MASTER_MODE;

    uint32_t freq_in = fc0_get_hz(fc0_clk_sys);
    uint32_t period = (freq_in + baudrate / 2) / baudrate;
    uint32_t lcnt = period * 3 / 5;
    uint32_t hcnt = period - lcnt;
    uint32_t sda_tx_hold_count = ((freq_in * 3) / 10000000000) + 1;
    
    i2c->FS_SCL_HCNT = hcnt;                        // SCL high clock period (Fast Speed)
    i2c->FS_SCL_LCNT = lcnt;                        // SCL low clock period (Fast Speed)
    i2c->FS_SPKLEN = lcnt < 16 ? 1 : lcnt / 16;     // Spike length = low clock period / 16
    write_masked(i2c->SDA_HOLD, sda_tx_hold_count, 0xffff, 0);  // Data hold time

    i2c->ENABLE = 1;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// deinitializes the I2C hardware
void i2c_deinit(I2C_t *i2c) {

    resets_reset_block(i2c_get_index(i2c) ? RESETS_I2C1 : RESETS_I2C0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------