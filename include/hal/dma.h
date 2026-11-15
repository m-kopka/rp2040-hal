#ifndef _HAL_DMA_H_
#define _HAL_DMA_H_

/*
 *  RP2040 DMA LL driver
 *  Martin Kopka 2026
*/

#include "rp2040.h"

//---- ENUMERATONS -----------------------------------------------------------------------------------------------------------------------------------------------

enum dma_channel_t {

    DMA_CH0 = 0,
    DMA_CH1 = 1,
    DMA_CH2 = 2,
    DMA_CH3 = 3,
    DMA_CH4 = 4,
    DMA_CH5 = 5,
    DMA_CH6 = 6,
    DMA_CH7 = 7,
    DMA_CH8 = 8,
    DMA_CH9 = 9,
    DMA_CH10 = 10,
    DMA_CH11 = 11
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// DMA transfer request signal selection
enum dma_transfer_request_signal_t {

    DMA_TREQ_PIO0_TX0   = 0,
    DMA_TREQ_PIO0_TX1   = 1,
    DMA_TREQ_PIO0_TX2   = 2,
    DMA_TREQ_PIO0_TX3   = 3,
    DMA_TREQ_PIO0_RX0   = 4,
    DMA_TREQ_PIO0_RX1   = 5,
    DMA_TREQ_PIO0_RX2   = 6,
    DMA_TREQ_PIO0_RX3   = 7,
    DMA_TREQ_PIO1_TX0   = 8,
    DMA_TREQ_PIO1_TX1   = 9,
    DMA_TREQ_PIO1_TX2   = 10,
    DMA_TREQ_PIO1_TX3   = 11,
    DMA_TREQ_PIO1_RX0   = 12,
    DMA_TREQ_PIO1_RX1   = 13,
    DMA_TREQ_PIO1_RX2   = 14,
    DMA_TREQ_PIO1_RX3   = 15,
    DMA_TREQ_SPI0_TX    = 16,
    DMA_TREQ_SPI0_RX    = 17,
    DMA_TREQ_SPI1_TX    = 18,
    DMA_TREQ_SPI1_RX    = 19,
    DMA_TREQ_UART0_TX   = 20,
    DMA_TREQ_UART0_RX   = 21,
    DMA_TREQ_UART1_TX   = 22,
    DMA_TREQ_UART1_RX   = 23,
    DMA_TREQ_PWM_WRAP0  = 24,
    DMA_TREQ_PWM_WRAP1  = 25,
    DMA_TREQ_PWM_WRAP2  = 26,
    DMA_TREQ_PWM_WRAP3  = 27,
    DMA_TREQ_PWM_WRAP4  = 28,
    DMA_TREQ_PWM_WRAP5  = 29,
    DMA_TREQ_PWM_WRAP6  = 30,
    DMA_TREQ_PWM_WRAP7  = 31,
    DMA_TREQ_I2C0_TX    = 32,
    DMA_TREQ_I2C0_RX    = 33,
    DMA_TREQ_I2C1_TX    = 34,
    DMA_TREQ_I2C1_RX    = 35,
    DMA_TREQ_ADC        = 36,
    DMA_TREQ_XIP_STREAM = 37,
    DMA_TREQ_XIP_SSITX  = 38,
    DMA_TREQ_XIP_SSIRX  = 39,
    DMA_TREQ_TIMER0     = 0x3b,
    DMA_TREQ_TIMER1     = 0x3c,
    DMA_TREQ_TIMER2     = 0x3d,
    DMA_TREQ_TIMER3     = 0x3e,
    DMA_TREQ_PERMANENT  = 0x3f
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// DMA data size selection
enum dma_data_size_t {

