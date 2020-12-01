#include<reg52.h>
sbit beep=P2^3;
sbit weld=P2^7;
sbit deld=P2^6;
#define uint unsigned int
#define uchar unsigned char
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uint num=0;
uint tt=0;
main()
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	EX0=1;
	IT0=1;
	TMOD=0x01;
	TR0=1;	
	weld=1;		   
	P0=0xc0;
	weld=0;
	deld=1;
	P0=0x3f;
	deld=0;
	while(1)
	{
			if(tt==20)
		{
			 beep=1;
			 tt=0;
			 num++;
			 deld=1;
			 if(num==16)
			 num=0;
			 P0=table[num];
			 deld=0;
		}
	}

}
void   time_control() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	tt++;
}			 
void   fengmingqi() interrupt 0
{
	beep=0;
}