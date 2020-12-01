#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
void display(uchar aa,uchar bb,uchar cc);
sbit adrd=P3^7;
sbit wela=P2^7;
sbit dula=P2^6;
sbit adwr=P3^6;
uchar bai,shi,ge,a;
uint num;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x79,0x38,0x3f};
const uchar table1[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,
                        0x87,0xff,0xef};
void delay(uchar z);
void main()
{
	wela=1;
    P0=0x7f;
    wela=0;
	while(1)
	{		
		adwr=1;
		_nop_();
		adwr=0;
		_nop_();
		adwr=1;
		for(a=20;a>0;a--)
		{
			display(bai,shi,ge);
		}
		P1=0xff;						 
		adrd=1;
		_nop_();
		adrd=0;
		_nop_();
		num=P1;
		adrd=1;
		num=(num/255.0)*500;
		bai=num/100;
		shi=num%100/10;
		ge=num%10;				
	}
}
void display(uchar aa,uchar bb,uchar cc)
{
	wela=1;
	P0=0x7e;
	wela=0;
	P0=0xff;					//ÏûÓ°
	dula=1;
	P0=table1[aa];
	dula=0;
	delay(5);
	P0=0xff;	  
	
	wela=1;
	P0=0x7d;
	wela=0;
	P0=0xff;					
	dula=1;
	P0=table[bb];
	dula=0;
	delay(5);
	P0=0xff;
	
	wela=1;
	P0=0x7b;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[cc];
	dula=0;
	delay(5);
	P0=0xff;
}
void delay(uchar z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}