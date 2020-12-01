#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char 
#define uint unsigned int
sbit cs=P1^4;
sbit sk=P1^5;
sbit di=P1^6;
sbit dout=P1^7;
sbit wela=P2^7;
sbit dula=P2^6;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x79,0x38,0x3f};
void display(uchar bai,uchar shi,uchar ge);
void delay(uint z);
void write(uchar add,uchar wdat);
uchar read(uchar add);
uchar RW(uchar dat);
void init();
void enwrite();

main()
{
	while(1)
	{
	uchar a1,a2,a3;
	enwrite();
	init();
	write(0,5);
	write(2,2);
	write(3,3);
	a1=read(0);
	a2=read(2);
	a3=read(3);
	
		display(a1,a2,a3);
	}
}

void init()
{
	cs=0;
	sk=0;
	di=0;
}

uchar RW(uchar dat)
{
	 uchar i;
	 for(i=0;i<8;i++)
	 {
		dat<<=1;
		sk=0;
		di=CY;
		sk=1;
		dat|=dout;
		sk=0;
	 }
	 return dat;
}

uchar read(uchar add)
{
	uchar rdat;
	cs=1;
	RW(0x03);
	RW(add);
	rdat=RW(0);
	cs=0;
	_nop_();_nop_();
	return rdat;
}

void write(uchar add,uchar wdat)
{
	cs=1;
	RW(0x02);
	RW(add|0x80);
	RW(wdat);
	cs=0;
	_nop_();_nop_();
	cs=1;
	while(!dout);
	cs=0;
	_nop_();_nop_();
}

void enwrite()
{
	cs=1;
	RW(0x02);
	RW(0x60);
	cs=0;
}

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void display(uchar bai,uchar shi,uchar ge)			   //数码管动态显示
{
	wela=1;
	P0=0xfe;
	wela=0;
	P0=0xff;								//消影
	dula=1;
	P0=table[bai];
	dula=0;
	delay(2);
	P0=0xff;
	
	wela=1;
	P0=0xfd;
	wela=0;
	P0=0xff;					
	dula=1;
	P0=table[shi];
	dula=0;
	delay(2);
	P0=0xff;
	
	wela=1;
	P0=0xfb;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[ge];
	dula=0;
	delay(2);
	P0=0xff;
}






