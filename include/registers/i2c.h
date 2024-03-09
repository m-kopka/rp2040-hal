#ifndef _REG_I2C_H_
#define _REG_I2C_H_

/*
 *  RP2040 I2C register definitions
 *  Martin Kopka 2023
*/

#include "registers/address_map.h"

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct {

    reg_t CON;                 // I2C Control Register
    reg_t TAR;                 // I2C Target Address Register
    reg_t SAR;                 // I2C Slave Address Register
    uint32_t _RESERVED_0;
    reg_t DATA_CMD;            // I2C Rx/Tx Data Buffer and Command Register
    reg_t SS_SCL_HCNT;         // Standard Speed I2C Clock SCL High Count Register
    reg_t SS_SCL_LCNT;         // Standard Speed I2C Clock SCL Low Count Register
    reg_t FS_SCL_HCNT;         // Fast Mode or Fast Mode Plus I2C Clock SCL High Count Register
    reg_t FS_SCL_LCNT;         // Fast Mode or Fast Mode Plus I2C Clock SCL Low Count Register
    uint32_t _RESERVED_1[2];
    reg_t INTR_STAT;           // I2C Interrupt Status Register
    reg_t INTR_MASK;           // I2C Interrupt Mask Register
    reg_t RAW_INTR_STAT;       // I2C Raw Interrupt Status Register
    reg_t RX_TL;               // I2C Receive FIFO Threshold Register
    reg_t TX_TL;               // I2C Transmit FIFO Threshold Register
    reg_t CLR_INTR;            // Clear Combined and Individual Interrupt Register
    reg_t CLR_RX_UNDER;        // Clear RX_UNDER Interrupt Register
    reg_t CLR_RX_OVER;         // Clear RX_OVER Interrupt Register
    reg_t CLR_TX_OVER;         // Clear TX_OVER Interrupt Register
    reg_t CLR_RD_REG;          // Clear RD_REQ Interrupt Register
    reg_t CLR_TX_ABRT;         // Clear TX_ABRT Interrupt Register
    reg_t CLR_RX_DONE;         // Clear RX_DONE Interrupt Register
    reg_t CLR_ACTIVITY;        // Clear ACTIVITY Interrupt Register
    reg_t CLR_STOP_DET;        // Clear STOP_DET Interrupt Register
    reg_t CLR_START_DET;       // Clear START_DET Interrupt Register
    reg_t CLR_GEN_CALL;        // Clear GEN_CALL Interrupt Register
    reg_t ENABLE;              // I2C ENABLE Register
    reg_t STATUS;              // I2C STATUS Register
    reg_t TXFLR;               // I2C Transmit FIFO Level Register
    reg_t RXFLR;               // I2C Receive FIFO Level Register
    reg_t SDA_HOLD;            // I2C SDA Hold Time Length Register
    reg_t TX_ABRT_SOURCE;      // I2C Transmit Abort Source Register
    reg_t SLV_DATA_NACK_ONLY;  // Generate Slave Data NACK Register
    reg_t DMA_CR;              // DMA Control Register
    reg_t DMA_TDLR;            // DMA Transmit Data Level Register
    reg_t DMA_RDLR;            // DMA Transmit Data Level Register
    reg_t SDA_SETUP;           // I2C SDA Setup Register
    reg_t ACK_GENERAL_CALL;    // I2C ACK General Call Register
    reg_t ENABLE_STATUS;       // I2C Enable Status Register
    reg_t FS_SPKLEN;           // I2C SS, FS or FM+ spike suppression limit
    uint32_t _RESERVED_2;
    reg_t CLR_RESTART_DET;     // Clear RESTART_DET Interrupt Register 
    uint32_t _RESERVED_3[18];
    reg_t COMP_PARAM_1;        // Component Parameter Register 1
    reg_t COMP_VERSION;        // I2C Component Version Register
    reg_t COMP_TYPE;           // I2C Component Type Register

} I2C_t;

#define I2C0 ((I2C_t*)I2C0_BASE)       // I2C0 register block
#define I2C1 ((I2C_t*)I2C1_BASE)       // I2C1 register block

