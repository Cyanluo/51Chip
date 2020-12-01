#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define wendushi 88
#define du 87
#define s 10
sbit lcden=P3^4;
sbit lcdrs=P3^5;
sbit DS=P2^2;           //define interface
uint temp,temp1;             // variable of temperature
uchar flag1;            // sign of the result positive or negative
sbit dula=P2^6;
sbit wela=P2^7;
sbit busy=P1^1;
//sbit jia=P3^4;
//sbit jian=P3^5;
sbit bofang=P3^6;
sbit zhidi=P3^7;
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
unsigned char code table1[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,
                        0x87,0xff,0xef};
uchar code yinliangjia[]={0xaa,0x14,0x00,'*'};
uchar code yinliangjian[]={0xaa,0x15,0x00,'*'};
uchar code zhidin[]={0xaa,0x07,0x02,0x00,0x09,'*'};
uchar code _1602_1[]="   temperature";
void send_date(uchar *p);
void send_byte(uchar dat);
void init();
void delay1(uint z);
void display(uint temp);
void dsreset(void);
bit tmpreadbit(void);
uchar tmpread(void);
void tmpwritebyte(uchar dat);
void tmpchange(void);
uint tmp();
void display(uint temp);
void zuhe();
void keyscan();
void init_1602();
void write_com(uchar com);
void write_dat(uchar dat);
void display_1602();

void main()
{
//	uchar a;
	init();
	init_1602();
	delay1(2000);
	while(1)
	{
		tmpchange();
		temp1=tmp();
		display_1602();
/*		for(a=10;a>0;a--)
	  	{   
	  		display(tmp());
	  	}			*/
		keyscan();
	}
}


void delay1(uint z)			 //延时z毫秒
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
	EA=1;
	EX1=1;
	IT1=1;
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
	delay1(120);	
}

void zuhe()
{
	uchar n,bai,shi,ge,a;
	uchar  wd[100];
	n=0;
	wd[n++]=0xaa;
	wd[n++]=0x1b;
	wd[n++]=0;
	a=temp1/10;
	bai=temp1/100;
	shi=temp1%100/10;
	ge=temp1%10;
	wd[n++]=wendushi/10+0x30;
	wd[n++]=wendushi%10+0x30;
	if(bai!=0)
	{
		if(temp1>19)
		{
			wd[n++]=bai/10+0x30;
			wd[n++]=bai%10+0x30;
		}
		wd[n++]=s/10+0x30;
		wd[n++]=s%10+0x30;	  
	}
	if(shi!=0)
	{
		wd[n++]=shi/10+0x30;
		wd[n++]=shi%10+0x30;
	}
	if(bai==0&&shi==0)
	{
		wd[n++]=0x30;
		wd[n++]=0x30;
	}
	wd[n++]=du/10+0x30;
	wd[n++]=du%10+0x30;
	if(ge!=0)
	{
		wd[n++]=ge/10+0x30;
		wd[n++]=ge%10+0x30;
	}
	wd[n++]='*';
	wd[2]=n-4;
	send_date(wd);
}

void delay(uint count)      //delay
{
  uint i;
  while(count)
  {
    i=200;
    while(i>0)
    i--;
    count--;
  }
}
void dsreset(void)       //send reset and initialization command
{
  uint i;
  DS=0;
  i=103;
  while(i>0)i--;
  DS=1;
  i=4;
  while(i>0)i--;
}

bit tmpreadbit(void)       //read a bit
{
   uint i;
   bit dat;
   DS=0;i++;          //i++ for delay
   DS=1;i++;i++;
   dat=DS;
   i=8;while(i>0)i--;
   return (dat);
}

uchar tmpread(void)   //read a byte date
{
  uchar i,j,dat;
  dat=0;
  for(i=1;i<=8;i++)
  {
    j=tmpreadbit();
    dat=(j<<7)|(dat>>1);   //读出的数据最低位在最前面，这样刚好一个字节在DAT里
  }
  return(dat);
}

void tmpwritebyte(uchar dat)   //write a byte to ds18b20
{
  uint i;
  uchar j;
  bit testb;
  for(j=1;j<=8;j++)
  {
    testb=dat&0x01;
    dat=dat>>1;
    if(testb)     //write 1
    {
      DS=0;
      i++;i++;
      DS=1;
      i=8;while(i>0)i--;
    }
    else
    {
      DS=0;       //write 0
      i=8;while(i>0)i--;
      DS=1;
      i++;i++;
    }

  }
}

void tmpchange(void)  //DS18B20 begin change
{
  dsreset();
  delay(1);
  tmpwritebyte(0xcc);  // address all drivers on bus
  tmpwritebyte(0x44);  //  initiates a single temperature conversion
}

uint tmp()               //get the temperature
{
  float tt;
  uchar a,b;
  dsreset();
  delay(1);
  tmpwritebyte(0xcc);
  tmpwritebyte(0xbe);
  a=tmpread();
  b=tmpread();
  temp=b;
  temp<<=8;             //two byte  compose a int variable
  temp=temp|a;
  tt=temp*0.0625;
  temp=tt*10+0.5;
  return temp;
}

/*void display(uint temp)			//显示程序
{
   uchar A1,A2,A2t,A3;
   A1=temp/100;
   A2t=temp%100;
   A2=A2t/10;
   A3=A2t%10;
   dula=0;
   P0=table[A1];		//显示百位
   dula=1;
   dula=0;

   wela=0;
   P0=0x7e;
   wela=1;
   wela=0;
   delay(1);

   dula=0;
   P0=table1[A2];		//显示十位
   dula=1;
   dula=0;

   wela=0;
   P0=0x7d;
   wela=1;
   wela=0;
   delay(1);

   P0=table[A3];		//显示个位
   dula=1;
   dula=0;

   P0=0x7b;
   wela=1;
   wela=0;			  
   delay(1);
}	   */

void keyscan()
{
/*	if(jia==0)
	{
		delay1(3);
		if(jia==0)
		{
			send_date(yinliangjia);
			while(!jia);
		}
	}
	if(jian==0)
	{
		delay1(3);
		if(jian==0)
		{
			send_date(yinliangjian);
			while(!jian);
		}
	} */
	if(bofang==0)
	{
		delay1(3);
		if(bofang==0)
		{
			zuhe();
			while(!bofang);
		}
	}
	if(zhidi==0)
	{
		delay1(3);
		if(zhidi==0)
		{
			send_date(zhidin);
			while(!zhidi);
		}
	}
}

void write_dat(uchar dat)
{
	lcden=0;
	lcdrs=1;
	P0=dat;
	delay1(5);
	lcden=1;
	delay1(5);
	lcden=0;
	lcdrs=0;
}

void write_com(uchar com)
{
	lcden=0;
	lcdrs=0;
	P0=com;
	delay1(5);
	lcden=1;
	delay1(5);
	lcden=0;
}

void init_1602()
{
	dula=0;
	wela=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80+0x00);
}

void display_1602()
{
	uchar i=0,bai,shi,ge;
	write_com(0x80+0x00);
	while(_1602_1[i])
	{
		write_dat(_1602_1[i++]);
	}
	write_com(0x80+0x46);
	bai=temp/100;
	shi=temp%100/10;
	ge=temp%10;
	write_dat(bai+0x30);
	write_dat(shi+0x30);
	write_dat('.');
	write_dat(ge+0x30);
}














