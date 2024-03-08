#ifndef _REG_ADDRESS_MAP_H_
#define _REG_ADDRESS_MAP_H_

/*
 *  RP2040 Address Map
 *  Martin Kopka 2022
 * 
 *  This file contains base addresses for memory blocks an memory-mapped hardware registers.
 *  extracted from the datasheet section 2.2 Address Map (page 24)
*/

#include <stdint.h>

//---- ROM -------------------------------------------------------------------------------------------------------------------------------------------------------

#define ROM_BASE                    0x00000000

//---- XIP -------------------------------------------------------------------------------------------------------------------------------------------------------

#define XIP_BASE                    0x10000000
#define XIP_NOALLOC_BASE            ((XIP_BASE) + 0x01000000)
#define XIP_NOCACHE_BASE            ((XIP_BASE) + 0x02000000)
#define XIP_NOCACHE_NOALLOC_BASE    ((XIP_BASE) + 0x03000000)
#define XIP_CTRL_BASE               ((XIP_BASE) + 0x04000000)
#define XIP_SRAM_BASE               ((XIP_BASE) + 0x05000000)
#define XIP_SRAM_END                ((XIP_BASE) + 0x05004000)
#define XIP_SSI_BASE                ((XIP_BASE) + 0x08000000)

//---- SRAM ------------------------------------------------------------------------------------------------------------------------------------------------------

// SRAM. SRAM0-3 striped
#define SRAM_BASE                   0x20000000
#define SRAM_STRIPED_BASE           ((SRAM_BASE) + 0x00000000)
#define SRAM_STRIPED_END            ((SRAM_BASE) + 0x00040000)

// SRAM 4-5 are always non-striped
#define SRAM4_BASE                  ((SRAM_BASE) + 0x00040000)
#define SRAM5_BASE                  ((SRAM_BASE) + 0x00041000)
#define SRAM_END                    ((SRAM_BASE) + 0x00042000)

// Non striped aliases of SRAM0-3
#define SRAM0_BASE                  ((SRAM_BASE) + 0x01000000)
#define SRAM1_BASE                  ((SRAM_BASE) + 0x01010000)
#define SRAM2_BASE                  ((SRAM_BASE) + 0x01020000)
#define SRAM3_BASE                  ((SRAM_BASE) + 0x01030000)

//---- APB PERIPHERALS -------------------------------------------------------------------------------------------------------------------------------------------

#define APB_BASE                    0x40000000
#define SYSINFO_BASE                ((APB_BASE) + 0x00000000)       // The sysinfo block contains system information
#define SYSCFG_BASE                 ((APB_BASE) + 0x00004000)       // The system config block controls miscellaneous chip settings
#define CLOCKS_BASE                 ((APB_BASE) + 0x00008000)       // The clocks block provides independent clocks to on-chip and external components
#define RESETS_BASE                 ((APB_BASE) + 0x0000c000)       // The reset controller allows software control of the resets to all of the peripherals that are not critical to boot the processor in RP2040
#define PSM_BASE                    ((APB_BASE) + 0x00010000)       // The power-on state machine removes the reset from various hardware blocks in a specific order
#define IO_BANK0_BASE               ((APB_BASE) + 0x00014000)       // The User GPIO bank
#define IO_QSPI_BASE                ((APB_BASE) + 0x00018000)       // The QSPI bank
#define PADS_BANK0_BASE             ((APB_BASE) + 0x0001c000)       // Each GPIO is connected to the off-chip world via a "pad". Pads are the electrical interface between the chip’s internal logic and external circuitry. They translate signal voltage levels, support higher currents and offer some protection against electrostatic discharge (ESD) events
#define PADS_QSPI_BASE              ((APB_BASE) + 0x00020000)       // Each GPIO is connected to the off-chip world via a "pad". Pads are the electrical interface between the chip’s internal logic and external circuitry. They translate signal voltage levels, support higher currents and offer some protection against electrostatic discharge (ESD) events
#define XOSC_BASE                   ((APB_BASE) + 0x00024000)       // The Crystal Oscillator (XOSC) uses an external crystal to produce an accurate reference clock
#define PLL_SYS_BASE                ((APB_BASE) + 0x00028000)       // PLL used to generate a system clock
#define PLL_USB_BASE                ((APB_BASE) + 0x0002c000)       // PLL used to generate a 48MHz USB reference clock
#define BUSCTRL_BASE                ((APB_BASE) + 0x00030000)       // The RP2040 bus fabric routes addresses and data across the chip
#define UART0_BASE                  ((APB_BASE) + 0x00034000)       // UART Peripheral, instance 0
#define UART1_BASE                  ((APB_BASE) + 0x00038000)       // UART Peripheral, instance 1
#define SPI0_BASE                   ((APB_BASE) + 0x0003c000)       // SPI Peripheral, instance 0
#define SPI1_BASE                   ((APB_BASE) + 0x00040000)       // SPI Peripheral, instance 1
#define I2C0_BASE                   ((APB_BASE) + 0x00044000)       // I2C Peripheral, instance 0
#define I2C1_BASE                   ((APB_BASE) + 0x00048000)       // I2C Peripheral, instance 1
#define ADC_BASE                    ((APB_BASE) + 0x0004c000)       // ADC Peripheral
#define PWM_BASE                    ((APB_BASE) + 0x00050000)       // PWM Peripheral
#define TIMER_BASE                  ((APB_BASE) + 0x00054000)       // Timer Peripheral
#define WATCHDOG_BASE               ((APB_BASE) + 0x00058000)       // Watchdog Peripheral 
#define RTC_BASE                    ((APB_BASE) + 0x0005c000)       // RTC Peripheral
#define ROSC_BASE                   ((APB_BASE) + 0x00060000)       // Internal Ring Oscillator registers
#define VREG_AND_CHIP_RESET_BASE    ((APB_BASE) + 0x00064000)
#define TBMAN_BASE                  ((APB_BASE) + 0x0006c000)

//---- AHB-LITE PERIPHERALS --------------------------------------------------------------------------------------------------------------------------------------

// AHB-Lite Peripherals
#define AHB_BASE                    0x50000000
#define DMA_BASE                    ((AHB_BASE) + 0x00000000)

// USB has a DPRAM at its base followed by registers:
#define USBCTRL_BASE                ((AHB_BASE) + 0x00100000)
#define USBCTRL_DPRAM_BASE          ((USBCTRL_BASE) + 0x00000000)
#define USBCTRL_REGS_BASE           ((USBCTRL_BASE) + 0x00010000)

// Remaining AHB-Lite Peripherals
#define PIO0_BASE                   ((AHB_BASE) + 0x00200000)
#define PIO1_BASE                   ((AHB_BASE) + 0x00300000)
#define XIP_AUX_BASE                ((AHB_BASE) + 0x00400000)

//---- IOPORT REGISTERS ------------------------------------------------------------------------------------------------------------------------------------------

// IOPORT Peripherals
#define IOPORT_BASE                 0xd0000000
#define SIO_BASE                    ((IOPORT_BASE) + 0x00000000)

//---- CORTEX-M0+ INTERNAL REGISTERS -----------------------------------------------------------------------------------------------------------------------------

#define CORTEX_M0PLUS_BASE          0xe0000000

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef volatile uint32_t reg_t;    // register definition data type
#define _BIT(bit) (1 << (bit))

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif /* _REG_ADDRESS_MAP_H_ */