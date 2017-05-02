;/****************************************Copyright (C)**************************************************
;**                               
;**                                                                            
;**                                   
;**--------------�ļ���Ϣ--------------------------------------------------------------------------------
;**��   ��   ��: PLC_DataOperating.c
;**��        ��: V2.1
;**��   ��   ��: LuHeDing
;**����޸�����: 2010��05��08��
;**��        ��: PLC���ݲ�����������
;** 
;********************************************************************************************************/

#include "PLC_PUBLIC.H"
/***********************************************
  ��������:PLC �������Ͳ���(pc(data))
  ���:����ȡ������
  ����:��16λΪ����ʶ���  
  	   0������=��Ч����; 
	   1=����;2=����;3=����K1(M);4=����K2(M);5=����K3(M);6=����K4(M);
	   7=����K5(M);8=����K6(M);9=����K7(M);A=����K8(M);B=λ����;
	   ��16λΪ��ַ   
***********************************************/
uint32 PLC_DataTypeTest(uint32 Data)
{
	uint32 cmd;
	uint32 TempAdd=((Data&0x0f0000)/0x100)+(Data%0x100);
	cmd=Data&0xff00ff00;
	switch(cmd)
	{	
		case 0x80008200:{cmd=0x010000;debug_send("��������H\r\n");}break;//����
		case 0x80008000:{cmd=0x010000;debug_send("����\r\n");}break;//����
		case 0x86008600:{cmd=0x020000|(TempAdd+0x1000);debug_send("����D0-D999\r\n");}break;//����D0-D999
		case 0x88008600:{cmd=0x020000|(((Data&0xFF0000)/0x100)+(Data%0x100)+0x17D0);debug_send("����D1000-D7999 \r\n");}break;//����D1000-D7999  
		case 0x80008600:{cmd=0x020000|(TempAdd+0x0E00);debug_send("����D8000-D8255\r\n");}break;//����D8000-D8255
		case 0x82008600:{cmd=0x020000|(TempAdd+0x0800);debug_send("����T0-T255\r\n");}break;//����T0-T255
		case 0x84008600:{cmd=0x020000|(TempAdd+0x0A00);debug_send("����C0-C255\r\n");}break;//����C0-C255
		case 0x82008400:{cmd=0x030000|TempAdd;debug_send("����K1(M0) M10 0A 84 08 82\r\n");}break;//����K1(M0) M10 0A 84 08 82
		case 0x84008400:{cmd=0x040000|TempAdd;debug_send("����K2(M0) M10 0A 84 08 84\r\n");}break;//����K2(M0) M10 0A 84 08 84
		case 0x86008400:{cmd=0x050000|TempAdd;debug_send("����K3(M0) M10 0A 84 08 86\r\n");}break;//����K3(M0) M10 0A 84 08 86
		case 0x88008400:{cmd=0x060000|TempAdd;debug_send("����K4(M0) M10 0A 84 08 88\r\n");}break;//����K4(M0) M10 0A 84 08 88
		case 0x8A008400:{cmd=0x070000|TempAdd;debug_send("����K5(M0) M10 0A 84 08 8A\r\n");}break;//����K5(M0) M10 0A 84 08 8A
		case 0x8C008400:{cmd=0x080000|TempAdd;debug_send("����K6(M0) M10 0A 84 08 8C\r\n");}break;//����K6(M0) M10 0A 84 08 8C
		case 0x8E008400:{cmd=0x090000|TempAdd;debug_send("����K7(M0) M10 0A 84 08 8E\r\n");}break;//����K7(M0) M10 0A 84 08 8E
		case 0x90008400:{cmd=0x0A0000|TempAdd;debug_send("����K8(M0) M10 0A 84 08 90\r\n");}break;//����K8(M0) M10 0A 84 08 90
		case 0x80008400:{cmd=0x0B0000|TempAdd;debug_send("Bit����\r\n");}break;//Bit����
		//(Z)
	 	case 0x8600A600://����D0-D999 Z0-Z3
		{
			debug_send("����D0-D999 Z0-Z3\r\n");
			cmd=Data&0x00f00000;
			switch(cmd)
		    	{
		    		case 0x00000000:{cmd=D8028;debug_send("Z0\r\n");}break;   //Z0
				case 0x00400000:{cmd=D8182;debug_send("Z1\r\n");}break;   //Z1
				case 0x00800000:{cmd=D8184;debug_send("Z2\r\n");}break;   //Z2
				case 0x00c00000:{cmd=D8186;debug_send("Z3\r\n");}break;   //Z3
				default:{cmd=0xFF6000;debug_send("��ַZ��ַδ֪\r\n");}break;	//��ַZ��ַδ֪
			}
		 	cmd=(cmd*2)+TempAdd+0x1000;
		 	if(cmd>0x4E7E||cmd<0x1000)
			{
				cmd=0xFF6000;debug_send("���ݶ�ȡ��ַ����\r\n");
			}//���ݶ�ȡ��ַ����
		 	else 
				cmd|=0x020000;
		}break;//END����D0-D999 Z0-Z3
		case 0x8700A600://����D0-D999 Z4-Z7
	 	{
			debug_send("����D0-D999 Z4-Z7\r\n");
			cmd=Data&0x00f00000;
			switch(cmd)
			{
				case 0x00000000:{cmd=D8188;debug_send("Z4\r\n");}break;   //Z4
				case 0x00400000:{cmd=D8190;debug_send("Z5\r\n");}break;   //Z5
				case 0x00800000:{cmd=D8192;debug_send("Z6\r\n");}break;   //Z6
				case 0x00c00000:{cmd=D8194;debug_send("Z7\r\n");}break;   //Z7
				default:{cmd=0xFF6000;debug_send("��ַZ��ַδ֪\r\n");}break;	//��ַZ��ַδ֪
			}
		 	cmd=(cmd*2)+TempAdd+0x1000;
		 	if(cmd>0x4E7E||cmd<0x1000)
			{
				cmd=0xFF6000;debug_send("���ݶ�ȡ��ַ����\r\n");
			}//���ݶ�ȡ��ַ����
			else 
				cmd|=0x020000;
		}break;//END ����D0-D999 Z4-Z7
		case 0x8800A600://����D1000-D7999 Z0-Z3
	 	{
			debug_send("����D1000-D7999 Z0-Z3\r\n");
			cmd=(Data&0x00f00000)-((Data&0x00F00000)%0x00400000);
			switch(cmd)
			{
				case 0x00000000:{cmd=D8028;debug_send("Z0\r\n");}break;   //Z0
				case 0x00400000:{cmd=D8182;debug_send("Z1\r\n");}break;   //Z1
				case 0x00800000:{cmd=D8184;debug_send("Z2\r\n");}break;   //Z2
				case 0x00c00000:{cmd=D8186;debug_send("Z3\r\n");}break;   //Z3
				default:{cmd=0xFF6000;debug_send("��ַZ��ַδ֪\r\n");}break;	//��ַZ��ַδ֪
			}
		 	cmd=((cmd*2)+TempAdd+(((Data&0x00F00000)%0x00400000)/0x100)+0x17D0);
		 	if(cmd>0x4E7E||cmd<0x1000)
			{
				cmd=0xFF6000;debug_send("���ݶ�ȡ��ַ����\r\n");
			}//���ݶ�ȡ��ַ����
		 	else 
				cmd|=0x020000;
		}break;//END ����D1000-D7999 Z0-Z3
		case 0x8900A600://����D1000-D7999 Z4-Z7
	 	{	
			debug_send("����D1000-D7999 Z4-Z7\r\n");
			cmd=(Data&0x00f00000)-((Data&0x00F00000)%0x00400000);
		 	switch(cmd)
		    	{
				case 0x00000000:{cmd=D8188;debug_send("Z4\r\n");}break;   //Z4
				case 0x00400000:{cmd=D8190;debug_send("Z5\r\n");}break;   //Z5
				case 0x00800000:{cmd=D8192;debug_send("Z6\r\n");}break;   //Z6
				case 0x00c00000:{cmd=D8194;debug_send("Z7\r\n");}break;   //Z7
				default:{cmd=0xFF6000;debug_send("��ַZ��ַδ֪\r\n");}break;	//��ַZ��ַδ֪
			}
			cmd=((cmd*2)+TempAdd+(((Data&0x00F00000)%0x00400000)/0x100)+0x17D0);
			if(cmd>0x4E7E||cmd<0x1000)
			{
				debug_send("���ݶ�ȡ��ַ����\r\n");
				cmd=0xFF6000;
			}//���ݶ�ȡ��ַ����
		 	else 
				cmd|=0x020000;
		}break;//END ����D1000-D7999 Z4-Z7
		default:{cmd=0xFF6000;debug_send("�Ƿ�����\r\n");}break;	//�Ƿ�����
	}
	return cmd;
}

