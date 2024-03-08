#include "hal/uart.h"
#include "hal/resets.h"
#include "hal/clocks.h"
#include "hal/gpio.h"
#include "hal/fc0.h"
#include "utils/string.h"

//---- CONSTANTS -------------------------------------------------------------------------------------------------------------------------------------------------

#define MAX_PUTS_STRING_LEN     128     // maximum length of a single string to be sent by the uart_puts() function; protection against non-terminated strings

//---- STRUCTS ---------------------------------------------------------------------------------------------------------------------------------------------------

// TX and RX circular buffers data structure
typedef struct {

    volatile char     *data;        // buffer to store data; this is provided by the calee od a uart_init function
             uint32_t size;         // size of the provided buffer
    volatile uint32_t head;         // position where the next byte will be pushed onto
    volatile uint32_t tail;         // position from where the next byte will be popped from
    volatile bool     is_full;      // set when the head meets the tail after pushing

} uart_fifo_t;

//---- PRIVATE DATA ----------------------------------------------------------------------------------------------------------------------------------------------

static uart_fifo_t tx_fifo[2] = {0};       // UART transmit FIFO buffer for UART0 and UART0
static uart_fifo_t rx_fifo[2] = {0};       // UART receive FIFO buffer for UART0 and UART1

//---- PRIVATE FUNCTIONS -----------------------------------------------------------------------------------------------------------------------------------------

