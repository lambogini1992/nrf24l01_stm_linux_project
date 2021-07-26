/*
 * nrf24_service.c
 *
 *  Created on: Feb 13, 2021
 *      Author: Admin
 */

#include "nrf24_hal.h"
#include "nrf24_reg_def.h"
#include "nrf24_service.h"

/*---------------------------------------------------------------------------
                            STATIC DEFINITION
---------------------------------------------------------------------------*/
#define NRF24_MAX_PIPE_IDX              (5)
#define NRF24_MAX_NO_PIPE               (6)
#define NRF24_MAX_NO_ADDR_PIPE          (7)

#define NRF24_MAX_PKT_RX_ARRAY          (20)
#define NRF24_MAX_PKT_TX_ARRAY          (20)
/*---------------------------------------------------------------------------
                            GLOBAL VARIABLE
---------------------------------------------------------------------------*/
NRF24_RX_PLD global_rx_pkt;
/*---------------------------------------------------------------------------
                            STATIC VARIABLE
---------------------------------------------------------------------------*/

static uint8_t NRF24_rx_pw_pipes[NRF24_MAX_NO_PIPE] =
{
    NRF24_REG_RX_PW_P0,
    NRF24_REG_RX_PW_P1,
    NRF24_REG_RX_PW_P2,
    NRF24_REG_RX_PW_P3,
    NRF24_REG_RX_PW_P4,
    NRF24_REG_RX_PW_P5
};

static uint8_t nRF24_address_regs[NRF24_MAX_NO_ADDR_PIPE] =
{
    NRF24_REG_RX_ADD0,
    NRF24_REG_RX_ADD1,
    NRF24_REG_RX_ADD2,
    NRF24_REG_RX_ADD3,
    NRF24_REG_RX_ADD4,
    NRF24_REG_RX_ADD5,
    NRF24_REG_TX_ADD
};
extern NRF24_HAL_HANDLER hal_handler;
NRF24_SERVICE_HANDLER nrf24_ser_handler;
/*This will be implement in next version*/
static NRF24_RX_PLD rx_pkt_arr[NRF24_MAX_PKT_RX_ARRAY];
static NRF24_TX_DATA_PLD tx_pkt_arr[NRF24_MAX_PKT_TX_ARRAY];
/*---------------------------------------------------------------------------
                            PROTOTYPE FUNCTION
---------------------------------------------------------------------------*/
static uint8_t NRF24_get_status_reg(void);
static uint8_t NRF24_get_pld_size_of_rx_pipe(uint8_t pipe_idx);
static NRF24_SERVICE_STATUS NRF24_get_pld_data_in_RX_FIFO(uint8_t *pld, uint8_t pld_size);
static uint8_t NRF24_Handle_IRQ_Pin_Signal(void);
static uint8_t NRF24_Handle_Timer_IRQ(void);