    DMA_SIZE_8BIT   = 0,
    DMA_SIZE_16BIT  = 1,
    DMA_SIZE_32BIT  = 2
};

//---- STRUCTS ---------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    bool sniff_enable;                                          // enable sniffing
    bool byte_swap;                                             // enable byte swapping
    bool quiet_irq;                                             // enable quiet IRQ
    enum dma_transfer_request_signal_t transfer_request_signal; // transfer request signal selection
    uint8_t chain_to;                                           // chain to another DMA channel
    bool ring_is_at_write_address;                              // wrap write address instead of read address
    uint8_t ring_size;                                          // wrap size (0-5)
    bool increment_write_address;                               // increment write address after each transfer
    bool increment_read_address;                                // increment read address after each transfer
    enum dma_data_size_t data_size;                             // data size (8, 16, 32 bit)
    bool high_priority;                                         // high priority channel
    bool enable;                                                // enable channel

} dma_config_t;

//---- FUNCTIONS ------------------------------------------------------------------------------------------------------------------------------------------------

static inline void dma_config_struct_reset(enum dma_channel_t channel, dma_config_t *config) {

    config->sniff_enable = false;
    config->byte_swap = false;
    config->quiet_irq = false;
    config->transfer_request_signal = DMA_TREQ_PERMANENT;
    config->chain_to = channel;
    config->ring_is_at_write_address = false;
    config->ring_size = 0;
    config->increment_write_address = false;
    config->increment_read_address = false;
    config->data_size = DMA_SIZE_32BIT;
    config->high_priority = false;
    config->enable = false;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static inline void dma_init_channel(enum dma_channel_t channel, dma_config_t *config, bool trigger_transfer) {

    uint32_t control_register = 0;

    if (config->sniff_enable) control_register |= DMA_CTRL_SNIFF_EN;
    if (config->byte_swap) control_register |= DMA_CTRL_BSWAP;
    if (config->quiet_irq) control_register |= DMA_CTRL_IRQ_QUIET;
    control_register |= (config->transfer_request_signal << DMA_CTRL_TREQ_SEL_LSB);
    control_register |= (config->chain_to << DMA_CTRL_CHAIN_TO_LSB);
    if (config->ring_is_at_write_address) control_register |= DMA_CTRL_RING_SEL;
    control_register |= (config->ring_size << DMA_CTRL_RING_SIZE_LSB);
    if (config->increment_write_address) control_register |= DMA_CTRL_INCR_WRITE;
    if (config->increment_read_address) control_register |= DMA_CTRL_INCR_READ;
    control_register |= (config->data_size << DMA_CTRL_DATA_SIZE_LSB);
    if (config->high_priority) control_register |= DMA_CTRL_HIGH_PRIORITY;
    if (config->enable) control_register |= DMA_CTRL_EN;

    if (trigger_transfer) DMA->CH[channel].CTRL_TRIG = control_register;
    else                  DMA->CH[channel].AL1_CTRL  = control_register;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static inline void dma_set_read_address(enum dma_channel_t channel, uint32_t* address, bool trigger_transfer) {

    if (trigger_transfer) DMA->CH[channel].AL3_READ_ADDR_TRIG = (uint32_t)address;
    else                  DMA->CH[channel].READ_ADDR          = (uint32_t)address;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static inline void dma_set_write_address(enum dma_channel_t channel, uint32_t* address, bool trigger_transfer) {

    if (trigger_transfer) DMA->CH[channel].AL2_WRITE_ADDR_TRIG = (uint32_t)address;
    else                  DMA->CH[channel].WRITE_ADDR          = (uint32_t)address;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static inline void dma_set_transfer_count(enum dma_channel_t channel, uint32_t count, bool trigger_transfer) {

    if (trigger_transfer) DMA->CH[channel].AL1_TRANS_COUNT_TRIG = count;
    else                  DMA->CH[channel].TRANS_COUNT          = count;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static inline uint32_t dma_get_transfer_count(enum dma_channel_t channel) {return DMA->CH[channel].TRANS_COUNT;}

static inline void dma_stop(enum dma_channel_t channel) {clear_bits(DMA->CH[channel].CTRL_TRIG, DMA_CTRL_EN);}

static inline void dma_start(enum dma_channel_t channel) {set_bits(DMA->CH[channel].CTRL_TRIG, DMA_CTRL_EN);}

static inline bool dma_is_busy(enum dma_channel_t channel) {return (DMA->CH[channel].CTRL_TRIG & DMA_CTRL_BUSY) != 0;}

static inline void dma_abort_transfer(enum dma_channel_t channel) {set_bits(DMA->CHAN_ABORT, 1 << channel);}

static inline void dma_enable_irq(enum dma_channel_t channel) {set_bits(DMA->INTE0, 1 << channel);}

static inline void dma_force_irq(enum dma_channel_t channel) {set_bits(DMA->INTF0, 1 << channel);}

static inline bool dma_irq_is_pending(enum dma_channel_t channel) {return (DMA->INTS0 & (1 << channel)) != 0;}

static inline void dma_irq_clear_pending(enum dma_channel_t channel) {DMA->INTS0 = 1 << channel;}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_DMA_H_ */