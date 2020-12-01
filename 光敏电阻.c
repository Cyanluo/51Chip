#include<reg52.h>
sbit GUANG=P2^2;
sbit beep=P2^3;
void main()
{
	while(1)
	{
		if(GUANG==0)
		{P1=0x00;
		beep=0;}
		else
		{P1=0xff;
		beep=1;} 
	}
}