/*This will be implement in next version*/
static void NRF24_Put_RX_pkt_into_array(void);
static void NRF24_Put_TX_pkt_into_array(void);
/*---------------------------------------------------------------------------
                            PUBLISH API
---------------------------------------------------------------------------*/
/*
    Description:
        + Initialize all HW peripheral for MCU
    Input Parameter:
        + NULL
    Output Parameter:
        + NULL
*/
NRF24_SERVICE_STATUS NRF24_Service_Init(void)
{
    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Init())
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK;
}
/*
    Description:
        + NRF24L01 Software reset.
        + This function is used to configure reset value for all register
        + The reset value is decribled in NRF24 datasheet
        + Initialize global variable.
    Input Parameter:
        + NULL
    Output Parameter:
        + NULL
*/
NRF24_SERVICE_STATUS NRF24_SoftReset_Init(void)
{
    size_t ret;
	uint8_t addr0[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	uint8_t addr1[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_CONFIG, 0x08, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_EN_ACK, 0x3F, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_EN_RXADD, 0x03, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_SET_RETRANSMIT, 0x03, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RF_CHANNEL, 0x02, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_SET_RF, 0x07, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_STATUS, 0x70, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_ADD0, addr0, 5, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_ADD1, addr1, 5, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_TX_ADD, addr0, 5, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_ADD2, 0x03, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_ADD3, 0x04, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_ADD4, 0x05, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_ADD5, 0x06, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_PW_P0, 0x00, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_PW_P1, 0x00, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_PW_P2, 0x00, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_PW_P3, 0x00, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_PW_P4, 0x00, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_RX_PW_P5, 0x00, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_DYNAMIC_PLD, 0x00, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_FEATURE, 0x00, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    hal_handler.callback_irq    = NRF24_Handle_IRQ_Pin_Signal;
    hal_handler.callback_timer  = NRF24_Handle_Timer_IRQ;

    return NRF24_SERVICE_STATUS_OK;
};

/*
    Description:
        + This function is used for clear IRQ bit in STATUS register
    Input Parameter:
        + irq_clear: this is bit value want to clear in STATUS register
    Output Parameter:
        + NULL
*/
NRF24_SERVICE_STATUS NRF24_ClearIRQ(NRF24_IRQ irq_clear)
{
    uint8_t status_data = 0;

    status_data = NRF24_get_status_reg();
    if(status_data == 0xFF)
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    status_data = status_data | irq_clear;

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Write(NRF24_REG_STATUS, status_data, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK;
}

/*
    Description:
        + This function is used to get IRQ status in STATUS Register
    Input Parameter:
        + NULL
    Output Parameter:
        + Return value of NRF24_IRQ enum
*/
NRF24_IRQ NRF24_GetIRQ_Status(void)
{
    uint8_t status_data = 0;
    
    status_data = NRF24_get_status_reg();
    if(status_data == 0xFF)
    {
        return NRF24_IRQ_INVALID;
    } 

    status_data = ~status_data;

    if((status_data & NRF24_IRQ_RX_DATA_READY) == NRF24_IRQ_RX_DATA_READY)
    {
        return NRF24_IRQ_RX_DATA_READY;
    }
    else if((status_data & NRF24_IRQ_TX_DATA_SENT) == NRF24_IRQ_TX_DATA_SENT)
    {
        return NRF24_IRQ_TX_DATA_SENT;
    }
    else if((status_data & NRF24_IRQ_MAX_RETRANSMIT) == NRF24_IRQ_MAX_RETRANSMIT)
    {
        return NRF24_IRQ_MAX_RETRANSMIT;
    }

    return NRF24_IRQ_INVALID;
}


/*
    Description:
        + This function is used to toggle DEBUG PIN 3 time with 500ms
    Input Parameter:
        + NULL
    Output Parameter:
        + NULL
*/
void NRF24_Toggle_Debug_Pin(void)
{
    NRF24_HAL_Control_DEBUG(NRF24_HAL_DEBUG_STATUS_HIGH);
    HAL_Delay(500000);
    NRF24_HAL_Control_DEBUG(NRF24_HAL_DEBUG_STATUS_LOW);
    HAL_Delay(500000);
    NRF24_HAL_Control_DEBUG(NRF24_HAL_DEBUG_STATUS_HIGH);
    HAL_Delay(500000);
    NRF24_HAL_Control_DEBUG(NRF24_HAL_DEBUG_STATUS_LOW);
    HAL_Delay(500000);
}

/*
    Description:
        + This function is used to set address for pipe
    Input Parameter:
        + pipe_idx: is index of pipe in nrf24 module
                    If pipe index is RX_PIPE 1/2/3/4/5. The address input must have one element and 
                    addr_size must be one
        + address: the configurate address for each pipe
        + addr_size: this is size of address input
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_SetAddress(uint8_t pipe_idx, uint8_t *address,uint8_t addr_size)
{
    if(pipe_idx > 6)
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if((addr_size > 5) || (addr_size < 0))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    switch (nRF24_address_regs[pipe_idx])
    {
        /*
          In datasheet, RX_PIPE 0 and TX_PIPE 
          must be had same address like each other
        */
        case NRF24_REG_RX_ADD0:
        case NRF24_REG_TX_ADD:
            {
                if(NRF24_HAL_Write(NRF24_REG_RX_ADD0, address, addr_size, 100) != NRF24_SERVICE_STATUS_OK)
                {
                    return NRF24_SERVICE_STATUS_FAIL;
                }

                if(NRF24_HAL_Write(NRF24_REG_TX_ADD, address, addr_size, 100) != NRF24_SERVICE_STATUS_OK)
                {
                    return NRF24_SERVICE_STATUS_FAIL;
                }
            }
            break;
        
        default:
            {
                if(NRF24_HAL_Write(nRF24_address_regs[pipe_idx], address, 1, 100) != NRF24_SERVICE_STATUS_OK)
                {
                    return NRF24_SERVICE_STATUS_FAIL;
                }
            }
            break;
    }    
    return NRF24_SERVICE_STATUS_OK;
}

/*
    Description:
        + This function is used to enable or disable rx pipe
    Input Parameter:
        + pipe: this is value to set ENABLE RX PIPE
        + is_en: this variable is enable or disable RX PIPE
                 If is_en is true, that mean the RX PIPE will be enabled.
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_En_Dis_PIPE(NRF24_ENABLE_RX_PIPE pipe, bool is_en)
{
    uint8_t data_reg = 0xFF;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_EN_RXADD, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(is_en)
    {
        data_reg = data_reg | pipe;
    }
    else
    {
        data_reg = ~data_reg;
        data_reg = data_reg | pipe;
        data_reg = ~data_reg;
    }

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_EN_RXADD, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_SERVICE_STATUS_OK;
}

/*
    Description:
        + This function is used to setting TX or RX mode for NRF24L01
    Input Parameter:
        + trans_mode: this is value will set into PRIM_RX bit in CONFIG register
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Set_RX_TX(NRF24_TRANSCIVER_MODE trans_mode)
{
    uint8_t data_reg = 0x08;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_CONFIG, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    switch (trans_mode)
    {
        case NRF24_TRANSCIVER_MODE_TX:
            {
                /*Because, PRIM_RX bit is first bit in CONFIG reg*/
                data_reg = data_reg & 0x7E;
            }
            break;

        case NRF24_TRANSCIVER_MODE_RX:
            {
                data_reg |= trans_mode;
            }
            break;
    }

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_CONFIG, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK;
}

