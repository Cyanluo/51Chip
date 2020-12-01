/*******************************************************************/
/*���⡢�������̵������Ƶ�										   */
/*��������Ԥ��ֵ��ʱ���ƣ���λ�����ڣ�						       */
/*������Ƴ����������		                                       */
/*******************************************************************/
#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
sbit jdq=P3^0;							  //�̵������ƿ�
sbit sk=P2^0;							  //�������������ƿ�
sbit ir=P3^3;							  //������տ�
sbit hw=P1^7;							  //��������Ӧ�ӿ�
uchar jiema[2]={0,0};					  
uchar shu[4],flag,a;

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)					  //��ʱ���z����
		for(y=110;y>0;y--);
}

void delay1(uchar x)
{
	uchar i;
	while(x--)
	{
		for(i=0;i<13;i++){}
	}
}

void inti()								 //��ʼ���ⲿ�ж�1
{
	EA=1;
	EX1=1;
	IT1=1;
}
void bianma()  interrupt 2	 
{
	uchar x,y,num=0;
	EX1=0;
	delay1(15);								 //����
	if(ir==1)								
	{
		EX1=1;
		return ;		
	}
	while(!ir)
		{
			delay1(1);
		}
	for(x=0;x<4;x++)						 //��ȡ32λ4������
	{
		for(y=0;y<8;y++)
		{
			while(ir)
			{
				delay1(1);
			}
			while(!ir)
			{
				delay1(1);
			}
			while(ir)						  //����ߵ�ƽ��ʱ��
			{
				delay1(1);			
				num++;
				if(num>=30)					  //ʱ�䳬����Χ��ֹ��ȡ����
				{
					EX1=1;
					return ;
				}
			}								
			shu[x]=shu[x]>>1;
			if(num>=8)						   //����ʱ���ж�1��0
			{
				shu[x]=shu[x]|0x80;
			}
			num=0;
		}
	}
		if(shu[2]==~shu[3])					   //����������䷴���Ƿ��Ӧ
		{
			flag=1;							   //�������º����������Ʊ�־��λ
		}
		EX1=1;
}

void main()
{
	jdq=0;
	inti();
	while(1)
	{
		if(sk==0)										//��������Ԥ��ֵ
		{
			jdq=1;										//����
			delay(1000);
			delay(1000);
			jdq=0;										//��ʱ��ص�
		}
		if(flag==1)
		{
			jiema[0]=shu[2]>>4;	  
			jiema[1]=shu[2]&0x0f;
			if(jiema[0]==1&&jiema[1]==6)				 //���ⰴ������ֵ92
			{
				jdq=1;									 //����
			}
			if(jiema[0]==1&&jiema[1]==9)				 //���ⰴ������ֵ93
			{
				jdq=0;									//�ص�
			}
			
	
			flag=0;
		}
/*		if(hw==1)										//��������Ӧ
		{
			jdq=1;										//����
			delay(1000);
			delay(1000);
			jdq=0;										//��ʱ��ص�	 
		}	  */
	}
}