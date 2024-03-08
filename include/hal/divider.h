#ifndef _HAL_DIVIDER_H_
#define _HAL_DIVIDER_H_

#include "rp2040.h"

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

uint32_t __aeabi_uidiv(uint32_t numerator, uint32_t denominator);
uint32_t __aeabi_uidivmod(uint32_t numerator, uint32_t denominator);

uint32_t __aeabi_idiv(uint32_t numerator, uint32_t denominator);
uint32_t __aeabi_idivmod(uint32_t numerator, uint32_t denominator);

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_DIVIDER_H_ */
