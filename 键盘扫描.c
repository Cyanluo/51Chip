#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit keyb1=P3^4;
sbit keyb2=P3^5;
sbit wela=P2^7;
sbit dula=P2^6;
sbit beep=P2^3;
uchar shu,tt,flag1,aa,num1,tt1,temp,num2,flag2,flag3,tt2,jian,temp1,bai,shi,ge;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x79,0x38,0x3f};
void delay(uchar z);
void display(uchar bai,uchar shi,uchar ge,uchar cc,uchar dd);
void inti();
uchar keydscan();
uchar keyjscan();
void timelimit();
void main()
{	
	inti();			
	while(1)
	{
		switch(shu=keydscan())
		{
			case 3:										//按键1 hello程序
				P1=temp;
				while(1)
				{	
					if(flag2)
					display(shu,shu,shu,shu,shu);
					if(tt==20)
					{
						tt=0;
						shu--;
						display(shu,shu,shu,shu,shu);
						beep=0;
						delay(50);
						beep=1;
						if(shu==0)
							{
							flag1=1;				   //启用else的中断程序
							P1=0;
							}
					}
					if(tt1==20)
					{
						 num2++;
						 tt1=0;
						 temp=_crol_(temp,1);
						 P1=temp;
						 if(num2==3)
						 {
						 	P1=0xff;
						 	TR1=0;
						 }
					}
					if(aa==10)
					{
						aa=0;
						num1++;
						P1=~P1;
						if(num1==6)
						{
							TR0=0;
							flag2=0;
						}
					}
					if(!flag2)
					{
						display(16,17,18,18,19);
						flag3=1;
						TR1=1;
						if(tt2==40)
						{
							dula=1;
							P0=0;
							dula=0;
							wela=1;
							P0=0xff;
							wela=0;
							inti();
							TR1=0;
							break;
						}	
					}
				}break;
			case 1:						   //倒数计时器
					 timelimit();
		}			
	}
	  
}
void delay(uchar z)
{
	uchar x,y;
	for(x=z;x>0;x--)					  //延时大概z毫秒
		for(y=110;y>0;y--);
}
uchar keydscan() 
{
	while(1)
	{
	if(keyb1==0)
		{
			delay(5);
			if(keyb1==0)
			{
			    while(!keyb1);
					TR0=1;
					TR1=1;
				return 3;					//松手开始倒数3个数
			}
		}
	if(keyb2==0)
		{
			delay(5);
			if(keyb2==0)
			{
				while(!keyb2);
					return 1;
			}
		}
	}
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

	wela=1;
	P0=0xf7;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[cc];
	dula=0;
	delay(5);
	P0=0xff;

	wela=1;
	P0=0xef;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[dd];
	dula=0;
	delay(5);
	P0=0xff;
}
void inti()
{
	 jian=0;
	 tt=0;
	 flag1=0;
	 aa=0;
	 num1=0;
	 tt1=0;
	 num2=0;
	 flag2=1;
	 flag3=0;
	 tt2=0;
	 temp=0xfe;
	 TMOD=0x11;					  
	 TH0=(65536-50000)/256;
	 TL0=(65536-50000)%256;
	 EA=1;
	 ET0=1;
	 TH1=(65536-50000)/256;
	 TL1=(65536-50000)%256;
	 ET1=1;	   
}
void timer0() interrupt 1
{
	 if(flag1==0)
	 {
	 	TH0=(65536-50000)/256;
	 	TL0=(65536-50000)%256;
	 	tt++;
	 }
	 else
	 {
		TH0=(65536-50000)/256;
	 	TL0=(65536-50000)%256;
		aa++;
	 }
}
void timer1() interrupt 3
{
	   if(flag3==0)
	   	{
			TH1=(65536-50000)/256;
		 	TL1=(65536-50000)%256;
			tt1++;
		}
		else
		{	
			TH1=(65536-50000)/256;
		 	TL1=(65536-50000)%256;
			tt2++;
		}
}
void timelimit()
{
	uint number;
	bai=keyjscan();
	flag1=1;
	shi=keyjscan();
	flag1=0;
	flag2=0;
	ge=keyjscan();
	number=bai*100+shi*10+ge;
	TR0=1;
	while(1)
	{
		bai=number/100;
		shi=number%100/10;
		ge=number%10;
		display(bai,shi,ge,0,0);		
		if(tt==20)
		{
			tt=0;
			number--;
			if(number==0)
			{
				beep=0;
				TR0=0;
				flag3=1;
				TR1=1;				
			}
		}
		if(tt2==40)
				{
					tt2=0;
					dula=1;
					P0=0;
					dula=0;
					TR1=0;
					beep=1;
					inti();
					break;
				}
	}
}
uchar keyjscan()
{
		while(1)
		{
			P3=0xfe;
			temp1=P3;
			temp1=temp1&0xf0;
			while(temp1!=0xf0)
			{
			 	delay(5);
				temp1=P3;
				temp1=temp1&0xf0;
				while(temp1!=0xf0)
				{
					temp1=P3;
					switch(temp1)
					{
						case 0xee:jian=1 ;break;
						case 0xde:jian=2 ;break;
						case 0xbe:jian=3 ;break;
						case 0x7e:jian=10 ;break;
					}
					while(temp1==0xfe)
					{
						P3=0xff;
						return jian;
					}
				}
			}
		
			P3=0xfd;
			temp1=P3;
			temp1=temp1&0xf0;
			while(temp1!=0xf0)
			{
			 	delay(5);
				temp1=P3;
				temp1=temp1&0xf0;
				while(temp1!=0xf0)
				{
					temp1=P3;
					switch(temp1)
					{
						case 0xed:jian=4 ;break;
						case 0xdd:jian=5 ;break;
						case 0xbd:jian=6 ;break;
						case 0x7d:jian=11 ;break;
					}					
					while(temp1==0xfd)
					{
						P3=0xff;
						return jian;
					}
				}
			}

			P3=0xfb;
			temp1=P3;
			temp1=temp1&0xf0;
			while(temp1!=0xf0)
			{
			 	delay(5);
				temp1=P3;
				temp1=temp1&0xf0;
				while(temp1!=0xfe)
				{
					temp1=P3;
					switch(temp1)
					{
						case 0xeb:jian=7 ;break;
						case 0xdb:jian=8 ;break;
						case 0xbb:jian=9 ;break;
						case 0x7b:jian=12 ;break;
					}					
					while(temp1==0xfb)
					{
						P3=0xff;
						return jian;
					}
				}
			}
		
			P3=0xf7;
			temp1=P3;
			temp1=temp1&0xf0;
			while(temp1!=0xf0)
			{
			 	delay(5);
				temp1=P3;
				temp1=temp1&0xf0;
				while(temp1!=0xf0)
				{
					temp1=P3;
					switch(temp1)
					{
						case 0xe7:jian=0 ;break;
						case 0xd7:jian=14;break;
						case 0xb7:jian=15;break;
						case 0x77:jian=16 ;break;
					}
					while(temp1==0xf7)
					{
						P3=0xff;
						return jian;
					}
				}
			}
		if(flag1==1)
			display(bai,0,0,0,0);
		if(flag2==0)
			display(bai,shi,0,0,0);
		}
}
