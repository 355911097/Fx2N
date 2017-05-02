#include "RCC.h"

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
/**************************************************************/
//�� �� ���� RCC_Config()
//�� �� �ߣ� 
//��ڲ����� ��
//����˵���� ϵͳʱ������
//**************************************************************/
void RCC_Config(void)
{
	ErrorStatus HSEStartUpStatus;	//����ṹ��
	/* RCC system reset(for debug purpose)������ RCC�Ĵ�������Ϊȱʡֵ */
	RCC_DeInit();
	/* Enable HSE �����ⲿ���پ���HSE��*/
	RCC_HSEConfig(RCC_HSE_ON);
	/* Wait till HSE is ready �ȴ� HSE ����*/
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if (HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer Ԥȡָ����ʹ��*/
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		/* Flash 2 wait state ���ô�����ʱֵ*/
		FLASH_SetLatency(FLASH_Latency_2);

		/* HCLK = SYSCLK ���� AHB ʱ�ӣ�HCLK��*/
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		/* PCLK2 = HCLK ���ø��� AHB ʱ�ӣ�PCLK2��*/
		RCC_PCLK2Config(RCC_HCLK_Div1);

		/* PCLK1 = HCLK/1 ���õ��� AHB ʱ�ӣ�PCLK1��*/
		RCC_PCLK1Config(RCC_HCLK_Div1);

		/* PLLCLK = 12MHz * 6 = 72 MHz ���� PLL ʱ��Դ����Ƶϵ��*/
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);

		/* Enable PLL ʹ�ܻ���ʧ�� PLL*/
		RCC_PLLCmd(ENABLE);

		/* Wait till PLL is ready �ȴ�ָ���� RCC ��־λ���óɹ� �ȴ�PLL��ʼ���ɹ�*/
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}
		/* Select PLL as system clock source ����ϵͳʱ�ӣ�SYSCLK�� ����PLLΪϵͳʱ��Դ*/
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Wait till PLL is used as system clock source �ȴ�PLL�ɹ�������ϵͳʱ�ӵ�ʱ��Դ*/
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}
}