/*
    Description:
        + This function is used to setting PWR mode for NRF24L01
    Input Parameter:
        + trans_mode: this is value will set into PRW_UP bit in CONFIG register
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Set_PWRUp(NRF24_PWR_CTRL pwr_mode)
{
    uint8_t data_reg = 0x08;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_CONFIG, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    switch (pwr_mode)
    {
        case NRF24_PWR_CTRL_DOWN:
            {
                /*Because, PWR_UP bit is second bit in CONFIG reg*/
                data_reg = data_reg & 0x7D;
            }
            break;

        case NRF24_PWR_CTRL_UP:
            {
                data_reg |= pwr_mode;
            }
            break;
    }   

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_CONFIG, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK; 
}

/*
    Description:
        + This function is used to setting No of CRC byte for transmit packet of NRF24L01
    Input Parameter:
        + trans_mode: this is value will set into CRCO and EN_CRC bits in CONFIG register
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Set_CRC_encoding(NRF24_CRC_ENCODE no_byte)
{
    uint8_t data_reg = 0x08;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_CONFIG, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    switch (no_byte)
    {
        case NRF24_CRC_ENCODE_OFF:
            {
                /*
                    Because, CRCO bit is third bit in CONFIG reg
                    and EN_CRC bit is forth bit in CONFIG reg
                */
                data_reg = data_reg & 0x73;
            }
            break;
        
        case NRF24_CRC_ENCODE_1BYTE:
            {
                /*
                    Because, CRCO bit is third bit in CONFIG reg
                    and EN_CRC bit is forth bit in CONFIG reg
                */
                data_reg = (data_reg & 0x73) | NRF24_CRC_ENCODE_1BYTE;
            }
            break;
        
        case NRF24_CRC_ENCODE_2BYTE:
            {
                /*
                    Because, CRCO bit is third bit in CONFIG reg
                    and EN_CRC bit is forth bit in CONFIG reg
                */
                data_reg = (data_reg & 0x73) | NRF24_CRC_ENCODE_2BYTE;
            }
            break;
    }   

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_CONFIG, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK; 
}