static force_inline void __fifo_push(uart_fifo_t *fifo, char data) {

    fifo->data[fifo->head++] = data;

    if (fifo->head == fifo->size) fifo->head = 0;
    if (fifo->head == fifo->tail) fifo->is_full = true;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static force_inline char __fifo_pop(uart_fifo_t *fifo) {

    char data = fifo->data[fifo->tail++];
    if (fifo->tail == fifo->size) fifo->tail = 0;
    fifo->is_full = false;

    return data;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static force_inline bool __fifo_has_data(uart_fifo_t *fifo) {

    return ((fifo->head != fifo->tail) || fifo->is_full);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static force_inline bool __fifo_is_full(uart_fifo_t *fifo) {

    return (fifo->is_full);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

static force_inline void __fifo_flush(uart_fifo_t *fifo) {

    fifo->tail = fifo->head;
    fifo->is_full = false;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// returns 0 if argument is UART0; returns 1 if argument is UART1
#define uart_get_index(uart) (uart == UART1)

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the UART hardware
void uart_init(UART_t *uart, uint32_t baudrate, uint8_t tx_gpio, uint8_t rx_gpio, char *tx_buffer, uint32_t tx_buffer_size, char *rx_buffer, uint32_t rx_buffer_size) {

    if (tx_buffer == 0 && rx_buffer == 0) return;           // TX buffer nor RX buffer is provided, nothing to initialize
    if (tx_buffer != 0 && tx_buffer_size == 0) return;      // TX buffer size is 0
    if (rx_buffer != 0 && rx_buffer_size == 0) return;      // RX buffer size is 0

    // configure peripheral clock
    clocks_set_aux_source(clk_peri, 0);
    clocks_set_enable(clk_peri, true);

    // take UART block out of reset
    uart_deinit(uart);
    resets_unreset_block(uart_get_index(uart) ? RESETS_UART1 : RESETS_UART0);

    // set gpio function to UART
    gpio_set_function(tx_gpio, GPIO_FUNC_UART);
    gpio_set_function(rx_gpio, GPIO_FUNC_UART);

    // transmit enable and receive enable if a respective fifo was provided by the user
    if (tx_buffer != 0) set_bits(uart->CR, UART_CR_TXE);
    if (rx_buffer != 0) set_bits(uart->CR, UART_CR_RXE);

    // configure the baud rate divisors
    // baud divisor is CLK_PERI * (1/16) / baud
    // by using the formula CLK_PERI * 4 / baud, we get the value shifted left by 6 bits (64x larger)
    // the top bits become the integer part of BRD and the bottom 6 bits become the fractional part
    uint32_t baud_divisor = 4 * fc0_get_hz(fc0_clk_peri) / baudrate;
	uart->IBRD = baud_divisor >> 6;
	uart->FBRD = baud_divisor & 0b111111;

    // set the word length to 8 bits
	write_masked(uart->LCR_H, 0b11, UART_LCR_H_WLEN_MASK, UART_LCR_H_WLEN_LSB);
    set_bits(uart->CR, UART_CR_UARTEN);     // enable the UART

    tx_fifo[uart_get_index(uart)].data = tx_buffer;
    rx_fifo[uart_get_index(uart)].data = rx_buffer;
    tx_fifo[uart_get_index(uart)].size = tx_buffer_size;
    rx_fifo[uart_get_index(uart)].size = rx_buffer_size;
    if (tx_buffer != 0) __fifo_flush(&tx_fifo[uart_get_index(uart)]);
    if (rx_buffer != 0) __fifo_flush(&rx_fifo[uart_get_index(uart)]);

    // enable the TX and RX interrupts and enable the UARTx IRQ in NVIC
    set_bits(uart->IMSC, UART_IMSC_TXIM | UART_IMSC_RXIM);
    NVIC_EnableIRQ(uart_get_index(uart) ? UART1_IRQ : UART0_IRQ);         // enable the UART IRQ in NVIC
    NVIC_SetPriority(uart_get_index(uart) ? UART1_IRQ : UART0_IRQ, 0);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// deinitializes the UART hardware
void uart_deinit(UART_t *uart) {

    resets_reset_block(uart_get_index(uart) ? RESETS_UART1 : RESETS_UART0);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// returns true, if the RX buffer contains new data
volatile bool uart_has_data(UART_t *uart) {

    return (__fifo_has_data(&rx_fifo[uart_get_index(uart)]));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// flushes the RX buffer
void uart_flush(UART_t *uart) {

    __fifo_flush(&rx_fifo[uart_get_index(uart)]);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// transmits one byte via UART; waits if the TX fifo is full
void uart_putc(UART_t *uart, char c) {

    // don't send if the fifo is full, busy waiting here would potentially cause deadline misses of other tasks or looping indefinetly in case of a fault
    // therefore skipping the bytes is the better option here
    if (__fifo_is_full(&tx_fifo[uart_get_index(uart)])) return;

    // disable interrupts while pushing to preserve the correct byte order
    __disable_irq();
    __fifo_push(&tx_fifo[uart_get_index(uart)], c);
    NVIC_SetPendingIRQ(uart_get_index(uart) ? UART1_IRQ : UART0_IRQ);   // trigger the TX empty interrupt
    __enable_irq();
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// converts a number to string and sends it via UART
void uart_puti(UART_t *uart, int num) {

    char temp_buff[16];
    itoa(num, temp_buff, 16, 10);
    uart_puts(uart, temp_buff);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// transmits a null-terminated string via UART; waits if the TX fifo is full
void uart_puts(UART_t *uart, const char *str) {

    uint32_t bytes_sent = 0;        // limit bytes sent in a single function; protection against infinite looping in case a non-terminated string is passed

    while (*str != '\0' && bytes_sent < MAX_PUTS_STRING_LEN) {
        
        uart_putc(uart, *str++);
        bytes_sent++;
    }
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// reads one byte from the RX buffer; returns -1 if there is no new data
int16_t uart_getc(UART_t *uart) {

    if (!__fifo_has_data(&rx_fifo[uart_get_index(uart)])) return -1;
    return __fifo_pop(&rx_fifo[uart_get_index(uart)]);
}

//---- IRQ HANDLERS ----------------------------------------------------------------------------------------------------------------------------------------------

static force_inline void uart_handler(UART_t *uart) {

    // transmit fifo empty
    if (bit_is_set(uart->FR, UART_FR_TXFE)) {

        if (__fifo_has_data(&tx_fifo[uart_get_index(uart)])) uart->DR = __fifo_pop(&tx_fifo[uart_get_index(uart)]);
    }

    // interrupt was triggered by RX
    if (bit_is_set(uart->RIS, UART_RIS_RXRIS)) {

        if (!__fifo_is_full(&rx_fifo[uart_get_index(uart)])) __fifo_push(&rx_fifo[uart_get_index(uart)], uart->DR);
    }

    // acknowledge the IRQ
    uart->ICR = 0xffff;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// triggered when the hardware has finished transmitting or when new data is received
void UART0_Handler() {

    uart_handler(UART0);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// triggered when the hardware has finished transmitting or when new data is received
void UART1_Handler() {

    uart_handler(UART1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------