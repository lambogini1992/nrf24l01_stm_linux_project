/*
 * nrf24_hal.h
 *
 *  Created on: Feb 9, 2021
 *      Author: Admin
 */

#ifndef NRF24_HAL_NRF24_HAL_H_
#define NRF24_HAL_NRF24_HAL_H_

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <string.h>

#define NRF24_HAL_MULTI_MODE_PTX_PRX        (0)
/*------------------------------------------------------------------
                             DEFINE DATA STRUCTURE
  ------------------------------------------------------------------*/

/*This is CE status PIN*/ 
typedef enum _nrf24_hal_CE_status
{
    NRF24_HAL_CE_STATUS_LOW = 0,
    NRF24_HAL_CE_STATUS_HIGH
}NRF24_HAL_CE_STATUS;

/*This is DEBUG status PIN*/ 
typedef enum _nrf24_hal_DEBUG_status
{
    NRF24_HAL_DEBUG_STATUS_LOW = 0,
    NRF24_HAL_DEBUG_STATUS_HIGH
}NRF24_HAL_DEBUG_STATUS;

/*This is return status function of API*/ 
typedef enum _nrf24_hal_status_
{
    NRF24_HAL_STATUS_OK = 0,
    NRF24_HAL_STATUS_FAIL,
    NRF24_HAL_STATUS_MAX
}NRF24_HAL_STATUS;

typedef struct _nrf24_hal_handler_
{
    uint8_t (*callback_irq)(void);
    uint8_t (*callback_timer)(void);
}NRF24_HAL_HANDLER;

/*------------------------------------------------------------------
                        PUBLISH API
  ------------------------------------------------------------------*/
NRF24_HAL_STATUS    NRF24_HAL_Init          (void);
NRF24_HAL_STATUS    NRF24_HAL_Write         (uint8_t reg_add, uint8_t *data, uint16_t data_size, uint16_t time_out);
NRF24_HAL_STATUS    NRF24_HAL_Read          (uint8_t reg_add, uint8_t *data, uint16_t data_size, uint16_t time_out);
NRF24_HAL_STATUS    NRF24_HAL_CMD           (uint8_t cmd, uint8_t *data, uint16_t data_size, uint16_t time_out);
NRF24_HAL_STATUS    NRF24_HAL_Control_CE    (NRF24_HAL_CE_STATUS status);
NRF24_HAL_STATUS    NRF24_HAL_Control_DEBUG (NRF24_HAL_DEBUG_STATUS status);
NRF24_HAL_CE_STATUS NRF24_HAL_Get_CE_Status (void);
#endif /* NRF24_HAL_NRF24_HAL_H_ */