//==== REGISTER BIT DEFINITIONS ==================================================================================================================================

// I2C: CON register
// I2C Control Register

#define I2C_CON_STOP_DET_IF_MASTER_ACTIVE   _BIT(10)
#define I2C_CON_RX_FIFO_FULL_HLD_CTRL       _BIT(9)
#define I2C_CON_TX_EMPTY_CTRL               _BIT(8)
#define I2C_CON_STOP_DET_IFADDRESSED        _BIT(7)
#define I2C_CON_IC_SLAVE_DISABLE            _BIT(6)
#define I2C_CON_IC_RESTART_EN               _BIT(5)
#define I2C_CON_IC_10BITADDR_MASTER         _BIT(4)
#define I2C_CON_IC_10BITADDR_SLAVE          _BIT(3)

#define I2C_CON_SPEED1              _BIT(2)
#define I2C_CON_SPEED0              _BIT(1)
#define I2C_CON_SPEED_LSB           1
#define I2C_CON_SPEED_MASK          (I2C_CON_SPEED1 | I2C_CON_SPEED0)
#define I2C_CON_SPEED_VAL_STANDARD  (I2C_CON_SPEED0)
#define I2C_CON_SPEED_VAL_FAST      (I2C_CON_SPEED1)
#define I2C_CON_SPEED_VAL_HIGH      (I2C_CON_SPEED1 | I2C_CON_SPEED0)

#define I2C_CON_MASTER_MODE     _BIT(0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// I2C: TAR register
// I2C Target Address Register

#define I2C_CON_TAR_SPECIAL         _BIT(11)
#define I2C_CON_TAR_GC_OR_START     _BIT(10)

#define I2C_CON_TAR_IC_TAR_LSB      0
#define I2C_CON_TAR_IC_TAR_MASK     0x000003ff

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// I2C: DATA_CMD register
// I2C Rx/Tx Data Buffer and Command Register

#define I2C_DATA_CMD_FIRST_DATA_BYTE    _BIT(11)
#define I2C_DATA_CMD_RESTART            _BIT(10)
#define I2C_DATA_CMD_STOP               _BIT(9)
#define I2C_DATA_CMD_CMD                _BIT(8)

#define I2C_DATA_CMD_DAT_LSB    0
#define I2C_DATA_CMD_DAT_MASK   0x000000ff

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// I2C: Interrupt registers

#define I2C_INTR_RESTART_DET        _BIT(12)
#define I2C_INTR_GEN_CALL           _BIT(11)
#define I2C_INTR_START_DET          _BIT(10)
#define I2C_INTR_STOP_DET           _BIT(9)
#define I2C_INTR_ACTIVITY           _BIT(8)
#define I2C_INTR_RX_DONE            _BIT(7)
#define I2C_INTR_TX_ABRT            _BIT(6)
#define I2C_INTR_RD_REQ             _BIT(5)
#define I2C_INTR_TX_EMPTY           _BIT(4)
#define I2C_INTR_TX_OVER            _BIT(3)
#define I2C_INTR_RX_FULL            _BIT(2)
#define I2C_INTR_RX_OVER            _BIT(1)
#define I2C_INTR_RX_UNDER           _BIT(0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// I2C: ENABLE register
// I2C Enable Register

#define I2C_ENABLE_TX_CMD_BLOCK     _BIT(2)
#define I2C_ENABLE_ABORT            _BIT(1)
#define I2C_ENABLE_ENABLE           _BIT(0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// I2C: STATUS register
// I2C Status Register

#define I2C_STATUS_SLV_ACTIVITY     _BIT(6)
#define I2C_STATUS_MST_ACTIVITY     _BIT(5)
#define I2C_STATUS_RFF              _BIT(4)
#define I2C_STATUS_RFNE             _BIT(3)
#define I2C_STATUS_TFE              _BIT(2)
#define I2C_STATUS_TFNF             _BIT(1)
#define I2C_STATUS_ACTIVITY         _BIT(0)

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// TODO: SDA_HOLD and the rest

//================================================================================================================================================================

#endif /* _REG_I2C_H_ */