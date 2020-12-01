#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned int
sbit led=P1^1;
sbit jia=P3^4;
sbit jian=P3^5;
sbit zheng=P3^6;
sbit fan=P3^7;
sbit wela=P2^7;
sbit dula=P2^6;
sbit in3=P2^4;
sbit in4=P2^5;
sbit ir=P3^3;
sbit in1=P2^2;
sbit in2=P2^1;
sbit led1=P2^0;
uchar jiema[2]={0,0};
uchar pwm2,i,j,shu1[3],shu[4],flag,aa=0,bb=2,cc=0;
char pwm1=20;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x79,0x38,0x3f};
//uchar code table1[]={0xfe,0xfd};
void delay(uint z);
void init();
void keyscan();
void change();
void delay1(uint z);
void delay2(uchar x);
void display(uchar bai,uchar shi,uchar ge);
void yaokong();
void yaokong_2();
uchar receive_3();

void main()
{
	uchar i;
	in1=1;
	in2=0;
	in3=1;
	in4=0;
	init();
	while(1)
	{
//		if(flag==1)
//		yaokong();
		yaokong_2();
		keyscan();
		change();
	    display(aa,bb,cc);
/*		for(i=0;i<5;i++)
		{
			in1=1;
			in2=0;
			in3=1;
			in4=0;
			delay(800);
			in1=0;
			in2=1;
			in3=0;
			in4=1;
			delay(800);
			pwm1+=10;
		}
		in1=0;
		in2=0;
		in3=0;
		in4=0;
		while(1);  */
	}
}


void init()
{
	TMOD=0x22;
	TH0=256-255;
	TL0=256-255;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SM0=0;
	SM1=1;
	REN=1;
//	TH1=(65536-1000)/256;
//	TL1=(65536-1000)%256;
	EA=1;
	ET0=1;
//	ET1=1;
	TR0=1;
//	TR1=1;
//  EX1=1;
//	IT1=1;
}

void timer0() interrupt 1
{
	 pwm2++;
	 if(pwm1>pwm2)
	 {
	 	led=1;
		led1=1;
	 }
	 else
	 {
	 	led=0;
		led1=0;
	 }
	 if(pwm2>=100)
	 pwm2=0;
}

/*void timer1() interrupt 3
{
	 TH1=(65536-1000)/256;
	 TL1=(65536-1000)%256;
	 wela=1;
	 P0=table1[j];
	 wela=0;
	 P0=0xff;
	 dula=1;
	 P0=table[shu1[j]];
	 dula=0;
	 P0=0xff;
	 if(j==1)
	 j=0;
	 else
	 j++;
}	*/

void bianma()  interrupt 2	 
{
	uchar x,y,num=0;
	EX1=0;
	delay2(15);
	if(ir==1)
	{
		EX1=1;
		return ;		
	}
	while(!ir)
		{
			delay2(1);
		}
	for(x=0;x<4;x++)
	{
		for(y=0;y<8;y++)
		{
			while(ir)
			{
				delay2(1);
			}
			while(!ir)
			{
				delay2(1);
			}
			while(ir)
			{
				delay2(1);			
				num++;
				if(num>=30)
				{
					EX1=1;
					return ;
				}
			}								
			shu[x]=shu[x]>>1;
			if(num>=8)
			{
				shu[x]=shu[x]|0x80;
			}
			num=0;
		}
	}
		if(shu[2]==~shu[3])
		{
			flag=1;
		}
		EX1=1;
}

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void delay1(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=20;y>0;y--);
}

void delay2(uchar x)
{
	uchar i;
	while(x--)
	{
		for(i=0;i<13;i++){}
	}
}

void keyscan()
{
	if(jia==0)
	{
		delay(3);
		if(jia==0)
		{
			pwm1+=10;
			if(pwm1>=100)
			pwm1=100;
			while(!jia);
		}
	}
	if(jian==0)
	{
		delay(3);
		if(jian==0)
		{
			pwm1-=10;
			if(pwm1<=0)
			pwm1=0;
			while(!jian);
		}
	}
	if(zheng==0)
	{
		delay(3);
		if(zheng==0)
		{
			in1=1;
			in2=0;
			in3=1;
			in4=0;
			while(!zheng);
		}
	}
	if(fan==0)
	{
		delay(3);
		if(fan==0)
		{
			in1=0;
			in2=1;
			in3=0;
			in4=1;
			while(!fan);
		}
	}	
}

