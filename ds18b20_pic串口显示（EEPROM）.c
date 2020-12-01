#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit receive=P3^3;
sbit transform=P3^4;
sbit wela=P2^7;
sbit dula=P2^6;
sbit scl=P2^1;
sbit sda=P2^0;

uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x79,0x38,0x3f};
const uchar table1[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,
                        0x87,0xff,0xef};

void display(uchar bai,uchar shi,uchar ge,uchar cc,uchar dd);
uchar randon_read(uchar add);					   //指定地址读
void randon_write(uchar add,uchar dat);			  //指定地址写
uchar read_byte();							 //读一个字节
void write_byte(uchar dat);					//写一个字节
void ack();									//应答信号
void stop();									//停止信号
void start();							   //开始信号
void delay();
void delay1(uint z);						 //z毫秒延时
void init();
void keyscan();
uchar count,flag=1;

void main()
{
	uchar aa=0,bai,shi,ge,biao[6],bb,cc,i,temp,mm,nn,add_romw,x1,add_romr;
	init();
	while(1)
	{
		keyscan();
		if(flag==1)
		{
			while(RI==0)
			{
			 display(bai,bb,cc,mm,nn);
			}
		
			RI=0;
			aa=SBUF;
			P1=SBUF;
			if(count==225)
			{
		    	count=0;
				TR0=0;
				randon_write(add_romw++,aa);
				if(add_romw>254)
				{
					add_romw=0;
				}
				TR0=1;
			}
					  
			
			while(RI==0)
			{
			 display(bai,bb,cc,mm,nn);
			}
			RI=0;
			temp=SBUF;
			SBUF=temp;
			if(aa!=0)
			{
				for(i=0;aa!=0;i++)
				{
					biao[i]=aa%10;
					aa/=10;
					if(aa==0)
					{
						biao[++i]='*';
					}
				}
				cc=0;
				bb=0;
				ge=0;
				shi=0;
				bai=0;
				for(i=0;biao[i]!='*';i++)
				{
					switch(i)
					{
						case 0:cc=biao[0];break;
						case 1:bb=biao[1];break;
						case 2:ge=biao[2];break;
						case 4:shi=biao[3];break;
						case 5:bai=biao[4];break;
					}
				}
			}
			mm=temp/10;
			nn=temp%10;
			display(bai,bb,cc,mm,nn);
		}
		if(flag==2)
		{
			 x1=randon_read(add_romr++);
			 if(add_romr<254)
			 {
			 	SBUF=x1;
			 }
		}
	}
}

/*void es() interrupt 4
{
	RI=0;
	P1=SBUF;
} */

void timer0() interrupt 1
{
	TH0=(65536-5000)/256;
	TL0=(65536-5000)%256;
	count++;	
}

void init()
{
	TMOD=0x21;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SM0=0;
	SM1=1;
	REN=1;
	TH0=(65536-5000)/256;
	TL0=(65536-5000)%256;
	TR0=1;
	EA=1;
	ET0=1;
//	ES=1;
}

void display(uchar bai,uchar shi,uchar ge,uchar cc,uchar dd)
{
	wela=1;
	P0=0xfe;
	wela=0;
	P0=0xff;								//消影
	dula=1;
	P0=table[bai];
	dula=0;
	delay1(5);
	P0=0xff;
	
	wela=1;
	P0=0xfd;
	wela=0;
	P0=0xff;					
	dula=1;
	P0=table[shi];
	dula=0;
	delay1(5);
	P0=0xff;
	
	wela=1;
	P0=0xfb;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table1[ge];
	dula=0;
	delay1(5);
	P0=0xff;

	wela=1;
	P0=0xf7;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[cc];
	dula=0;
	delay1(5);
	P0=0xff;

	wela=1;
	P0=0xef;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[dd];
	dula=0;
	delay1(5);
	P0=0xff;
}

void delay1(uint z)						 //z毫秒延时
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void delay()
{
	;;
}

void start()							   //开始信号
{
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();
}

void stop()									//停止信号
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();
}

void ack()									//应答信号
{
	uchar i=255;
	scl=1;
	while(sda==1&&i>0)i--;
	sda=1;
	scl=0;
}

void write_byte(uchar dat)					//写一个字节
{
	uchar i,aa;
	scl=0;
	delay();
	aa=dat;
	for(i=0;i<8;i++)
	{
		dat=dat<<1;
		sda=CY;
		scl=1;
		delay();
		scl=0;
		delay();
		sda=1;
		delay();
	}
}

uchar read_byte()							 //读一个字节
{
	uchar i,x,y;
	scl=0;
	delay();
	for(i=0;i<8;i++)
	{
		scl=1;
    	delay();
		x=sda;
		y=y<<1|x;
		scl=0;
		delay();
		sda=1;
		delay();
	}
	return y;
}

void randon_write(uchar add,uchar dat)			  //指定地址写
{
	start();
	write_byte(0xa0);
	ack();
	write_byte(add);
	ack();
	write_byte(dat);
	ack();
	stop();
	delay1(100);
}

uchar randon_read(uchar add)					   //指定地址读
{
	uchar aa;
	start();
	write_byte(0xa0);
	ack();
	write_byte(add);
	ack();
	start();
	write_byte(0xa1);
	ack();
	aa=read_byte();
	stop();
	delay1(100);
	return aa;
}

void keyscan()
{
	if(receive==0)
	{
		delay1(3);
		if(receive==0)
		{
			flag=1;
			while(!receive);
		}
	}
	if(transform==0)
	{
		delay1(3);
		if(transform==0)
		{
			flag=2;
			while(!transform);
		}
	}	
}







