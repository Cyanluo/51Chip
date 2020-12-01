#include<reg52.h>
#define uchar unsigned char
sbit wela=P2^7;
sbit dula=P2^6;
sbit beep=P2^3;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar temp=12,ge,shi,bai,tt=0;
void inti();
void delay(uchar z);
void display(uchar bai,uchar shi,uchar ge); 
void main()
{
	inti();
	while(1)
	{
		bai=temp/100;
		shi=temp%100/10;
		ge=temp%10;	
		if(tt==20)
		{
			tt=0;
			temp--;
			if(temp==0)
			{
				beep=0;
				TR0=0;	
			}
		}
		display(bai,shi,ge);	
	}
	

}
void inti() 
{
	wela=0;
	dula=0;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
}
void display(uchar bai,uchar shi,uchar ge)
{
	wela=1;
	P0=0xfe;
	wela=0;
	P0=0xff;					//ÏûÓ°
	dula=1;
	P0=table[bai];
	dula=0;
	delay(5);
	P0=0xff;
	
	wela=1;
	P0=0xfd;
	wela=0;
	P0=0xff;					
	dula=1;
	P0=table[shi];
	dula=0;
	delay(5);
	P0=0xff;
	
	wela=1;
	P0=0xfb;
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
void time() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	tt++;
}