/*
    Description:
        + This function is used to set IRQ mask for NRF24L01
    Input Parameter:
        + irq_mask: this is value will set into PRW_UP bit in CONFIG register
        + irq_en: this is used to allow enable or disable interrupt of NRF24L01
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Config_IRQ_Mask(NRF24_CONFIG_IRQ_MASK irq_mask, bool irq_en)
{
    uint8_t data_reg = 0x08;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_CONFIG, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(irq_en)
    {
        data_reg = data_reg | irq_mask;
    }
    else
    {
        data_reg = ~data_reg;
        data_reg = data_reg | irq_mask;
        data_reg = ~data_reg;
    }   

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_CONFIG, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK; 
}

/*
    Description:
        + This function is used to set no. of byte to be used for Address of device
    Input Parameter:
        + add_width: this is value will set no of byte used for address. It will config
                     into AW bit of SETUP_AW register
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Set_Addr_Width(NRF24_SET_ADDR_WIDTH add_width)
{
    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_CONFIG, &add_width, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK; 
}

/*
    Description:
        + This function is used to set delay between retransmit packet
    Input Parameter:
        + delay_rt: this is value will set no of byte used for address. It will config
                    into AW bit of ARD register of SETUP_RETR
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Set_Auto_Retransmit_Delay(NRF24_RETRANSMIT_DELAY delay_rt)
{
    uint8_t data_reg = 0x08;
    uint8_t set_value;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_SET_RETRANSMIT, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    set_value = (delay_rt << 4) & 0xF0;
    data_reg = data_reg | set_value;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_SET_RETRANSMIT, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK;     
}

/*
    Description:
        + This function is used to set no. of retransmit packet of device
    Input Parameter:
        + set_count: this is value will set no of retranmit
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Set_Auto_Retransmit_Count(uint8_t set_count)
{
    uint8_t data_reg = 0x08;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_SET_RETRANSMIT, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    data_reg = data_reg | set_count;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_SET_RETRANSMIT, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK;        
}

/*
    Description:
        + This function is used to set rf channel communication of device
    Input Parameter:
        + rf_channel: this is value will rf channel of device
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Set_RF_Channel(uint8_t rf_channel)
{
    uint8_t data_reg = 0x08;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_RF_CHANNEL, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    data_reg = data_reg | rf_channel;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_RF_CHANNEL, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK;   
}

/*
    Description:
        + This function is used to set rf data rate communication of device
    Input Parameter:
        + data_rate: this is value will rf data rate of device
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Set_RF_Data_Rate(NRF24_DATA_RATE data_rate)
{
    uint8_t data_reg = 0x08;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_SET_RF, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    data_reg = data_reg | data_rate;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_SET_RF, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK;  
}

/*
    Description:
        + This function is used to set rf pwr transmit communication of device
    Input Parameter:
        + data_rate: this is value will rf pwr transmit of device
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Set_RF_PWR(NRF24_OUTPUT_PWR rf_pwr)
{
    uint8_t data_reg = 0x08;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_SET_RF, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    data_reg = data_reg | rf_pwr;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_SET_RF, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK;  
}

/*
    Description:
        + This function is used to know another node is transmit or not
    Input Parameter:
        + NULL
    Output Parameter:
        + Return value of RPD bit in RPD register
*/
NRF24_RECEIVE_PWR NRF24_Get_PWR_Received_status(void)
{
    uint8_t data_reg;
    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_RPD, &data_reg, 1, 100))
    {
        return NRF24_RECEIVE_PWR_NONE;
    }

    return (NRF24_RECEIVE_PWR)data_reg;
}

/*
    Description:
        + This function is used to know status of TX FIFO
    Input Parameter:
        + NULL
    Output Parameter:
        + Return value of TX FIFO in FIFO_STATUS register
*/
NRF24_TXFIFO_STATUS  NRF24_Get_TX_FIFO_Status(void)
{
    uint8_t data_reg;
    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_FIFO_STATUS, &data_reg, 1, 100))
    {
        return NRF24_RECEIVE_PWR_NONE;
    }

    return (NRF24_TXFIFO_STATUS)(data_reg >> 4);    
}

/*
    Description:
        + This function is used to know status of RX FIFO
    Input Parameter:
        + NULL
    Output Parameter:
        + Return value of RX FIFO in FIFO_STATUS register
*/
NRF24_RXFIFO_STATUS  NRF24_Get_RX_FIFO_Status(void)
{
    uint8_t data_reg;
    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_FIFO_STATUS, &data_reg, 1, 100))
    {
        return NRF24_RECEIVE_PWR_NONE;
    }

    return (NRF24_RECEIVE_PWR)(data_reg & 0x03);    
}

