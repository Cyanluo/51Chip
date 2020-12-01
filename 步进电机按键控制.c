/*******************************************************************/
/*����ʽ�����������											   */
/*������������Ϊ����ת����ת�����١�����						   */
/*�����ǰ��λ��ʾ�ٶȣ�01-05�� ��һλ��ʾ����0������1��ת		   */
/*******************************************************************/
#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned int
uchar table1[8] ={0x0c,0x06,0x03,0x09,0x03,0x06,0x0c,0x09};//��ת �����ͨ����,��ת �����ͨ���� 
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x79,0x38,0x3f};

sbit zhen=P3^4;
sbit fan=P3^5;
sbit jia=P3^6;
sbit jian=P3^7;
sbit wela=P2^7;
sbit dula=P2^6;

void delay(uint z);
void keyscan();
void run();
void change();
void display(uchar bai,uchar shi,uchar ge);

uchar toward,shi,ge,b;
char speed=1;

void main()
{
	delay(50);						 //�ȴ������ȶ�
	while(1)
	{
	
		run();						  //�������
		change();					  //�������ʾ����ת��
	}
}

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void keyscan()
{
	if(zhen==0)							 //��ת��
	 {
	 	delay(2);				 
		if(zhen==0)
		{
			toward=0;
			while(!zhen);
		}
	 }
	 if(fan==0)							 //��ת��
	 {
	 	delay(2);
		if(fan==0)
		{
			toward=4;
			while(!fan);
		}
	 }
	 if(jia==0)							  //���ټ�
	 {
	 	delay(2);
		if(jia==0)
		{
			speed--;
			if(speed<=1)
			{
			speed=1;
			}
			while(!jia);
		}
	 }
	 if(jian==0)							//���ټ�
	 {
	 	delay(2);
		if(jian==0)
		{
			speed++;
			if(speed>=5)
			{
				speed=5;
			}
			while(!jian);
		}
	 }
}

void run()										   //����
{
	 uchar i,j;
	 for(j=0;j<10;j++)
		{
		 for(i=toward;i<toward+4;i++)
		 {
		 	P1=table1[i];
			display(shi,ge,b);						//����ʾ��������ʱ
		 }
			keyscan();	
		 }
		 
}

void change()										 //����ת��
{
	uchar a;
	a=speed;
	a=6-a;
	shi=a/10;
	ge=a%10;
	if(toward==0)
		b=0;
	else
		b=1;
}

void display(uchar bai,uchar shi,uchar ge)			   //����ܶ�̬��ʾ
{
	wela=1;
	P0=0xfe;
	wela=0;
	P0=0xff;								//��Ӱ
	dula=1;
	P0=table[bai];
	dula=0;
	delay(speed);
	P0=0xff;
	
	wela=1;
	P0=0xfd;
	wela=0;			  
	P0=0xff;					
	dula=1;
	P0=table[shi];
	dula=0;
	delay(speed);
	P0=0xff;
	
	wela=1;
	P0=0xf7;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[ge];
	dula=0;
	delay(speed-1);
	P0=0xff;
}









 