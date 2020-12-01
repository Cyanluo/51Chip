#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int				 
sbit wela=P2^7;
sbit dula=P2^6;
sbit ir=P3^3;
uchar jiema[2]={0,0};
uchar shu[4],flag;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void delay1(uchar x)
{
	uchar i;
	while(x--)
	{
		for(i=0;i<13;i++){}
	}
}
void delay(uint z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void display()
{
	dula=0;
	P0=table[jiema[0]];
	dula=1;
	dula=0;
	wela=0;
	P0=0xfe;
	wela=1;
	wela=0;
	delay(5);
	P0=table[jiema[1]];
	dula=1;
	dula=0;
	P0=0xfd;
	wela=1;
	wela=0;
	delay(5);
}
void inti()
{
	EA=1;
	EX1=1;
	IT1=1;
}
void bianma()  interrupt 2	 
{
	uchar x,y,num=0;
	EX1=0;
	delay1(15);
	if(ir==1)
	{
		EX1=1;
		return ;		
	}
	while(!ir)
		{
			delay1(1);
		}
	for(x=0;x<4;x++)
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
			while(ir)
			{
				delay1(1);			
				num++;
				if(num>=30)
				{
					EX1=1;
					return ;
				}
			}								
			shu[x]=shu[x]>>1;
			if(num>=8)
			{
				shu[x]=shu[x]|0x80;
			}
			num=0;
		}
	}
		if(shu[2]==~shu[3])
		{
			flag=1;
		}
		EX1=1;
}
void main()
{
	uchar a;
	inti();
	while(1)
	{
	if(flag==1)
	{
		jiema[0]=shu[2]>>4;
		jiema[1]=shu[2]&0x0f;

		flag=0;
	}
	
		display();
			
	}
}

