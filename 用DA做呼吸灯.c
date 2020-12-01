#include<reg52.h>
#define uchar unsigned char
sbit dacs=P3^2;
sbit dawr=P3^6;
sbit wela=P2^7;
sbit dula=P2^6;
sbit beep=P2^3;
void delay(uchar z);
void main()
{
	int i;
	wela=0;
	dula=0;
	dacs=0;
	dawr=0;
	P0=0;
	while(1)
	{
		for(i=255;i>=0;i-=5)
		{
			delay(100);
			P0=i;
			if(i==0)
			{
				beep=0;
				delay(100);
				beep=1;
			}
		}
		for(i=0;i<256;i+=5)
		{
			delay(100);
			P0=i;
			if(i==255)
			{
				beep=0;
				delay(100);
				beep=1;
			}
		}
	}
}
void delay(uchar z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}