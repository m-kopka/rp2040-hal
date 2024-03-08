.syntax unified
.cpu cortex-m0plus
.thumb

#include "registers/address_map.h"

.equ SIO_DIV_UDIVIDEND_OFFSET,    0x060
.equ SIO_DIV_UDIVISOR_OFFSET,     0x064
.equ SIO_DIV_SDIVIDEND_OFFSET,    0x068
.equ SIO_DIV_SDIVISOR_OFFSET,     0x06c
.equ SIO_DIV_QUOTIENT_OFFSET,     0x070
.equ SIO_DIV_REMAINDER_OFFSET,    0x074

.macro _div_wait_8_cycles
    b 1f
1:  b 1f
1:  b 1f
1:  b 1f
1:
.endm

.type __aeabi_uidiv, %function
.global __aeabi_uidiv
__aeabi_uidiv:

.type __aeabi_uidivmod, %function
.global __aeabi_uidivmod
__aeabi_uidivmod:

    ldr r3, =(SIO_BASE)
    str r0, [r3, #SIO_DIV_UDIVIDEND_OFFSET]
    str r1, [r3, #SIO_DIV_UDIVISOR_OFFSET]

    _div_wait_8_cycles

    ldr r1, [r3, #SIO_DIV_REMAINDER_OFFSET]
    ldr r0, [r3, #SIO_DIV_QUOTIENT_OFFSET]
    bx lr



.type __aeabi_idiv, %function
.global __aeabi_idiv
__aeabi_idiv:

.type __aeabi_idivmod, %function
.global __aeabi_idivmod
__aeabi_idivmod:

    ldr r3, =(SIO_BASE)
    str r0, [r3, #SIO_DIV_SDIVIDEND_OFFSET]
    str r1, [r3, #SIO_DIV_SDIVISOR_OFFSET]

    _div_wait_8_cycles

    ldr r1, [r3, #SIO_DIV_REMAINDER_OFFSET]
    ldr r0, [r3, #SIO_DIV_QUOTIENT_OFFSET]
    bx lr