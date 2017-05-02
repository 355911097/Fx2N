#include "PLC_PUBLIC.H"
#include "stm32f10x.h"

extern  uint8_t PLC_UART_T_BUFFER[0x8f];
extern uint8_t  PLC_UART_BUFFER[0x8f];	
extern uint8_t  PLC_UART_RECEIVE_CNT;	
extern  uint8_t PLC_UART_T_CNT;		//���ͼ���

/******************************************************************************/
//uint8  	PLC_UART_BUFFER[0x8F]; 	//���ջ���	 BUFFER
//uint8 	PLC_UART_T_BUFFER[0x8F]; 	//���ͻ���
//uint8	PLC_UART_RECEIVE_CNT;	//���ռ���
//uint8	PLC_UART_T_CNT;		//���ͼ���
/*
const uint8 hex[256]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//16
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//32
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//48
0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,	//64
0,10,11,12,13,14,15,0,0,0,0,0,0,};
*/
/*******************************************************************************
�������ܣ�����У��� 
*******************************************************************************/
uint8_t check(uint8_t *MyD_str )                 
{	
	char sum=3;
	MyD_str++;
	while(*MyD_str!=0x03)
	{
		sum+=*MyD_str;
		MyD_str++;
	}
	return  (sum);
}

/*******************************************************************************
�������ƣ�PLC_Comm_Bit_ADD
�������ܣ�
��ڲ�����          
���ڲ�����
********************************************************************************/

uint16 PLC_Comm_Bit_ADD(uint16 comm_add)
{
	uint8 h_add;
	h_add=comm_add/0x100;
	comm_add=comm_add&0xFF;
	switch (h_add)
	{
		case 0x14: {comm_add+=0x0000;}break; 
		case 0x15: {comm_add+=0x0100;}break; 
		case 0x16: {comm_add+=0x0200;}break; 
		case 0x17: {comm_add+=0x0300;}break; 
		case 0x12: {comm_add+=0x0400;}break; 
		case 0x0C: {comm_add+=0x0500;}break; 
		case 0x10: {comm_add+=0x0600;}break; 
		case 0x28: {comm_add+=0x1600;}break; 
		case 0x00: {comm_add+=0x0800;}break; 
		case 0x01: {comm_add+=0x0900;}break; 
		case 0x02: {comm_add+=0x0A00;}break; 
		case 0x03: {comm_add+=0x0B00;}break; 
		case 0x04: {comm_add+=0x0C00;}break; 
		case 0x05: {comm_add+=0x0D00;}break; 
		case 0x0F: {comm_add+=0x0E00;}break; 
		case 0x27: {comm_add+=0x1E00;}break; 
		case 0x0E: {comm_add+=0x0F00;}break; 

		case 0x06: {comm_add += 0x5800;}break; 
		case 0x07: {comm_add += 0x5900;}break; 
		case 0x08: {comm_add += 0x5A00;}break; 
		case 0x09: {comm_add += 0x5B00;}break; 	
		case 0x0A: {comm_add += 0x5C00;}break; 
		case 0x0B: {comm_add += 0x5D00;}break;
		
		default:   {comm_add =0x1000;}break; 
	} 
	return comm_add;
}

/*******************************************************************************
�������ƣ�PLC_2AsciiHex(����ͨ��ר��)
�������ܣ���2��Asciiת��Hex
��ڲ�����Ascii1��һ��Ascii��,Ascii2�ڶ���Ascii��          
���ڲ�����ת���õ�Hex��(��һ��Ascii���ڸ�4λ,�ڶ���Ascii���ڵ�4λ)
********************************************************************************/

uint8 PLC_2AsciiHex(char Ascii1,char Ascii2)
{
	return ((hex[Ascii1]*0x10)+hex[Ascii2]);
}

/*******************************************************************************
�������ƣ�PLC_4AsciiHex(����ͨ��ר��)
�������ܣ���4��Asciiת��Hex
��ڲ�����Ascii1��һ��Ascii��,Ascii2�ڶ���Ascii��          
���ڲ�����ת���õ�Hex��
********************************************************************************/

