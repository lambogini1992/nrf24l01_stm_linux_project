/*
 * nrf24_reg_def.h
 *
 *  Created on: Feb 12, 2021
 *      Author: Admin
 */

#ifndef NRF24_SERVICE_NRF24_REG_DEF_H_
#define NRF24_SERVICE_NRF24_REG_DEF_H_

/*------------------DEFINE REGISTER------------------*/
#define NRF24_REG_CONFIG                    (0x00)
#define NRF24_REG_EN_ACK                    (0x01)
#define NRF24_REG_EN_RXADD                  (0x02)
#define NRF24_REG_EN_RXADD                  (0x02)
#define NRF24_REG_SET_ADD_WIDTH             (0x03)
#define NRF24_REG_SET_RETRANSMIT            (0x04)
#define NRF24_REG_RF_CHANNEL                (0x05)
#define NRF24_REG_SET_RF                    (0x06)
#define NRF24_REG_STATUS                    (0x07)
#define NRF24_REG_OBSERVER_TX               (0x08)
#define NRF24_REG_RPD                       (0x09)
#define NRF24_REG_RX_ADD0                   (0x0A)
#define NRF24_REG_RX_ADD1                   (0x0B)
#define NRF24_REG_RX_ADD2                   (0x0C)
#define NRF24_REG_RX_ADD3                   (0x0D)
#define NRF24_REG_RX_ADD4                   (0x0E)
#define NRF24_REG_RX_ADD5                   (0x0F)
#define NRF24_REG_TX_ADD                    (0x10)
#define NRF24_REG_RX_PW_P0                  (0x11)
#define NRF24_REG_RX_PW_P1                  (0x12)
#define NRF24_REG_RX_PW_P2                  (0x13)
#define NRF24_REG_RX_PW_P3                  (0x14)
#define NRF24_REG_RX_PW_P4                  (0x15)
#define NRF24_REG_RX_PW_P5                  (0x16)
#define NRF24_REG_FIFO_STATUS               (0x17)
#define NRF24_REG_DYNAMIC_PLD               (0x1C)
#define NRF24_REG_FEATURE                   (0x1D)

/*------------------DEFINE COMMAND------------------*/
#define NRF24_CMD_READ_RX_PLD_WIDTH         (0x60)
#define NRF24_CMD_WRITE_TX_PAYLOAD          (0x60)
#define NRF24_CMD_READ_RX_PAYLOAD           (0x61)
#define NRF24_CMD_FLUSH_TX                  (0xE1)
#define NRF24_CMD_FLUSH_RX                  (0xE2)
#define NRF24_CMD_REUSE_TX_PLD              (0xE3)
#define NRF24_CMD_W_ACK_PAYLOAD             (0xA8)
#define NRF24_CMD_TX_PLD_NO_ACK             (0xA0)
#define NRF24_CMD_NO_OPERATIONS             (0xFF)

#endif /* NRF24_SERVICE_NRF24_REG_DEF_H_ */
