#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
sbit beep=P2^3;

void delay(uint z)						 //zºÁÃëÑÓÊ±
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void main()
{
	int i;
	
	while(1)
	{

	for(i=0;i<1000;i++)
	{
		P1=0;
		delay(100);
		P1=1;
		delay(100);
	} 	  
	}
}