/***********************************************
  ��������:ר���ڿ�ʼ����������ݲ���
  ��ڲ���:pc���ݿ�ʼ��ַ
           count���Ը���
***********************************************/
void PLC_ProgDataTest(uint32 pc,uint8 count)
{
	uint32 temp;
	 for(;count!=0;count--)
	 {
	 	temp=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
		pc+=4;
	 	if((temp&0xff0000)==0x010000)
		{
			;
		}
	 	else if((temp&0xff0000)==0x020000)
		{
			if((temp&0xFFFF)>0x4E7F)
			{
				PLC_PROG_ERROR(1020);
				debug_send("�ֽڲ���������\r\n");
			}
		}//�ֽڲ���������
		 else if((temp&0xff0000)==0x030000){;}//K1(M0)
		 else if((temp&0xff0000)==0x040000){;}//K2(M0)
		 else if((temp&0xff0000)==0x050000){;}//K3(M0)
		 else if((temp&0xff0000)==0x060000){;}//K4(M0)
	 	else if((temp&0xff0000)==0x070000){;}//K5(M0)
		 else if((temp&0xff0000)==0x080000){;}//K6(M0)
	 	else if((temp&0xff0000)==0x090000){;}//K7(M0)
	 	else if((temp&0xff0000)==0x0A0000){;}//K8(M0)
		 else if((temp&0xff0000)==0x0B0000){;}//Bit
	 	else {PLC_PROG_ERROR(1020);count=0;debug_send("����������\r\n");}//����������
	 }//end for	
}