uint16 PLC_4AsciiHex(char Ascii1,char Ascii2,char Ascii3,char Ascii4)
{
	return ((hex[Ascii1]*0x1000)+(hex[Ascii2]*0x100)+(hex[Ascii3]*0x10)+hex[Ascii4]);
}

/*******************************************************************************
�������ƣ�PLC_BufAsciiHex(����ͨ��ר��)
�������ܣ���4��Asciiת��Hex
��ڲ�����Ascii1��һ��Ascii��,Ascii2�ڶ���Ascii��          
���ڲ�����ת���õ�Hex��
********************************************************************************/

uint8 PLC_Buf2AsciiHex(uint8 S_Add)
{
	return((hex[PLC_UART_BUFFER[S_Add]]*0x10)+hex[PLC_UART_BUFFER[S_Add+1]]);
}

/*******************************************************************************
�������ƣ�PLC_BufAsciiHex(����ͨ��ר��)
�������ܣ���4��Asciiת��Hex
��ڲ�����Ascii1��һ��Ascii��,Ascii2�ڶ���Ascii��          
���ڲ�����ת���õ�Hex��
********************************************************************************/

uint16 PLC_Buf4AsciiHex(uint8 S_Add)
{
	return((hex[PLC_UART_BUFFER[S_Add]]*0x1000)+(hex[PLC_UART_BUFFER[S_Add+1]]*0x100)+(hex[PLC_UART_BUFFER[S_Add+2]]*0x10)+hex[PLC_UART_BUFFER[S_Add+3]]);
}

/*******************************************************************************
�������ƣ�PLC_Comm_Bit_ADD
�������ܣ�ͨ������E7,E8�ĵ�ַ��ӳ��
��ڲ�����ͨ�ŵ�ַ(BIT��ַ)          
���ڲ�����ӳ���ʵ�ʵ�ַ(BIT��ַ)
********************************************************************************/

void PLC_Iap_data_rst(void)
{
	uint32 i;
	
	
	for(i=PLC_PROG_B_START_ADD-4;i<(PLC_PROG_B_START_ADD+0X8004);i++)
	{
		PLC_RAM8(i)=0xff;
	}


}

/*******************************************************************************
�������ƣ�PLC_Comm_Byte_ADD
�������ܣ�
��ڲ�����          
���ڲ�����
********************************************************************************/

uint16 PLC_Comm_Byte_ADD(uint16 comm_add)
{
	if(comm_add>=0x4000&&comm_add<=0x7E7F){comm_add-=0x3000;} 
else if(comm_add>=0x0E00&&comm_add<=0x0FFF){comm_add-=0x0000;} 
else if(comm_add>=0x1000&&comm_add<=0x11FF){comm_add-=0x0800;} 
else if(comm_add>=0x0A00&&comm_add<=0x0B8F){comm_add-=0x0000;} 
else if(comm_add>=0x0C00&&comm_add<=0x0CDF){comm_add-=0x0000;} 
else if(comm_add>=0x1400&&comm_add<=0x16FF){comm_add+=0x4900;} 
else if(comm_add>=0x1790&&comm_add<=0x18FF){comm_add+=0x4400;} 
else if(comm_add>=0x0280&&comm_add<=0x02FC){comm_add-=0x0280;} 
else if(comm_add>=0x0240&&comm_add<=0x024F){comm_add-=0x01C0;} 	
else if(comm_add>=0x0180&&comm_add<=0x018F){comm_add-=0x00E0;} 
else if(comm_add>=0x0200&&comm_add<=0x021F){comm_add-=0x0140;} 
else if(comm_add>=0x0500&&comm_add<=0x051F){comm_add-=0x0240;} 
else if(comm_add<=0x00BF){comm_add+=0x0100;} 
else if(comm_add>=0x01E0&&comm_add<=0x01FF){comm_add-=0x0020;} 
else if(comm_add>=0x04E0&&comm_add<=0x04FF){comm_add-=0x0120;} 
else if(comm_add>=0x01C0&&comm_add<=0x01DF){comm_add+=0x0020;} 

else if(comm_add>=0x00C0&&comm_add<=0x017F){comm_add+=0x5760;} 

else{comm_add=0x0200;}//��Ч��ַ
return comm_add;
}

