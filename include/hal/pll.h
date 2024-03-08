#ifndef _HAL_PLL_H_
#define _HAL_PLL_H_

/*
 *  RP2040 PLL LL Driver
 *  Martin Kopka 2022
*/

#include "rp2040.h"
#include "hal/resets.h"

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the pll block
void pll_init(PLL_t *pll, uint16_t vco_fdiv, uint8_t post_div1, uint8_t post_div2);

// disables the pll block
static inline void pll_disable(PLL_t *pll) {

    set_bits(pll->PWR, PLL_PWR_PD);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _HAL_PLL_H_ */