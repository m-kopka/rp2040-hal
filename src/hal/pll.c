#include "hal/pll.h"

//---- FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------------

// initializes the pll block
void pll_init(PLL_t *pll, uint16_t vco_fbdiv, uint8_t post_div1, uint8_t post_div2) {

    // reset the PLL block
    resets_reset_block(  (pll == PLL_SYS) ? RESETS_PLL_SYS : RESETS_PLL_USB);
    resets_unreset_block((pll == PLL_SYS) ? RESETS_PLL_SYS : RESETS_PLL_USB);

	pll->CS = 1;                    // no PLL bypass, REFDIV = 1
    pll->FBDIV_INT = vco_fbdiv;     // set VCO feedback divider

	// enable power for PLL and VCO
    clear_bits(pll->PWR, PLL_PWR_PD | PLL_PWR_VCOPD);

    // wait for the PLL to lock
	while (bit_is_clear(pll->CS, PLL_CS_LOCK));

    // set PLL post dividers
	write_masked(pll->PRIM, post_div1, PLL_PRIM_POSTDIV1_MASK, PLL_PRIM_POSTDIV1_LSB);
	write_masked(pll->PRIM, post_div2, PLL_PRIM_POSTDIV2_MASK, PLL_PRIM_POSTDIV2_LSB);

	// enable power for post dividers
    clear_bits(pll->PWR, PLL_PWR_POSTDIVPD);
}  

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
