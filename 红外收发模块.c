#include<reg52.h>
#include<hongwai.h>
#include<1602.h>
#include<at24c02.h>
sbit beep=P2^3;
sbit key=P1^4;
sbit key_1=P1^0;
sbit key_2=P1^1;
sbit key_3=P1^2;
sbit key_4=P1^3;
sbit LED=P1^0;
sbit LEDa=P1^1;
uchar jiema[6],s[3],du[6],flag,tx[5],flag1=0;


void init_chuanko()
{
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SM0=0;
	SM1=1;
	REN=1;
	EA=1;
//	ES=1;
}	

void change()
{
	uchar i;
//	receive_3(s);
	jiema[0]=s[0]>>4;
	jiema[1]=s[0]&0x0f;
	jiema[2]=s[1]>>4;
	jiema[3]=s[1]&0x0f;
	jiema[4]=s[2]>>4;
	jiema[5]=s[2]&0x0f;
	for(i=0;i<6;i++)
	{
		if(jiema[i]>9&&jiema[i]<16)
		jiema[i]+=7;
	}
}

void read_24c02()
{
	uchar a1,a2,a3,i;
	static uchar j=0;
	a1=randon_read(j++);
	a2=randon_read(j++);
	a3=randon_read(j++);
	if(j>=9)
	j=0;
	du[0]=a1>>4;
	du[1]=a1&0x0f;
	du[2]=a2>>4;
	du[3]=a2&0x0f;
	du[4]=a3>>4;
	du[5]=a3&0x0f;
	for(i=0;i<6;i++)
	{
		if(du[i]>9&&du[i]<16)
		du[i]+=7;
	}
	write_com(0x80+0x40);
	write_dat(du[0]+0x30); 
	write_dat(du[1]+0x30);
	write_dat(0x20);
	write_dat(du[2]+0x30);
	write_dat(du[3]+0x30);
	write_dat(0x20);
	write_dat(du[4]+0x30);
	write_dat(du[5]+0x30);
	write_com(0x80+0x4b);
	if(j==0)
	write_dat(3+0x30);
	else
	write_dat(j/3+0x30);
	write_com(0x80+0x40);
}

void tr(uchar i)
{
	tx[0]=0xa1;
	tx[1]=0xf1;
	tx[2]=randon_read(i++);
	tx[3]=randon_read(i++);
	tx[4]=randon_read(i++);
//	flag1=1;
//	EA=0;
//	ES=0;
	fasong(tx);
//	ES=1;
//	EA=1;

}

void keyscan()
{
	key=0;
	if(key_1==0)
	{
		delay1(2);
		if(key_1==0)
		{
			ES=0;
			beep=0;
			delay1(100);
			beep=1;
			while(!key_1);
		}
	}
	if(key_2==0)
	{
		delay1(2);
		if(key_2==0)
		{
			ES=1;
			beep=0;
			delay1(100);
			beep=1;
			while(!key_2);
		}
	}
	if(key_3==0)
	{
		delay1(2);
		if(key_3==0)
		{
			tr(0);
			while(!key_3);
		}
	}
	if(key_4==0)
	{
		delay1(2);
		if(key_4==0)
		{
			read_24c02();
			while(!key_4);
		}
	}
}        

void main()
{
	 uchar i=0;
	 init_chuanko();
	 inti();
	 while(1)
	 {
		if(flag==1)
		{
			change();
			flag=0;
		write_com(0x80);
		write_dat(jiema[0]+0x30); 
		write_dat(jiema[1]+0x30);
		write_dat(0x20);
		write_dat(jiema[2]+0x30);
		write_dat(jiema[3]+0x30);
		write_dat(0x20);
		write_dat(jiema[4]+0x30);
		write_dat(jiema[5]+0x30);
		write_com(0x80);
		randon_write(i++,s[0]);
		randon_write(i++,s[1]);
		randon_write(i++,s[2]);
		beep=0;
		delay1(100);
		beep=1;
		if(i>=9)
		i=0;
		}
//		read_24c02();
		keyscan();
	 }
}

void chuanko() interrupt 4
{
	EA=0;
	if(flag1==0)
	{
		if(RI==1)
		{
			uint i;
			for(i=0;i<3;i++)
			{
				LEDa=0;
				while(RI==0);
				LEDa=1;
				RI=0;
				s[i]=SBUF;
			}
			EA=1;
			flag=1;
		}	
	}   

/*	if(flag1==1)
	{
		if(TI==1)
		{
			uint j;
			for(j=1;j<5;j++)
			{
				SBUF=tx[j++];
				LED=0;
				while(TI==0);
				LED=1;
				TI=0;
			}
			EA=1;
			flag1=0;
		}
	}				*/
}






