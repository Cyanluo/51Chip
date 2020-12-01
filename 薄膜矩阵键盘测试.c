#include<reg52.h>
sbit key=P0^4;
sbit key_1=P0^0;
sbit key_2=P0^1;
sbit key_3=P0^2;
sbit key_4=P0^3;


void delay1(unsigned int z)						 //zºÁÃëÑÓÊ±
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void main()
{
	key=0;
	if(key_1==0)
	{
		delay1(2);
		if(key_1==0)
		{
			P1=1;
		}
	}
	if(key_2==0)
	{
		delay1(2);
		if(key_2==0)
		{
			P1=2;
		}
	}
	if(key_3==0)
	{
		delay1(2);
		if(key_3==0)
		{
			P1=3;
		}
	}
	if(key_4==0)
	{
		delay1(2);
		if(key_4==0)
		{
			P1=4;
		}
	}
}