/*
    Description:
        + This function is used to allow another pipe is DYNAMIC PLD or not
    Input Parameter:
        + pipe_idx: this is value will set which pipe is en/dis DYNAMIC PLD
        + mode: this is used to know which mode is used
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Set_DYNPLD_For_PIPE(uint8_t pipe_idx, NRF24_DYNAMIC_PLD mode)
{
    uint8_t data_reg;

    if(pipe_idx > NRF24_MAX_PIPE_IDX)
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_DYNAMIC_PLD, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    switch (mode)
    {
        case NRF24_DYNAMIC_PLD_ON:
        {
            data_reg = data_reg | (0x01 << pipe_idx);
        }
        break;

        case NRF24_DYNAMIC_PLD_OFF:
        {
            data_reg = data_reg & (~(0x01 << pipe_idx));
        }
        break;
    }

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_DYNAMIC_PLD, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_SERVICE_STATUS_OK;
}

/*
    Description:
        + This function is used to en/dis dynamic payload for nrf24 device
    Input Parameter:
        + mode: this is value will set dynamic payload bit in FEATURE register
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_En_Dis_DYN_PLD(NRF24_DYNAMIC_PLD_MODE mode)
{
    uint8_t data_reg;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_FEATURE, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    data_reg = data_reg | mode;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_FEATURE, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_SERVICE_STATUS_OK;    
}

/*
    Description:
        + This function is used to en/dis ACK payload for nrf24 device
    Input Parameter:
        + mode: this is value will set ACK payload bit in FEATURE register
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_En_Dis_ACK_PLD(NRF24_ACK_STATUS mode)
{
    uint8_t data_reg;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_FEATURE, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    data_reg = data_reg | mode;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_FEATURE, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_SERVICE_STATUS_OK;    
}

/*
    Description:
        + This function is used to en/dis DYNAMIC ACK payload for nrf24 device
    Input Parameter:
        + mode: this is value will set DYNAMIC ACK payload bit in FEATURE register
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_En_Dis_DYN_ACK(NRF24_DYNAMIC_ACK_MODE mode)
{
    uint8_t data_reg;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Read(NRF24_REG_FEATURE, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    data_reg = data_reg | mode;

    if(NRF24_HAL_STATUS_OK != NRF24_HAL_Write(NRF24_REG_FEATURE, &data_reg, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_SERVICE_STATUS_OK;        
}

/*
    Description:
        + This function is used to send FLUSH TX FIFO command for nrf24 device
    Input Parameter:
        + NULL
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Flush_TX_FIFO(void)
{
    if(NRF24_HAL_STATUS_OK != NRF24_HAL_CMD(NRF24_CMD_FLUSH_TX, NULL, 0, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_SERVICE_STATUS_OK;  
}

/*
    Description:
        + This function is used to send FLUSH RX FIFO command for nrf24 device
    Input Parameter:
        + NULL
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Flush_RX_FIFO(void)
{
    if(NRF24_HAL_STATUS_OK != NRF24_HAL_CMD(NRF24_CMD_FLUSH_RX, NULL, 0, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_SERVICE_STATUS_OK; 
}

/*
    Description:
        + This function is used to send Reused TX PLD command for nrf24 device
    Input Parameter:
        + NULL
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Reuse_TX_PL(void)
{
    if(NRF24_HAL_STATUS_OK != NRF24_HAL_CMD(NRF24_CMD_REUSE_TX_PLD, NULL, 0, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_SERVICE_STATUS_OK;
}

/*
    Description:
        + This function is used to read RX PLD in first FIFO pf nrf24 device
    Input Parameter:
        + NULL
    Output Parameter:
        + pld: this is data rx payload.
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Read_RX_PLD(NRF24_RX_PLD *pld)
{
    uint8_t status_reg = 0;

    status_reg = NRF24_get_status_reg();
    if(0xFF == status_reg)
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    /*Because Pipe idx is in 3 bit from second to fourth bit of STATUS register*/
    pld->pipe_idx = (status_reg >> 1) & 0x07;

    pld->pld_size = NRF24_get_pld_size_of_rx_pipe(pld->pipe_idx);
    if(pld->pld_size == 0x00)
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_get_pld_data_in_RX_FIFO(pld->data_pld, pld->pld_size);
}

