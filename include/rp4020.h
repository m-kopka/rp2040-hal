#ifndef _RP2040_H_
#define _RP2040_H_

#include <stdint.h>
#include <stdbool.h>

//---- REGISTER MANIPULATION FUNCTIONS ---------------------------------------------------------------------------------------------------------------------------

// set bits in register
#define set_bits(address, mask) ((address) |= ((uint32_t)mask))

// clear bits in register
#define clear_bits(address, mask) ((address) &= ~((uint32_t)mask))

// xor bits in register
#define xor_bits(address, mask) ((address) ^= ((uint32_t)mask))

/** write bits to a group of adjacent bits in register
 * @param address register to manipulate
 * @param value new value
 * @param mask bit mask
 * @param lsb offset to the least significant bit in a group
 *  e.g. write_masked(PORTB, 0b110, 0b111, PB2) sets PB4 and PB3, clears PB2 in PORTB
*/
#define write_masked(address, value, mask, lsb) ((address) = ((address) & (~(mask))) | ((value) << (lsb)))

// tests if a bit is set
#define bit_is_set(address, mask) ((address) & (mask))

// tests if a bit is clear
#define bit_is_clear(address, mask) (!((address) & (mask)))

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#define force_inline inline __attribute__((always_inline))

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _RP2040_H_ */
