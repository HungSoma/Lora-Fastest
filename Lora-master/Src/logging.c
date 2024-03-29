#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "My_type.h"
#include "logging.h"
//#include "SW_Timer.h"
//TxPacket myTxPacket;
//LoraPtr myLoraPtr;

extern TIM_HandleTypeDef htim2; 
//LoraTimeTest LoraTime;
/**
  * @brief  	Data send over USB with format "numTick:Data\n"
  * @param  	data, length of data you want to transmit
  * @retval 	None
  */
void print_data(char* data, u8 len_transmit)
{
        char packet_transmit[64]; // 11+1+48+1 = 61
        char data_transmit[48];
        strncpy(data_transmit,data,len_transmit);	 // coppy len_transmit characters from data to data_transmit
        data_transmit[len_transmit] = '\0';				// gan ky tu null cho vi tri cuoi cua data_transmit
        sprintf((char*)packet_transmit,"%d:%s\n",HAL_GetTick(),data_transmit);  
        CDC_Transmit_FS((uint8_t*)packet_transmit,strlen((char*)packet_transmit)); 
}
/**
  * @brief  	Start Timer 2
  * @param  	None
  * @retval 	None
  */
void timer_measure_start(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}
/**
  * @brief  	Stop Timer 2
  * @param  	None
  * @retval 	counter in us
  */
u32 timer_measure_stop(void)
{
	HAL_TIM_Base_Stop_IT(&htim2);
        u32 count = __HAL_TIM_GET_COUNTER(&htim2);  
        __HAL_TIM_SET_COUNTER(&htim2,0);
        return count;
}

/*void HAL_SYSTICK_Callback(void){
        SW_TIMER_ISR();
}*/