/***********************************************
  ��������:�ӳ����з��ص�ַ
***********************************************/
uint16 PLC_ProgAddReturn(uint32 pc)
{
	return PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc))&0xffff;
}


/***********************************************
  ��������:�ӳ����з�������
  0������=��Ч����; 
  1=����;2=����;3=����K1(M);4=����K2(M);5=����K3(M);6=����K4(M);
  7=����K5(M);8=����K6(M);9=����K7(M);A=����K8(M);B=λ����;
***********************************************/
uint16 PLC_ProgTypeReturn(uint32 pc)
{
	return (PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc))&0xff0000)/0x10000;
}

/***********************************************
  ��������:�ӳ����з������ͼ���ַ
  0������=��Ч����; 
  1=����;2=����;3=����K1(M);4=����K2(M);5=����K3(M);6=����K4(M);
  7=����K5(M);8=����K6(M);9=����K7(M);A=����K8(M);B=λ����;
***********************************************/
uint32 PLC_ProgTypeAddReturn(uint32 pc)
{return PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
}


/***********************************************
  ��������:�ֽ�����������λ
***********************************************/
void PLC_ByteReset(uint16 BitStartAdd,uint16 BitEndAdd)
{
	uint32 SAdd,EAdd;
	uint16 Temp;
	if(BitStartAdd>BitEndAdd)//�����ַ����
	{
		Temp=BitStartAdd;
		BitStartAdd=BitEndAdd;
		BitEndAdd=Temp;
	}
	SAdd=PLC_R_START_ADD+BitStartAdd;
	EAdd=PLC_R_START_ADD+BitEndAdd;
	while (SAdd<=EAdd)
	{
		if(SAdd%4==0&&(EAdd-SAdd)>=4)
		{
			PLC_RAM32(SAdd)=0;
			SAdd+=4;
		}
		else
		{
			PLC_RAM8(SAdd)=0;
			SAdd++;
		}
	} 
}

