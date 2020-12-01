#include<reg52.h>
#include<intrins.h>
sbit weld=P2^7;
sbit deld=P2^6;
sbit beep=P2^3;
#define uchar unsigned char	
#define  uint unsigned int
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
int temp;
void delay(uint n);
void main()
{	uint i;
	temp=0xfe;
	P1=temp;
	delay(1000);
	weld=1;
	P0=0xc0;
	weld=0;
	while(1)
	{
		for(i=0;i<16;i++)
		{
			deld=1;
			P0=table[i];
			deld=0;
			temp=_crol_(temp,1);
			P1=temp;
			beep=0;
			delay(500);
			beep=1;
			delay(500);
		}
	}
}
void delay(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
		for(j=110;j>0;j--);
}