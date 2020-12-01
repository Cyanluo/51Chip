/*******************************************************************/
/*                        人体红外感应							   */
/*                          蜂鸣器响						  	   */
/*******************************************************************/
#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
sbit hw=P1^7;
sbit beep=P2^3;

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void main()
{
	uint i;
	while(1)
	{
		if(hw==1)
		{			
			beep=0;
					
		}
		else
		{
			 beep=1;
			
		}
		
	}
}