/*******************************************************************************
�������ƣ�PLC_Comm_Batch()
�������ܣ�
��ڲ�����
���ڲ�����
********************************************************************************/

void PLC_Comm_Batch(void)
{
	uint32  PLC_Ins_S_Add,PLC_Ins_S_Add2,PLC_Ins_E_Add;
	uint16  PLC_Ins_Count,PLC_Ins_Temp_Add,temp;
	PLC_Ins_S_Add=PLC_Ins1400_S_Add+4;
	PLC_Ins_E_Add=PLC_Ins_S_Add+(PLC_RAM8(PLC_Ins1400_S_Add)*2);//ȡ�Ĵ�������
	PLC_Ins_S_Add2=PLC_Ins1790_S_Add;

	
	for(;PLC_Ins_E_Add>PLC_Ins_S_Add;PLC_Ins_S_Add+=2) //�Ĵ���ֵ(16λ����)
	{
		PLC_Ins_Temp_Add=PLC_Comm_Byte_ADD(PLC_RAM16(PLC_Ins_S_Add));
		PLC_RAM16(PLC_Ins_S_Add2)=PLC_RAM16(PLC_R_START_ADD+PLC_Ins_Temp_Add);
		PLC_Ins_S_Add2+=2;
		if(PLC_Ins_Temp_Add>=0x0C00&&PLC_Ins_Temp_Add<0x0CDF)	//�����Ƿ�C200-C255
		{
			PLC_RAM16(PLC_Ins_S_Add2)=PLC_RAM16(PLC_R_START_ADD+PLC_Ins_Temp_Add+2);
			PLC_Ins_S_Add2+=2;
		}
	}
	PLC_Ins_E_Add=PLC_Ins_S_Add+(PLC_RAM8(PLC_Ins1400_S_Add+2)*2);//ȡλ����
	PLC_Ins_Count=0;
	for(;PLC_Ins_E_Add>PLC_Ins_S_Add;PLC_Ins_S_Add+=2) //λֵ(λ����)
	{
		temp = PLC_Comm_Bit_ADD(PLC_RAM16(PLC_Ins_S_Add));
		if((temp & 0xF000) == 0x5000)
		{
			if(PLC_BIT_M1536_TEST(temp & 0x0FFF))
			{
				PLC_RAM8(PLC_Ins_S_Add2+(PLC_Ins_Count/8))|=PLC_BIT_OR[PLC_Ins_Count%8];
			}
			else
			{
				PLC_RAM8(PLC_Ins_S_Add2+(PLC_Ins_Count/8))&=PLC_BIT_AND[PLC_Ins_Count%8];
			}
		}
		else
		{
			if(PLC_BIT_TEST(temp))
			{
				PLC_RAM8(PLC_Ins_S_Add2+(PLC_Ins_Count/8))|=PLC_BIT_OR[PLC_Ins_Count%8];
			}
			else
			{
				PLC_RAM8(PLC_Ins_S_Add2+(PLC_Ins_Count/8))&=PLC_BIT_AND[PLC_Ins_Count%8];
			}
		}
		PLC_Ins_Count++;
	}
}

