#ifndef __usartdma_H__
#define __usartdma_H__

#include "stm32f10x.h"

//USART �� DMA Ӳ����ʼ������
 
void DMA_Uart_Init(void);
void LumMod_Uart_DAM_Tx_Over(void);
void LumMod_Uart_DMA_Rx_Data(void);


#endif

