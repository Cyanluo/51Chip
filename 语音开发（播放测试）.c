#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code bofang[]={0xAA,0x02,0x00,0xAC,'*'}; //播放
uchar code yinliang[]={0xAA,0X13,0X01,20,'*'};
uchar code zuhe[]={0xaa,0x1b,0x04,'0','1','0','2','*'};
void send_date(uchar *p);
void send_byte(uchar dat);
void init();
void delay(uint z);

void main()
{
	 init();
	 delay(2000);
//	 send_date(yinliang);
//	 send_date(bofang);
	 send_date(zuhe);
	 while(1);
}

void delay(uint z)			 //延时z毫秒
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void init()					 //串口初始化
{
//	EA=1;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
//	ES=1;
	SM0=0;
	SM1=1;
	REN=1;
}

void send_byte(uchar dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}

void send_date(uchar *p)	  //发送指令
{
	uchar  c,i;
	i=0;
	c=0;
	while(p[i]!='*')
	{
		send_byte(p[i]);
		c+=p[i];
	 	i++;
	}
	send_byte(c);		       //校验位	
	delay(120);	
}
