/*******************************************************************************
�������ƣ�PLC_Comm_Send()
�������ܣ���ָ����ַ�е������򴮿��ͳ�
��ڲ�����data_s_add �������ݿ�ʼ��ַ(��ַֻ���ǼĴ�����,�����ǳ�����)
          Send_count ���͸���          
���ڲ�������
********************************************************************************/
void PLC_Comm_Send(uint16 data_s_add,uint8 count)
{
	uint32 PLC_Send_S_Add,PLC_Send_E_Add;
	uint8  PLC_Send_temp,PLC_Send_Sum;
	if(data_s_add>=0x5b90&&data_s_add<=0x5b90)
	{
		PLC_Comm_Batch();
	}	//�������ݶ�
	if(data_s_add>=0x8000&&data_s_add<=0xFD1C)	//��������bedc/*0xFD1C����160000��0xbedc,����8000��*/	
	{
		PLC_Send_S_Add=(PLC_PROG_START_ADD+data_s_add)-0x8000;
	}
	else
	{
		PLC_Send_S_Add=PLC_R_START_ADD+data_s_add;
	}	
	//��RAM����ʼ��ַ
	PLC_Send_E_Add=PLC_Send_S_Add+count;
	if((PLC_Send_E_Add>=PLC_R_START_ADD&&PLC_Send_E_Add<=PLC_R_END_ADD)||(PLC_Send_E_Add>=PLC_PROG_START_ADD&&PLC_Send_E_Add<=PLC_PROG_END_ADD))//���Ե�ַ�Ƿ񳬳�
	{
		PLC_UART_T_CNT=0;
		PLC_UART_T_BUFFER[0]=0x02;
		PLC_UART_T_CNT++;
		PLC_Send_Sum=0x03;
		for(;PLC_Send_E_Add>PLC_Send_S_Add;PLC_Send_S_Add++)
		{
			PLC_Send_temp=asc[PLC_RAM8(PLC_Send_S_Add)/0x10];
			PLC_UART_T_BUFFER[PLC_UART_T_CNT]=PLC_Send_temp;
			PLC_UART_T_CNT++;
			PLC_Send_Sum+=PLC_Send_temp;
			PLC_Send_temp=asc[PLC_RAM8(PLC_Send_S_Add)&0x0f];
			PLC_UART_T_BUFFER[PLC_UART_T_CNT]=PLC_Send_temp;
			PLC_UART_T_CNT++;
			PLC_Send_Sum+=PLC_Send_temp;
		}
		PLC_UART_T_BUFFER[PLC_UART_T_CNT]=0x03;
		PLC_UART_T_CNT++;
		PLC_UART_T_BUFFER[PLC_UART_T_CNT]=asc[PLC_Send_Sum/0x10];
		PLC_UART_T_CNT++;
		PLC_UART_T_BUFFER[PLC_UART_T_CNT]=asc[PLC_Send_Sum%0x10];
		PLC_UART_T_CNT++;
//		UART_COUNT=PLC_UART_T_CNT;UART_COUNT2=0; 
	}
	else
	{
//		USART_SendData1(USART1,0x15);
		PLC_UART_T_BUFFER[0]=0x15;
		PLC_UART_T_CNT=1;	
	}
}


