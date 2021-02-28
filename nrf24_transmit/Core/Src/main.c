/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "nrf24_service.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
extern NRF24_SERVICE_HANDLER nrf24_ser_handler;
uint8_t node_addr[5] = {0x26, 0x26, 0x26, 0x26, 0x02};
/* USER CODE END Includes */
uint16_t data_count_ptx = 0;
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1*/
  if(NRF24_SERVICE_STATUS_OK != NRF24_Service_Init())
  {
    return -1;
  }

  //Init nrf24 service handler;
  memset(&nrf24_ser_handler, 0, sizeof(NRF24_SERVICE_HANDLER));
  nrf24_ser_handler.mode             = NRF24_TRANSCIVER_MODE_RX;
  nrf24_ser_handler.have_rx_pkt      = false;
  nrf24_ser_handler.tx_pkt_full      = false;
  nrf24_ser_handler.transmit_done    = false;
  nrf24_ser_handler.rx_data_ready    = false;
  nrf24_ser_handler.transmit_err     = false;
  memcpy(nrf24_ser_handler.nrf24_dev_addr, node_addr, 5);
  //Used Only one pipe for this example
  nrf24_ser_handler.pipe[0].is_en    = true;
  nrf24_ser_handler.pipe[0].addr     = 0x03;
  nrf24_ser_handler.pipe[0].pipe_idx = 1;
  /* USER CODE END 1 */
  //Going to Stan-By Mode to configurate device
  if(NRF24_SERVICE_STATUS_OK != NRF24_Control_Mode_Standby_Active(NRF24_CONTROL_MODE_STANDBY))
  {
	  return -1;
  }
  //Reset all Register
  if(NRF24_SERVICE_STATUS_OK != NRF24_SoftReset_Init())
  {
    return -1;
  }

  //Set address witdh is 5 byte
  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_Addr_Width(NRF24_SET_ADDR_WIDTH_5BYTE))
  {
    return -1;
  }

  //Set 1 Byte CRC encoding
  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_CRC_encoding(NRF24_CRC_ENCODE_1BYTE))
  {
    return -1;
  }

  //Set IRQ mask for node: MAX re-transmit, data send, rx data ready
  if(NRF24_SERVICE_STATUS_OK != NRF24_Config_IRQ_Mask(NRF24_CONFIG_IRQ_MASK_ALL, true))
  {
    return -1;
  }

  //Set Auto re-transmit delay
  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_Auto_Retransmit_Delay(NRF24_RETRANSMIT_DELAY_1000US))
  {
    return -1;
  }

  //Set Max auto re-transmit count
  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_Auto_Retransmit_Count(6))
  {
    return -1;
  }

  //Set RF channel
  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_RF_Channel(26))
  {
    return -1;
  }

  //Set Data rate
  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_RF_Data_Rate(NRF24_DATA_RATE_1MBPS))
  {
    return -1;
  }

  //Set Power Transmition
  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_RF_PWR(NRF24_OUTPUT_PWR_6DBM))
  {
    return -1;
  }

  //Set Enable PIPE 0
  if(NRF24_SERVICE_STATUS_OK != NRF24_En_Dis_PIPE(NRF24_ENABLE_RX_PIPE0, true))
  {
    return -1;
  }

  //Set Enable PIPE 1
  if(NRF24_SERVICE_STATUS_OK != NRF24_En_Dis_PIPE(NRF24_ENABLE_RX_PIPE1, true))
  {
    return -1;
  }

  //Set Dynamic payload for pipe 0
  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_DYNPLD_For_PIPE(0, NRF24_DYNAMIC_PLD_MODE_ON))
  {
    return -1;
  }

  //Set Dynamic payload for pipe 1
  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_DYNPLD_For_PIPE(1, NRF24_DYNAMIC_PLD_MODE_ON))
  {
    return -1;
  }

  //Set address for this node
  if(NRF24_SERVICE_STATUS_OK != NRF24_SetAddress(0, nrf24_ser_handler.nrf24_dev_addr, 5))
  {
    return -1;
  }

  //Set address for pipe 1
  if(NRF24_SERVICE_STATUS_OK != NRF24_SetAddress(nrf24_ser_handler.pipe[0].pipe_idx, \
                                                      &(nrf24_ser_handler.pipe[0].addr), 1))
  {
    return -1;
  }

  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_RX_TX(NRF24_TRANSCIVER_MODE_TX))
  {
	  return -1;
  }

  if(NRF24_SERVICE_STATUS_OK != NRF24_Set_PWRUp(NRF24_PWR_CTRL_UP))
  {
	  return -1;
  }

  //Going to Active Mode to Enable PTX Mode
  if(NRF24_SERVICE_STATUS_OK != NRF24_Control_Mode_Standby_Active(NRF24_CONTROL_MODE_STANDBY))
  {
	  return -1;
  }

  while (1)
  {
    /* USER CODE END WHILE */
    //Send ACK_PLD data
    if(NRF24_SERVICE_STATUS_OK != NRF24_Write_TX_PLD_ACK(nrf24_ser_handler.pipe[0].pipe_idx,\
                                                              &data_count_ptx, (uint8_t)sizeof(data_count_ptx)))
    {
      return -1;
    }

    while(!nrf24_ser_handler.transmit_done)
    {
      if(nrf24_ser_handler.transmit_err)
      {
        break;
      }
    }
    /* USER CODE BEGIN 3 */
    data_count_ptx++;
  }
  /* USER CODE END 3 */
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
