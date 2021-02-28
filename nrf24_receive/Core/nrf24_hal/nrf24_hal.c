/*
 * nrf24_hal.c
 *
 *  Created on: Feb 9, 2021
 *      Author: Admin
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "nrf24_hal.h"

/*------------------------------------------------------------------
                             DEFINATION
  ------------------------------------------------------------------*/
/* Connect to CE PIN of NRF24 */
#define NRF24_HAL_CE_PORT               GPIOA
#define NRF24_HAL_CE_PIN                GPIO_PIN_2

/* Connect to IRQ PIN of NRF24 */
#define NRF24_HAL_IRQ_PORT              GPIOA
#define NRF24_HAL_IRQ_PIN               GPIO_PIN_3

/* Connect to CS PIN of NRF24 */
#define NRF24_HAL_CS_PORT               GPIOA
#define NRF24_HAL_CS_PIN                GPIO_PIN_4

/* DEBUG LED */
#define NRF24_HAL_DEBUG_PORT            GPIOC
#define NRF24_HAL_DEBUG_PIN             GPIO_PIN_13


/*
   This is help to run 1.5s for interupt with formula:
        TIME_DELAY(second) = (PRESCALER)/(HCLK * COUNTER)
*/
#define NRF24_HAL_TIME_COUNT            (30000)
#define NRF24_HAL_TIME_PRESCALER        (36000)


#define NRF24_HAL_INVALID_DATA          NULL
#define NRF24_HAL_INVALID_DATA_LENGTH   (0)

#define NRF24_HAL_DUMMY_BYTE_SPI        (0xFF)

#define NRF24_HAL_WRITE_REG_CMD         (0x20) 
#define NRF24_HAL_READ_REG_CMD          (0x00) 

/*------------------------------------------------------------------
                             GLOBLE VARIABLE
  ------------------------------------------------------------------*/
NRF24_HAL_HANDLER hal_handler;
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim1;
/*------------------------------------------------------------------
                             STATIS VARIABLE
  ------------------------------------------------------------------*/
typedef enum _nrf24_hal_spi_status_
{
    NRF24_HAL_SPI_STATUS_ENABLE = 0,
    NRF24_HAL_SPI_STATUS_DISABLE
}NRF24_HAL_SPI_STATUS;


/*------------------------------------------------------------------
                           PROTOTYPE FUNCTION
  ------------------------------------------------------------------*/
NRF24_HAL_STATUS NRF24_HAL_init_clock   (void);
NRF24_HAL_STATUS NRF24_HAL_init_spi     (void);
NRF24_HAL_STATUS NRF24_HAL_init_gpio    (void);
NRF24_HAL_STATUS NRF24_HAL_init_timer   (void);
void             NRF24_HAL_control_spi  (NRF24_HAL_SPI_STATUS ctrl_status);
extern void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
extern void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

/*------------------------------------------------------------------
                           PUBLISH FUNCTION
  ------------------------------------------------------------------*/
NRF24_HAL_STATUS NRF24_HAL_Init(void)
{
    memset(&hal_handler, 0, sizeof(NRF24_HAL_HANDLER));

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_init_clock())
    {
        return NRF24_HAL_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_init_spi())
    {
        return NRF24_HAL_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_init_timer())
    {
        return NRF24_HAL_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_init_gpio())
    {
        return NRF24_HAL_STATUS_FAIL;
    }

    return NRF24_HAL_STATUS_OK;
}

/*
    Function is used to transfer data to register of NRF24L01 module
    Input Parameter:
        + reg_add: this is register address of NRF24L01
        + data: this is configuration value for NRF24L01
        + data_size: this is No. of register, which will be configurated.
        + time_out: this is time out when SPI transmit.
    Output Parameter:
        + NULL
*/
NRF24_HAL_STATUS NRF24_HAL_Write(uint8_t reg_add, uint8_t *data, uint16_t data_size, uint16_t time_out)
{
    uint8_t tx_data[data_size + 1];
    uint8_t idx;

    tx_data[0] = NRF24_HAL_WRITE_REG_CMD | reg_add;

    for(idx = 0; idx < data_size; idx++)
    {
        tx_data[idx + 1] = data[idx];
    }

    NRF24_HAL_control_spi(NRF24_HAL_SPI_STATUS_ENABLE);

    if(HAL_OK != HAL_SPI_Transmit(&hspi1, tx_data, data_size + 1, time_out))
    {
        return NRF24_HAL_STATUS_FAIL;
    }

    NRF24_HAL_control_spi(NRF24_HAL_SPI_STATUS_DISABLE);

    return NRF24_HAL_STATUS_OK;
}