/*******************************************************************************
�������ƣ�PLC_UART_CMD()
�������ܣ��������ݴ���
��ڲ�����
          
���ڲ�����
********************************************************************************/
void PLC_UART_CMD(void)
{
	uint8_t PLC_Uart_Sum; 
	if (PLC_UART_RECEIVE_CNT != 0)
	{
		if(PLC_UART_BUFFER[0]==0x05)
		{
			PLC_UART_RECEIVE_CNT=0;
			PLC_UART_T_BUFFER[0]=0x06;
			PLC_UART_T_CNT=1;	
			//USART_SendData1(USART1,0x06);
		}
		else 
			{
			if(PLC_UART_BUFFER[0]==0x02)
			{
				if(PLC_UART_BUFFER[PLC_UART_RECEIVE_CNT-3]==0x03)
				{ 
					PLC_Uart_Sum=check(PLC_UART_BUFFER);
					if(PLC_Uart_Sum/0x10==hex[PLC_UART_BUFFER[PLC_UART_RECEIVE_CNT-2]]&&PLC_Uart_Sum%0x10==hex[PLC_UART_BUFFER[PLC_UART_RECEIVE_CNT-1]])//��У��
					{
						PLC_UART_RECEIVE_CNT=0;
						PLC_UART_HANDLE();		 //����������
						PLC_UART_RECEIVE_CNT=0;
					}						   //��ȷ��������		
					else 
					{
						PLC_UART_RECEIVE_CNT=0;
						//USART_SendData1(USART1,0x15);//���󷵻ش�����(NCK)
						PLC_UART_T_BUFFER[0]=0x15;
						PLC_UART_T_CNT=1;	
						PLC_UART_RECEIVE_CNT=0; //�ô����־
					}
				}
			}	
			else
			{
				PLC_UART_RECEIVE_CNT=0;
				PLC_UART_T_BUFFER[0]=0x15;
				PLC_UART_T_CNT=1;	
				//USART_SendData1(USART1,0x15);				
			}  
			}		
	}
}
/*******************************************************************************
�������ƣ� PLC_UART_HANDLE(void)
�������ܣ� ����������
��ڲ�����
���ڲ�����
********************************************************************************/
uint8 PLC_PROG_W_BIT=0;
void PLC_UART_HANDLE(void)
{
	uint32 PLC_Uart_Add,PLC_Uart_Add_temp,i;
	uint16 PLC_Uart_S_Add;
	uint8  PLC_Uart_Temp,PLC_Uart_Count;	
	if(PLC_UART_BUFFER[1]==0X30)	  //0������
	{
		PLC_Uart_S_Add=PLC_Buf4AsciiHex(2);
		PLC_Uart_Count=PLC_Buf2AsciiHex(6);
		PLC_Comm_Send(PLC_Uart_S_Add,PLC_Uart_Count);   
	}
 	/********************************END������********************************************/
 
 	else 
	if(PLC_UART_BUFFER[1]==0X31)  //1д����
	{
		PLC_Uart_Add=PLC_R_START_ADD+PLC_Buf4AsciiHex(2);	//��ʼ��ַ
		 PLC_Uart_Add_temp=PLC_Uart_Add+PLC_Buf2AsciiHex(6);
		 PLC_Uart_Temp=8;
		 for(;PLC_Uart_Add_temp>PLC_Uart_Add;PLC_Uart_Add++)
		{
			PLC_RAM8(PLC_Uart_Add)=PLC_Buf2AsciiHex(PLC_Uart_Temp);			 
		 	PLC_Uart_Temp+=2;
		 }
		PLC_UART_T_BUFFER[0]=0x06;
		PLC_UART_T_CNT=1;	
	 	//USART_SendData1(USART1,0x06);
	}
	/********************************ENDд����********************************************/

 	else 
	if(PLC_UART_BUFFER[1]==0X37) //7ǿ��ON
 	{
 		PLC_Uart_S_Add=(hex[PLC_UART_BUFFER[4]]<<12)+(hex[PLC_UART_BUFFER[5]]<<8)+(hex[PLC_UART_BUFFER[2]]<<4)+hex[PLC_UART_BUFFER[3]];
		 PLC_BIT_ON(PLC_Uart_S_Add);
		 PLC_UART_T_BUFFER[0]=0x06;
		PLC_UART_T_CNT=1;
		// USART_SendData1(USART1,0x06);
	}
	/********************************ENDǿ��ON********************************************/

 	else
	if(PLC_UART_BUFFER[1]==0X38) //8ǿ��OFF
 	{
 		PLC_Uart_S_Add=(hex[PLC_UART_BUFFER[4]]<<12)+(hex[PLC_UART_BUFFER[5]]<<8)+(hex[PLC_UART_BUFFER[2]]<<4)+hex[PLC_UART_BUFFER[3]];
		 PLC_BIT_OFF(PLC_Uart_S_Add);
		 PLC_UART_T_BUFFER[0]=0x06;
		PLC_UART_T_CNT=1;
		// USART_SendData1(USART1,0x06);
	}
	/********************************ENDǿ��OFF********************************************/

	 else 
	if(PLC_UART_BUFFER[1]==0X45) //ǿ��FNC
	{
		if(PLC_UART_BUFFER[2]==0x30)
		{
			if(PLC_UART_BUFFER[3]==0x30)//E00������30 31 43 32
			{
				PLC_Uart_S_Add=PLC_Comm_Byte_ADD((hex[PLC_UART_BUFFER[4]]<<12)+(hex[PLC_UART_BUFFER[5]]<<8)+(hex[PLC_UART_BUFFER[6]]<<4)+hex[PLC_UART_BUFFER[7]]);
				PLC_Uart_Count=(hex[PLC_UART_BUFFER[8]]<<4)+hex[PLC_UART_BUFFER[9]];
				PLC_Comm_Send(PLC_Uart_S_Add,PLC_Uart_Count);
			}
			/*********************END������*************************/
			
		    	else if(PLC_UART_BUFFER[3]==0x31)//E01������
			{
				PLC_Uart_S_Add=(hex[PLC_UART_BUFFER[4]]<<12)+(hex[PLC_UART_BUFFER[5]]<<8)+(hex[PLC_UART_BUFFER[6]]<<4)+hex[PLC_UART_BUFFER[7]];
   	           		PLC_Uart_Count=(hex[PLC_UART_BUFFER[8]]<<4)+hex[PLC_UART_BUFFER[9]];
	             		PLC_Comm_Send(PLC_Uart_S_Add,PLC_Uart_Count);
			}
			/*********************END������*************************/
			
		  	 else
			{
				PLC_UART_T_BUFFER[0]=0x15;
				PLC_UART_T_CNT=1;
			  //	USART_SendData1(USART1,0x15);
			}	 //ͨ�ų���
		}

		else if(PLC_UART_BUFFER[2]==0x34)//�������ɶ��˼?
		{
			 if(PLC_UART_BUFFER[3]==0x31)
			 {
				PLC_UART_T_CNT=0;
				PLC_UART_T_BUFFER[PLC_UART_T_CNT]=0x02;
				PLC_UART_T_CNT++;
				PLC_UART_T_BUFFER[PLC_UART_T_CNT]=0x31;
				PLC_UART_T_CNT++;
				PLC_UART_T_BUFFER[PLC_UART_T_CNT]=0x38;
				PLC_UART_T_CNT++;
				PLC_UART_T_BUFFER[PLC_UART_T_CNT]=0x30;
				PLC_UART_T_CNT++;
				PLC_UART_T_BUFFER[PLC_UART_T_CNT]=0x36;
				PLC_UART_T_CNT++;
				PLC_UART_T_BUFFER[PLC_UART_T_CNT]=0x34;
				PLC_UART_T_CNT++;
				PLC_UART_T_BUFFER[PLC_UART_T_CNT]=0x03;
				PLC_UART_T_CNT++;				
				PLC_UART_T_BUFFER[PLC_UART_T_CNT]=0x30;
				PLC_UART_T_CNT++;
				PLC_UART_T_BUFFER[PLC_UART_T_CNT]=0x36;
				PLC_UART_T_CNT++;				
//				UART_COUNT=PLC_UART_T_CNT;UART_COUNT2=0; 
				// PLC_Uart_S_Add=(hex[PLC_UART_BUFFER[4]]<<12)+(hex[PLC_UART_BUFFER[5]]<<8)+(hex[PLC_UART_BUFFER[6]]<<4)+hex[PLC_UART_BUFFER[7]];
				// PLC_Uart_Count=(hex[PLC_UART_BUFFER[8]]<<12)+(hex[PLC_UART_BUFFER[9]]<<8)+(hex[PLC_UART_BUFFER[10]]<<4)+hex[PLC_UART_BUFFER[11]];
				// PLC_Comm_Send(PLC_Uart_S_Add,PLC_Uart_Count);
					
			 }
			 else
			{
				PLC_UART_T_BUFFER[0]=0x15;
				PLC_UART_T_CNT=1;
		  	//	USART_SendData1(USART1,0x15);
			}	
	
		}
				
		else if(PLC_UART_BUFFER[2]==0x31)
		{
			if(PLC_UART_BUFFER[3]==0x30)//E10д����
			{
				PLC_Uart_Add_temp=(hex[PLC_UART_BUFFER[4]]<<12)+(hex[PLC_UART_BUFFER[5]]<<8)+(hex[PLC_UART_BUFFER[6]]<<4)+hex[PLC_UART_BUFFER[7]];	//��ʼ��ַ
				PLC_Uart_Add=PLC_R_START_ADD+PLC_Comm_Byte_ADD(PLC_Uart_Add_temp);	
				PLC_Uart_Add_temp=PLC_Uart_Add+(hex[PLC_UART_BUFFER[8]]<<4)+hex[PLC_UART_BUFFER[9]];
				PLC_Uart_Temp=10;
				for(;PLC_Uart_Add_temp>PLC_Uart_Add;PLC_Uart_Add++)
				{
					PLC_RAM8(PLC_Uart_Add)=(hex[PLC_UART_BUFFER[PLC_Uart_Temp]]<<4)+hex[PLC_UART_BUFFER[PLC_Uart_Temp+1]];			 			
			 		PLC_Uart_Temp+=2;
					}
			 		PLC_UART_T_BUFFER[0]=0x06;
					PLC_UART_T_CNT=1;
		 		   	//USART_SendData1(USART1,0x06);
				 }
			/*********************ENDд����*************************/
			
			else if(PLC_UART_BUFFER[3]==0x31)//E11д����
			{
				PLC_Uart_Add=PLC_PROG_B_START_ADD+(hex[PLC_UART_BUFFER[4]]<<12)+(hex[PLC_UART_BUFFER[5]]<<8)+(hex[PLC_UART_BUFFER[6]]<<4)+hex[PLC_UART_BUFFER[7]]-0X8000;//0X805C;
				PLC_Uart_Add_temp=PLC_Uart_Add+(hex[PLC_UART_BUFFER[8]]<<4)+hex[PLC_UART_BUFFER[9]];
				PLC_Uart_Temp=10;
				if(PLC_Uart_Add==PLC_PROG_B_START_ADD)
				{
					//PLC_Iap_data_rst();
					for(i=0;i<0x800;i++)
						PLC_RAM8(PLC_PROG_B_START_ADD+0x5c+i) =PLC_RAM8(PLC_PROG_START_ADD2+i);
					PLC_PROG_W_BIT=2;
				}
				if(PLC_Uart_Add==PLC_PROG_B_START_ADD+0x5c)
				{
					for(i=0;i<0x5c;i++)
						PLC_RAM8(PLC_PROG_B_START_ADD+i) =PLC_RAM8(PLC_PROG_START_ADD+i);
					//PLC_Iap_data_rst();
					PLC_PROG_W_BIT=1;
				}
		 		for(;PLC_Uart_Add_temp>PLC_Uart_Add;PLC_Uart_Add++)
				{
					PLC_RAM8(PLC_Uart_Add)=(hex[PLC_UART_BUFFER[PLC_Uart_Temp]]<<4)+hex[PLC_UART_BUFFER[PLC_Uart_Temp+1]];			 			
			 		PLC_Uart_Temp+=2;
				}
				PLC_UART_T_BUFFER[0]=0x06;
				PLC_UART_T_CNT=1;
		 		//USART_SendData1(USART1,0x06);
			}
			/*********************ENDд����*************************/
			
			else
			{
				PLC_UART_T_BUFFER[0]=0x15;
				PLC_UART_T_CNT=1;
				//USART_SendData1(USART1,0x15);
			}//ͨ�ų���
		}
		else if(PLC_UART_BUFFER[2]==0x37)//E7ǿ��ON
		{
			PLC_Uart_S_Add=PLC_Comm_Bit_ADD((hex[PLC_UART_BUFFER[5]]*0x1000)\
			   								   +(hex[PLC_UART_BUFFER[6]]*0x100)\
											   +(hex[PLC_UART_BUFFER[3]]*0x10)\
											   +hex[PLC_UART_BUFFER[4]]);	
			if((PLC_Uart_S_Add & 0xF000) == 0x5000)
                        PLC_BIT_M1536_ON(PLC_Uart_S_Add & 0x0FFF);	
			else
                        PLC_BIT_ON(PLC_Uart_S_Add);
			//USART_SendData1(USART1,0x06);
			PLC_UART_T_BUFFER[0]=0x06;
			PLC_UART_T_CNT=1;			
		}
		else if(PLC_UART_BUFFER[2]==0x38)//E8ǿ��OFF
		{
			PLC_Uart_S_Add=PLC_Comm_Bit_ADD((hex[PLC_UART_BUFFER[5]]*0x1000)\
			   								    +(hex[PLC_UART_BUFFER[6]]*0x100)\
											    +(hex[PLC_UART_BUFFER[3]]*0x10)\
											    +hex[PLC_UART_BUFFER[4]]);	
			if((PLC_Uart_S_Add & 0xF000) == 0x5000)
                        PLC_BIT_M1536_OFF(PLC_Uart_S_Add & 0x0FFF);	
			else
                        PLC_BIT_OFF(PLC_Uart_S_Add);
			//USART_SendData1(USART1,0x06);
			PLC_UART_T_BUFFER[0]=0x06;
			PLC_UART_T_CNT=1;	
		}
		else if(PLC_UART_BUFFER[2]==0x36)//���ߡ��������PLC�ڴ�..������PLC�ڴ�
		{
			if(PLC_UART_BUFFER[3]==0x30)
			{
				//��Ҫ�����롣	
				//USART_SendData1(USART1,0x06);
				PLC_UART_T_BUFFER[0]=0x06;
				PLC_UART_T_CNT=1;
			}
			else if(PLC_UART_BUFFER[3]==0x31)
			{
				//��Ҫ�����롣	
				//USART_SendData1(USART1,0x06);
				PLC_UART_T_BUFFER[0]=0x06;
				PLC_UART_T_CNT=1;
			}
			else if(PLC_UART_BUFFER[3]==0x32)
			{
				//��Ҫ�����롣	
				//USART_SendData1(USART1,0x06);
				PLC_UART_T_BUFFER[0]=0x06;
				PLC_UART_T_CNT=1;
			}
			else if(PLC_UART_BUFFER[3]==0x33)
			{
				//��Ҫ�����롣	
				//USART_SendData1(USART1,0x06);
				PLC_UART_T_BUFFER[0]=0x06;
				PLC_UART_T_CNT=1;
			}
			else if(PLC_UART_BUFFER[3]==0x34)
			{
				//��Ҫ�����롣	
				//USART_SendData1(USART1,0x06);
				PLC_UART_T_BUFFER[0]=0x06;
				PLC_UART_T_CNT=1;
			}
			else
			{
		  		//USART_SendData1(USART1,0x15);
		  		PLC_UART_T_BUFFER[0]=0x15;
				PLC_UART_T_CNT=1;
			}	
		}
		else
		{
			//USART_SendData1(USART1,0x15);
			PLC_UART_T_BUFFER[0]=0x15;
			PLC_UART_T_CNT=1;
		}  //ͨ�ų���
	}/********************************ENDǿ��FNC********************************************/
	 else if(PLC_UART_BUFFER[1]==0x42)	//����������ɡ�������
 	{
 		if(PLC_PROG_W_BIT==1)
		{
			Plc_Program_iap();	//д�����
			PLC_PROG_W_BIT=0;

		}	
		 if(PLC_PROG_W_BIT==2)
		{
			Plc_parameter_iap();//д�����
			PLC_PROG_W_BIT=0;
		}	
		 PLC_RUN_BIT=0;
		D8065=0;
		// USART_SendData1(USART1,0x06);
		 PLC_UART_T_BUFFER[0]=0x06;
		PLC_UART_T_CNT=1;
	}

 	else if(PLC_UART_BUFFER[1]==0x34)
 	{
 		//USART_SendData1(USART1,0x06);
		 PLC_UART_T_BUFFER[0]=0x06;
		PLC_UART_T_CNT=1;
	}
 	else
	{
		 PLC_UART_T_BUFFER[0]=0x15;
		PLC_UART_T_CNT=1;
		//USART_SendData1(USART1,0x15);
	}//ͨ�ų���
}