/***********************************************
  ��������:λ����������λ
***********************************************/
void PLC_BitReset(uint16 BitStartAdd,uint16 BitEndAdd)
{
	while (BitStartAdd<=BitEndAdd)
	{
		if(BitStartAdd%8==0&&(BitEndAdd-BitStartAdd)>=8)
	 	{
	 		PLC_RAM8(PLC_R_START_ADD+(BitStartAdd/8))=0;
			BitStartAdd+=8;
		}
		else
		{
			PLC_BIT_OFF(BitStartAdd);BitStartAdd++;
		}
	}
}

/***********************************************
  ��������:λ���ݶ�
  ��ڲ���:BitStartAdd ��ʼ��ַ >=0x0000 <=0x0FFF
		   BitCount    ��ȡ����1-32
  ���ڲ���:���ض�ȡ����ֵ
***********************************************/
uint32 PLC_BitDataRead(uint16 BitStartAdd,uint8 BitCount)
{uint32 r_data=0;
 uint16 EndAdd=BitStartAdd+BitCount;
while (1)
 {EndAdd--;
  if(PLC_BIT_TEST(EndAdd))r_data|=0x01;
  if(BitStartAdd==EndAdd)return r_data;
  r_data<<=1;}
}

/***********************************************
  ��������:λ����д
  ��ڲ���:BitStartAdd ��ʼ��ַ >=0x0000 <=0x0FFF
		   BitCount    д�����1-64
		   data		   Ҫд�������
  ���ڲ���:��
***********************************************/
void PLC_BitDataWrite(uint16 BitStartAdd,uint8 BitCount,uint32 data)
{uint16 EndAdd=BitStartAdd+BitCount;
 for(;BitStartAdd<EndAdd;BitStartAdd++)
   {if(data&0x01)PLC_BIT_ON(BitStartAdd);
	else PLC_BIT_OFF(BitStartAdd);
	data>>=1;}
}

/***********************************************
  ��������:�ֽ�����64λд
  1=����;2=����;3=����K1(M);4=����K2(M);5=����K3(M);6=����K4(M);
  7=����K5(M);8=����K6(M);9=����K7(M);A=����K8(M);
***********************************************/
void PLC_ByteWrite64(uint32 pc,uint32 Data,uint32 Data2)
{uint32 cmd_add;
 uint32 cmd;
 cmd_add=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
 cmd=cmd_add&0xff0000;
 cmd_add&=0x0000ffff;
 switch(cmd)
	{case 0x00020000://����
		{PLC_RAM16(PLC_R_START_ADD+cmd_add)=Data;
		 PLC_RAM16(PLC_R_START_ADD+cmd_add+2)=(Data/0x10000);
		 PLC_RAM16(PLC_R_START_ADD+cmd_add+4)=Data2;
		 PLC_RAM16(PLC_R_START_ADD+cmd_add+6)=(Data2/0x10000);
		}break;   //END ����
	 case 0x00030000:
	 	{PLC_BitDataWrite(cmd_add,4,Data);
		 PLC_BitDataWrite(cmd_add+4,4,Data2);}break;    //����K1(M)
	 case 0x00040000:
	 	{PLC_BitDataWrite(cmd_add,8,Data);
		 PLC_BitDataWrite(cmd_add+8,8,Data2);}break;    //����K2(M)
	 case 0x00050000:
	 	{PLC_BitDataWrite(cmd_add,12,Data);
		 PLC_BitDataWrite(cmd_add+12,12,Data2);}break;   //����K3(M)
	 case 0x00060000:
	 	{PLC_BitDataWrite(cmd_add,16,Data);
		 PLC_BitDataWrite(cmd_add+16,16,Data2);}break;   //����K4(M)
	 case 0x00070000:
	 	{PLC_BitDataWrite(cmd_add,20,Data);
		 PLC_BitDataWrite(cmd_add+20,20,Data2);}break;   //����K5(M)
	 case 0x00080000:
	 	{PLC_BitDataWrite(cmd_add,24,Data);
		 PLC_BitDataWrite(cmd_add+24,24,Data2);}break;   //����K6(M)
	 case 0x00090000:
	 	{PLC_BitDataWrite(cmd_add,28,Data);
		 PLC_BitDataWrite(cmd_add+28,28,Data);}break;   //����K7(M)
	 case 0x000A0000:
	 	{PLC_BitDataWrite(cmd_add,32,Data);
		 PLC_BitDataWrite(cmd_add+32,32,Data);}break;   //����K8(M)
	 default:{PLC_PROG_ERROR(0x12);}break;	//��֧�ֲ���
	}

}