/*
    Function is used to transfer data to register of NRF24L01 module
    Input Parameter:
        + reg_add: this is register address of NRF24L01
        + data_size: this is size request to read data
        + time_out: this is time out when SPI transmit.
    Output Parameter:
        + data: this is out_put value of register
*/
NRF24_HAL_STATUS NRF24_HAL_Read(uint8_t reg_add, uint8_t *data, uint16_t data_size, uint16_t time_out)
{
    uint8_t tx_data[data_size + 1];
    uint8_t rx_data[data_size + 1];
    uint8_t idx;

    tx_data[0] = NRF24_HAL_READ_REG_CMD | reg_add;

    for(idx =0; idx < data_size; idx++)
    {
        tx_data[idx + 1] = NRF24_HAL_DUMMY_BYTE_SPI;
        rx_data[idx] = 0x00;
    }

    NRF24_HAL_control_spi(NRF24_HAL_SPI_STATUS_ENABLE);
    if(HAL_OK != HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, data_size + 1, time_out))
    {
        return NRF24_HAL_STATUS_FAIL;
    }
    NRF24_HAL_control_spi(NRF24_HAL_SPI_STATUS_DISABLE);
    memcpy(data, rx_data + 1, data_size);
    return NRF24_HAL_STATUS_OK;
}

/*
    Function is used to send command and get data  NRF24L01 module
    Input Parameter:
        + cmd: this is command, which send to NRF24L01
        + data_size: this is size request to read data
        + time_out: this is time out when SPI transmit.
    Output Parameter:
        + data: this is out_put value of register
*/
NRF24_HAL_STATUS NRF24_HAL_CMD(uint8_t cmd, uint8_t *data, uint16_t data_size, uint16_t time_out)
{
    uint8_t tx_data[data_size + 1];
    uint8_t rx_data[data_size + 1];
    uint8_t idx;

    tx_data[0] =  cmd;

    for(idx =0; idx < data_size; idx++)
    {
        tx_data[idx + 1] = NRF24_HAL_DUMMY_BYTE_SPI;
        rx_data[idx] = 0x00;
    }

    NRF24_HAL_control_spi(NRF24_HAL_SPI_STATUS_ENABLE);
    if(HAL_OK != HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, data_size + 1, time_out))
    {
        return NRF24_HAL_STATUS_FAIL;
    }
    NRF24_HAL_control_spi(NRF24_HAL_SPI_STATUS_DISABLE);

    if(data != NULL)
    {
        memcpy(data, rx_data + 1, data_size);
    }
    return NRF24_HAL_STATUS_OK;
}

NRF24_HAL_STATUS NRF24_HAL_Control_CE(NRF24_HAL_CE_STATUS status)
{
    HAL_GPIO_WritePin(NRF24_HAL_CE_PORT, NRF24_HAL_CE_PIN, status);
}


NRF24_HAL_STATUS    NRF24_HAL_Control_DEBUG (NRF24_HAL_DEBUG_STATUS status)
{
    HAL_GPIO_WritePin(NRF24_HAL_DEBUG_PORT, NRF24_HAL_DEBUG_PIN, status);
}

NRF24_HAL_CE_STATUS NRF24_HAL_Get_CE_Status (void)
{
    return (NRF24_HAL_CE_STATUS)HAL_GPIO_ReadPin(NRF24_HAL_CE_PORT, NRF24_HAL_CE_PIN);
}

/*------------------------------------------------------------------
                           STATIC FUNCTION
  ------------------------------------------------------------------*/
NRF24_HAL_STATUS NRF24_HAL_init_clock(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        return NRF24_HAL_STATUS_FAIL;
    }
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        return NRF24_HAL_STATUS_FAIL;
    }
    return NRF24_HAL_STATUS_OK;
}

/*
    This function will config SPI like
    + SPI Master
    + Full Duplex
    + Data size is 8 bit
    + Max Baudrate: 4Mhz 
*/
NRF24_HAL_STATUS NRF24_HAL_init_spi(void)
{
    /* SPI1 parameter configuration*/
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        return NRF24_HAL_STATUS_FAIL;
    }
    return NRF24_HAL_STATUS_OK;
}

NRF24_HAL_STATUS NRF24_HAL_init_gpio(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

    /*Configure GPIO pins : PA2 PA4 */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PC13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pin : PA3 */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
    return NRF24_HAL_STATUS_OK;
}

/*
    This function will config TIMER 1 like
    + Over counter at 1.5 s
*/
NRF24_HAL_STATUS NRF24_HAL_init_timer(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM1_Init 1 */

    /* USER CODE END TIM1_Init 1 */
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = NRF24_HAL_TIME_PRESCALER;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = NRF24_HAL_TIME_COUNT;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
    {
        return NRF24_HAL_STATUS_FAIL;
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
    {
        return NRF24_HAL_STATUS_FAIL;
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
    {
        return NRF24_HAL_STATUS_FAIL;
    }
    return NRF24_HAL_STATUS_OK;
}

void NRF24_HAL_control_spi(NRF24_HAL_SPI_STATUS ctrl_status)
{
    HAL_GPIO_WritePin(NRF24_HAL_CS_PORT, NRF24_HAL_CS_PIN, ctrl_status);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == htim1.Instance)
    {
#if NRF24_HAL_MULTI_MODE_PTX_PRX
        if(NULL != hal_handler.callback_timer())
        {
            hal_handler.callback_timer();
        }
#endif
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == NRF24_HAL_IRQ_PIN)
    {
    	if(NULL != hal_handler.callback_irq())
        {
            hal_handler.callback_irq();
        }
    }
}