/*
    Description:
        + This function is used to write TX PLD without ACK in first FIFO pf nrf24 device
    Input Parameter:
        + data: packet want to transfer
        + data_size: size of packet(byte)
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Write_TX_PLD(uint8_t *data, uint8_t data_size)
{
    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_CMD(NRF24_CMD_TX_PLD_NO_ACK, data, data_size, 1))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_SERVICE_STATUS_OK;
}

/*
    Description:
        + This function is used to write TX PLD with ACK in first FIFO pf nrf24 device
    Input Parameter:
        + data: packet want to transfer
        + data_size: size of packet(byte)
        + pipe_idx
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Write_TX_PLD_ACK(uint8_t pipe_idx, uint8_t *data, uint8_t data_size)
{
    if(pipe_idx > NRF24_MAX_PIPE_IDX)
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_CMD(NRF24_CMD_W_ACK_PAYLOAD | pipe_idx, data, data_size, 1))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }

    return NRF24_SERVICE_STATUS_OK;
}

/*
    Description:
        + This function is used to enable nrf24 device is in stand-by mode or active mode with CE PIN
    Input Parameter:
        + mode : the mode control
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Control_Shockbrust(NRF24_ENABLE_PTX_PRX mode)
{
    switch(mode)
    {
        case NRF24_ENABLE_PTX_PRX_ON:
            {
                if(NRF24_HAL_STATUS_OK != NRF24_HAL_Control_CE(NRF24_HAL_CE_STATUS_HIGH))
                {
                    return NRF24_SERVICE_STATUS_FAIL;
                }
            }
            break;

        case NRF24_ENABLE_PTX_PRX_OFF:
            {
                if(NRF24_HAL_STATUS_OK != NRF24_HAL_Control_CE(NRF24_HAL_CE_STATUS_HIGH))
                {
                    return NRF24_SERVICE_STATUS_FAIL;
                }
            }
            break;
    }

    return NRF24_SERVICE_STATUS_OK;
}

/*
    Description:
        + This function is used to enable nrf24 device is in stand-by mode or active mode with CE PIN
    Input Parameter:
        + mode : the mode control
    Output Parameter:
        + Return status to know the process is success or failed
*/
NRF24_SERVICE_STATUS NRF24_Control_Mode_Standby_Active(NRF24_CONTROL_MODE mode)
{
    switch(mode)
    {
        case NRF24_CONTROL_MODE_ACTIVE_TX_RX:
            {
                if(NRF24_HAL_STATUS_OK != NRF24_HAL_Control_CE(NRF24_HAL_CE_STATUS_HIGH))
                {
                    return NRF24_SERVICE_STATUS_FAIL;
                }
            }
            break;

        case NRF24_CONTROL_MODE_STANDBY:
            {
                if(NRF24_HAL_STATUS_OK != NRF24_HAL_Control_CE(NRF24_HAL_CE_STATUS_HIGH))
                {
                    return NRF24_SERVICE_STATUS_FAIL;
                }
            }
            break;
    }

    return NRF24_SERVICE_STATUS_OK;
}

/*---------------------------------------------------------------------------
                            STATIC FUNCTION
---------------------------------------------------------------------------*/
/*
    Description:
        + This function is used to read STATUS register
    Input Parameter:
        + NULL
    Output Parameter:
        + Return value of STATUS register
*/
static uint8_t NRF24_get_status_reg(void)
{
    uint8_t status_data = 0;
    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Read(NRF24_REG_STATUS, &status_data, 1, 100))
    {
        return 0xFF;
    }
    return status_data;
}

/*
    Description:
        + This function is used to read how many byte in rx fifo payload of RX_PW_Px register
    Input Parameter:
        + pipe_idx: this is pipe index
    Output Parameter:
        + Return no of byte in RX FIFO
*/
static uint8_t NRF24_get_pld_size_of_rx_pipe(uint8_t pipe_idx)
{
    uint8_t data_reg = 0;
    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_Read(NRF24_REG_RX_PW_P0 + pipe_idx, &data_reg, 1, 100))
    {
        return 0x00;
    }
    return data_reg;
}