/***********************************************
  ��������:�ֽ�����32λд
  1=����;2=����;3=����K1(M);4=����K2(M);5=����K3(M);6=����K4(M);
  7=����K5(M);8=����K6(M);9=����K7(M);A=����K8(M);
***********************************************/
void PLC_ByteWrite32(uint32 pc,uint32 Data)
{uint32 cmd_add;
 uint32 cmd;
 cmd_add=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
 cmd=cmd_add&0xff0000;
 cmd_add&=0x0000ffff;
 switch(cmd)
	{case 0x00020000://����
		{PLC_RAM16(PLC_R_START_ADD+cmd_add)=Data;
		 PLC_RAM16(PLC_R_START_ADD+cmd_add+2)=Data/0x10000;
		}break;   //END ����
	 case 0x00030000:{PLC_BitDataWrite(cmd_add,4,Data);}break;    //����K1(M)
	 case 0x00040000:{PLC_BitDataWrite(cmd_add,8,Data);}break;    //����K2(M)
	 case 0x00050000:{PLC_BitDataWrite(cmd_add,12,Data);}break;   //����K3(M)
	 case 0x00060000:{PLC_BitDataWrite(cmd_add,16,Data);}break;   //����K4(M)
	 case 0x00070000:{PLC_BitDataWrite(cmd_add,20,Data);}break;   //����K5(M)
	 case 0x00080000:{PLC_BitDataWrite(cmd_add,24,Data);}break;   //����K6(M)
	 case 0x00090000:{PLC_BitDataWrite(cmd_add,28,Data);}break;   //����K7(M)
	 case 0x000A0000:{PLC_BitDataWrite(cmd_add,32,Data);}break;   //����K8(M)
	 default:{PLC_PROG_ERROR(0x12);}break;	//��֧�ֲ���
	}

}

/***********************************************
  ��������:�ֽ�����16λд
  1=����;2=����;3=����K1(M);4=����K2(M);5=����K3(M);6=����K4(M);
***********************************************/
void PLC_ByteWrite16(uint32 pc,uint16 Data)
{
	uint32 cmd_add;
	uint32 cmd;
	cmd_add=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
	cmd=cmd_add&0xff0000;
	cmd_add&=0x0000ffff;
	switch(cmd)
	{
		case 0x00020000:{PLC_RAM16(PLC_R_START_ADD+cmd_add)=Data;}break;   //����
	 	case 0x00030000:{PLC_BitDataWrite(cmd_add,4,Data);}break;    //����K1(M)
	 	case 0x00040000:{PLC_BitDataWrite(cmd_add,8,Data);}break;    //����K2(M)
	 	case 0x00050000:{PLC_BitDataWrite(cmd_add,12,Data);}break;   //����K3(M)
	 	case 0x00060000:{PLC_BitDataWrite(cmd_add,16,Data);}break;   //����K4(M)
	 	default:{PLC_PROG_ERROR(0x12);}break;	//��֧�ֲ���
	}
}

