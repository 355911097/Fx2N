#include "usartdma.h"

extern uint8_t PLC_UART_T_BUFFER[0x8f];
extern uint8_t PLC_UART_BUFFER[0x8f];	
extern  uint8_t PLC_UART_RECEIVE_CNT;

void DMA_Uart_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	/* DMA clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // ����DMA1ʱ��
	
	//=DMA_Configuration==============================================================================//
 
 	/*--- LUMMOD_UART_Tx_DMA_Channel DMA Config ---*/
 	DMA_Cmd(DMA1_Channel4, DISABLE);                           // ��DMAͨ��
	DMA_DeInit(DMA1_Channel4);                                 // �ָ�ȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);// ���ô��ڷ������ݼĴ���
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)PLC_UART_T_BUFFER;         // ���÷��ͻ������׵�ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                      // ��������λĿ�꣬�ڴ滺���� -> ����Ĵ���
	DMA_InitStructure.DMA_BufferSize = 0X8F;                     // ��Ҫ���͵��ֽ�����������ʵ��������Ϊ0����Ϊ��ʵ��Ҫ���͵�ʱ�򣬻��������ô�ֵ
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // �����ַ�������ӵ�����������������DMA�Զ�ʵ�ֵ�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // �ڴ滺������ַ���ӵ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // �������ݿ��8λ��1���ֽ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // �ڴ����ݿ��8λ��1���ֽ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // ���δ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 // ���ȼ�����
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // �ر��ڴ浽�ڴ��DMAģʽ
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);               // д������
	DMA_ClearFlag(DMA1_FLAG_GL4);                                 // ���DMA���б�־
	DMA_Cmd(DMA1_Channel4, DISABLE); // �ر�DMA
	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);            // ��������DMAͨ���ж�
    
	/*--- LUMMOD_UART_Rx_DMA_Channel DMA Config ---*/
	DMA_Cmd(DMA1_Channel5, DISABLE);                           // ��DMAͨ��
	DMA_DeInit(DMA1_Channel5);                                 // �ָ�ȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);// ���ô��ڽ������ݼĴ���
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)PLC_UART_BUFFER;         // ���ý��ջ������׵�ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      // ��������Ϊ����Դ������Ĵ��� -> �ڴ滺����
	DMA_InitStructure.DMA_BufferSize = 0x8f;                     // ��Ҫ�����ܽ��յ����ֽ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // �����ַ�������ӵ�����������������DMA�Զ�ʵ�ֵ�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // �ڴ滺������ַ���ӵ���
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // �������ݿ��8λ��1���ֽ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // �ڴ����ݿ��8λ��1���ֽ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           // ���δ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 // ���ȼ�����
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // �ر��ڴ浽�ڴ��DMAģʽ
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);               // д������
	DMA_ClearFlag(DMA1_FLAG_GL5);                                 // ���DMA���б�־
	DMA_Cmd(DMA1_Channel5, ENABLE);                            // ��������DMAͨ�����ȴ���������
}

//============================================================//
//DMA ����Ӧ��Դ��
void DMA1_Channel4_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_FLAG_TC4))
	{
		LumMod_Uart_DAM_Tx_Over();
	}
}
void LumMod_Uart_DAM_Tx_Over(void)
{
	DMA_ClearFlag(DMA1_FLAG_GL4);         // �����־
	DMA_Cmd(DMA1_Channel4, DISABLE);   // �ر�DMAͨ��
}
	
//============================================================//
//DMA ����Ӧ��Դ��
 void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  // �����ж�
	{
		LumMod_Uart_DMA_Rx_Data();
		USART_ReceiveData( USART1 ); // Clear IDLE interrupt flag bit
	}
}
void LumMod_Uart_DMA_Rx_Data(void)
{
	uint8_t i;
	DMA_Cmd(DMA1_Channel5, DISABLE);       // �ر�DMA ����ֹ����
	DMA_ClearFlag( DMA1_FLAG_GL5 );           // ��DMA��־λ
	PLC_UART_RECEIVE_CNT = 0x8F - DMA_GetCurrDataCounter(DMA1_Channel5); //��ý��յ����ֽ���
	DMA1_Channel5->CNDTR = 0x8f;    //  ���¸�ֵ����ֵ��������ڵ��������ܽ��յ�������֡��Ŀ;
	for(i=0;i<PLC_UART_RECEIVE_CNT;i++)
		PLC_UART_BUFFER[i] &= 0x7f;
 /*	DMA_Cmd(DMA1_Channel5, ENABLE);      	 //DMA �������ȴ����ݡ�ע�⣬����жϷ�������֡�����ʺܿ죬MCU����������˴ν��յ������ݣ��ж��ַ������ݵĻ������ﲻ�ܿ������������ݻᱻ���ǡ���2�ַ�ʽ�����
	1. �����¿�������DMAͨ��֮ǰ����LumMod_Rx_Buf��������������ݸ��Ƶ�����һ�������У�Ȼ���ٿ���DMA��Ȼ�����ϴ����Ƴ��������ݡ�
	2. ����˫���壬��LumMod_Uart_DMA_Rx_Data�����У���������DMA_MemoryBaseAddr �Ļ�������ַ����ô�´ν��յ������ݾͻᱣ�浽�µĻ������У������ڱ����ǡ�*/
}
