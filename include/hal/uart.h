#ifndef _HAL_UART_H_
#define _HAL_UART_H_

/*
 *  RP2040 UART hardware abstraction layer
 *  Martin Kopka 2024
 *
 *  Implements software FIFOs (circular buffers) for:
 *  • data to be transmitted by the hardware
 *  • received data not yet read by the software
*/ 

#include "rp2040.h"

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the UART hardware
void uart_init(UART_t *uart, uint32_t baudrate, uint8_t tx_gpio, uint8_t rx_gpio, char *tx_buffer, uint32_t tx_buffer_size, char *rx_buffer, uint32_t rx_buffer_size);

// deinitializes the UART hardware
void uart_deinit(UART_t *uart);

// returns true, if the RX buffer contains new data
bool uart_has_data(UART_t *uart);

// flushes the RX buffer
void uart_flush(UART_t *uart);

// transmits one byte via UART; waits if the TX fifo is full
void uart_putc(UART_t *uart, char c);

// converts a number to string and sends it via UART
void uart_puti(UART_t *uart, int num);

// transmits a null-terminated string via UART; waits if the TX fifo is full
void uart_puts(UART_t *uart, const char *str);

// reads one byte from the RX buffer; returns -1 if there is no new data
int16_t uart_getc(UART_t *uart);

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_UART_H_ */