/*
    Description:
        + This function is used to RX FIFO byte
    Input Parameter:
        + pld_size: this is size of PLD
    Output Parameter:
        + pld: this is array data PLD packet
        + Return status to know the process is success or failed
*/
static NRF24_SERVICE_STATUS NRF24_get_pld_data_in_RX_FIFO(uint8_t *pld, uint8_t pld_size)
{
    if(NRF24_HAL_STATUS_FAIL == NRF24_HAL_CMD(NRF24_CMD_READ_RX_PAYLOAD, &pld, 1, 100))
    {
        return NRF24_SERVICE_STATUS_FAIL;
    }
    return NRF24_SERVICE_STATUS_OK;
}

/*
    Description:
        + This function is used to Check Nrf24 IRQ PIN status signal
            If IRQ singal is RX_DR. We will check RX_FIFO and get data from it.
            If IRQ signal is MAX_RT. We will change nRF device to PRX-mode.
            If IRQ signal is TX_DS. We have 2 sittuation.
                1st: If TX-FIFO is out of pkt. We will change to PRX mode
                2nd: If TX-FIFO is have pkt. We will transmit next pkt. This 
                     This sittuation will happend again and we will do it util out of pkt in TX-FIFO
    Input Parameter:
        + NULL
    Output Parameter:
        + NULL
*/
static uint8_t NRF24_Handle_IRQ_Pin_Signal(void)
{
    NRF24_IRQ irq_status;

    irq_status = NRF24_GetIRQ_Status();

    switch (irq_status)
    {
        case NRF24_IRQ_RX_DATA_READY:
            {
                if(NRF24_SERVICE_STATUS_FAIL == NRF24_Read_RX_PLD(&global_rx_pkt))
                {
                    memset(&global_rx_pkt, 0, sizeof(NRF24_RX_PLD));
                }
                else
                {
                    nrf24_ser_handler.transmit_done = false;
                    nrf24_ser_handler.rx_data_ready = true;
                    nrf24_ser_handler.transmit_err  = false;
                }
            }
            break;
        
        case NRF24_IRQ_MAX_RETRANSMIT:
            {
                (void)NRF24_Set_RX_TX(NRF24_TRANSCIVER_MODE_RX);
                nrf24_ser_handler.mode          = NRF24_TRANSCIVER_MODE_RX;
                nrf24_ser_handler.transmit_done = false;
                nrf24_ser_handler.rx_data_ready = false;
                nrf24_ser_handler.transmit_err  = true;
            }
            break;
        
        case NRF24_IRQ_TX_DATA_SENT:
            {
                if((NRF24_TXFIFO_STATUS_ERROR == NRF24_Get_TX_FIFO_Status()) ||\
                   (NRF24_TXFIFO_STATUS_EMPTY == NRF24_Get_TX_FIFO_Status()))
                {
                    (void)NRF24_Set_RX_TX(NRF24_TRANSCIVER_MODE_RX);
                    nrf24_ser_handler.mode          = NRF24_TRANSCIVER_MODE_RX;
                    nrf24_ser_handler.transmit_done = true;
                    nrf24_ser_handler.rx_data_ready = false;
                    nrf24_ser_handler.transmit_err  = false;
                }
            }
            break;
    }
    return 0;
}

/*
    Description:
        + When time_out interrupt is signal. 
            If nRF24 device is PRX mode. We will check TX_FIFO have data or not
                If TX_FIFO have data. We will check RPD to know another nodes are transmitting pkt or not
                    If not, we will change nNF24 device to TX mode and transmit data in TX_FIFO
                    If have, we will bypass IRQ signal.
            If nRF24 device is PTX mode. We will bypass this signal
    Input Parameter:
        + NULL
    Output Parameter:
        + NULL
*/
static uint8_t NRF24_Handle_Timer_IRQ(void)
{
    if(nrf24_ser_handler.mode == NRF24_TRANSCIVER_MODE_RX)
    {
        if((NRF24_TXFIFO_STATUS_ERROR != NRF24_Get_TX_FIFO_Status()) ||\
            (NRF24_TXFIFO_STATUS_EMPTY != NRF24_Get_TX_FIFO_Status()))
        {
            (void)NRF24_Set_RX_TX(NRF24_TRANSCIVER_MODE_TX);
            nrf24_ser_handler.mode = NRF24_TRANSCIVER_MODE_TX;
        }
    }
    return 0;
}