/***********************************************
  ��������:�ֽ�����32λ��
  1=����;2=����;3=����K1(M);4=����K2(M);5=����K3(M);6=����K4(M);
  7=����K5(M);8=����K6(M);9=����K7(M);A=����K8(M);
***********************************************/
uint32 PLC_ByteRead32(uint32 pc)
{uint32 cmd_add;
 uint32 cmd;
 cmd_add=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
 cmd=cmd_add&0xff0000;
 cmd_add&=0x0000ffff;
 switch(cmd)
	{case 0x00010000://����
		{cmd=((PLC_RAM8(pc+2)*0X100)+PLC_RAM8(pc)+
		      (PLC_RAM8(pc+6)*0X1000000)+(PLC_RAM8(pc+4)*0X10000));
		}break;   //END ����
	 case 0x00020000://����
		{cmd=PLC_RAM16(PLC_R_START_ADD+cmd_add)+(PLC_RAM16(PLC_R_START_ADD+cmd_add+2)*0x10000);
		}break;   //END ����
	 case 0x00030000:{cmd=PLC_BitDataRead(cmd_add,4);}break;    //����K1(M)
	 case 0x00040000:{cmd=PLC_BitDataRead(cmd_add,8);}break;    //����K2(M)
	 case 0x00050000:{cmd=PLC_BitDataRead(cmd_add,12);}break;   //����K3(M)
	 case 0x00060000:{cmd=PLC_BitDataRead(cmd_add,16);}break;   //����K4(M)
	 case 0x00070000:{cmd=PLC_BitDataRead(cmd_add,20);}break;   //����K5(M)
	 case 0x00080000:{cmd=PLC_BitDataRead(cmd_add,24);}break;   //����K6(M)
	 case 0x00090000:{cmd=PLC_BitDataRead(cmd_add,28);}break;   //����K7(M)
	 case 0x000A0000:{cmd=PLC_BitDataRead(cmd_add,32);}break;   //����K8(M)
	 default:{PLC_PROG_ERROR(0x12);}break;	//��֧�ֲ���
	}
return cmd;
}

/***********************************************
  ��������:�ֽ�����16λ��
  1=����;2=����;3=����K1(M);4=����K2(M);5=����K3(M);6=����K4(M);
***********************************************/
uint16 PLC_ByteRead16(uint32 pc)
{
	uint32 cmd_add;
	uint32 cmd;
	cmd_add=PLC_DataTypeTest((PLC_RAM16(pc+2)*0X10000)+PLC_RAM16(pc));
	cmd=cmd_add&0xff0000;
	cmd_add&=0x0000ffff;
	switch(cmd)
	{
		case 0x00010000:
		{
			cmd=(PLC_RAM8(pc+2)*0X100)+PLC_RAM8(pc);
		}break;//END ����
		case 0x00020000://����
		{
			cmd=PLC_RAM16(PLC_R_START_ADD+cmd_add)+(PLC_RAM16(PLC_R_START_ADD+cmd_add+2)*0x10000);
		}break;   //END ����
		case 0x00030000:
		{
			cmd=PLC_BitDataRead(cmd_add,4);
		}break;    //����K1(M)
		case 0x00040000:
		{
			cmd=PLC_BitDataRead(cmd_add,8);
		}break;    //����K2(M)
		case 0x00050000:
		{
			cmd=PLC_BitDataRead(cmd_add,12);
		}break;   //����K3(M)
		case 0x00060000:
		{
			cmd=PLC_BitDataRead(cmd_add,16);
		}break;   //����K4(M)
		default:
		{
			PLC_PROG_ERROR(0x12);
		}break;	//��֧�ֲ���
	}
	return cmd;
}