void change()
{
	aa=pwm1/100;
	bb=pwm1%100/10;
	cc=pwm1%10;
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
	delay1(1);
	P0=0xff;
	
	wela=1;
	P0=0xfd;
	wela=0;
	P0=0xff;					
	dula=1;
	P0=table[shi];
	dula=0;
	delay1(1);
	P0=0xff;
	
	wela=1;
	P0=0xfb;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[ge];
	dula=0;
	delay1(1);
	P0=0xff;
}

void yaokong()
{
	jiema[0]=shu[2]>>4;
	jiema[1]=shu[2]&0x0f;
	if(jiema[0]==0&&jiema[1]==6)
	{
		 pwm1+=10;
		 if(pwm1>=100)
	     pwm1=100; 
	}
	if(jiema[0]==0&&jiema[1]==4)
	{
		 pwm1-=10;
		 if(pwm1<=0)
		 pwm1=0;
	}
	if(jiema[0]==0&&jiema[1]==15)
	{
		 in1=1;
		 in2=0;
		 in3=1;
		 in4=0;
	}
	if(jiema[0]==0&&jiema[1]==5)
	{
		 in1=0;
		 in2=1;
		 in3=0;
		 in4=1;
	}
	if(jiema[0]==0&&jiema[1]==10)
	{
 		 if(in3==1)
		 {
		 	in1=1;
			in2=0;
		 }
		 else
		 {
		 	in1=0;
			in2=1;
		 }
		 in3=0;
		 in4=0;
	}
	if(jiema[0]==0&&jiema[1]==9)
	{
	   	 if(in1==1)
		 {
		 	in3=1;
			in4=0;
		 }
		 else
		 {
		 	in3=0;
			in4=1;
		 }
		 in1=0;
		 in2=0;
	}
	if(jiema[0]==0&&jiema[1]==11)
	{
		 in1=0;
		 in2=0;
		 in3=0;
		 in4=0;	
	}
	flag=0; 	
}

void yaokong_2()
{
	uchar aa;
	aa=receive_3();
	jiema[0]=aa>>4;
	jiema[1]=aa&0x0f;
	if(jiema[0]==0&&jiema[1]==6)
	{
		 pwm1+=10;
		 if(pwm1>=100)
	     pwm1=100; 
	}
	if(jiema[0]==0&&jiema[1]==4)
	{
		 pwm1-=10;
		 if(pwm1<=0)
		 pwm1=0;
	}
	if(jiema[0]==0&&jiema[1]==15)
	{
		 in1=1;
		 in2=0;
		 in3=1;
		 in4=0;
	}
	if(jiema[0]==0&&jiema[1]==5)
	{
		 in1=0;
		 in2=1;
		 in3=0;
		 in4=1;
	}
	if(jiema[0]==0&&jiema[1]==9)
	{
 		 if(in3==1)
		 {
		 	in1=1;
			in2=0;
		 }
		 else
		 {
		 	in1=0;
			in2=1;
		 }
		 in3=0;
		 in4=0;
	}
	if(jiema[0]==0&&jiema[1]==10)
	{
	   	 if(in1==1)
		 {
		 	in3=1;
			in4=0;
		 }
		 else
		 {
		 	in3=0;
			in4=1;
		 }
		 in1=0;
		 in2=0;
	}
	if(jiema[0]==0&&jiema[1]==11)
	{
		 in1=0;
		 in2=0;
		 in3=0;
		 in4=0;	
	}
}

uchar receive_3()
{
	uchar s[3];
	uint i;
	for(i=0;i<3;i++)
	{
		while(RI==0)
		display(aa,bb,cc);
		RI=0;
		s[i]=SBUF;
	}
	return s[2];
}








