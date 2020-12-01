#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
uchar num,bai,shi,ge;
bite adwr=3^6;
bite adrd=3^7;
bite wela=2^7;
bite dula=2^6;
void display(uchar bai,uchar shi,uchar ge);
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x79,0x38,0x3f};
void delay(uchar z);
void main()
{
	P0=0x7f;
	wela=0;
	while(1)
	{
		adwr=1
		adwr=0;
		adwr=1;
		display(bai,shi,ge);
		delay(10);
		P1=0xff;						  //Æô¶¯ad
		adrd=1;
		_nop_();
		adrd=0;
		_nop_();
		adrd=1;
		num=P1;
		bai=num/100;
		shi=num%100/10;
		ge=num%10;				
	}
}
void display(uchar bai,uchar shi,uchar ge)
{
	wela=1;
	P0=0x7e;
	wela=0;
	P0=0xff;					//ÏûÓ°
	dula=1;
	P0=table[bai];
	dula=0;
	delay(5);
	P0=0xff;
	
	wela=1;
	P0=0x7d;
	wela=0;
	P0=0xff;					
	dula=1;
	P0=table[shi];
	dula=0;
	delay(5);
	P0=0xff;
	
	wela=1;
	P0=0x7b;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[ge];
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