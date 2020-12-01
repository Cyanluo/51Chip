#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit lcden=P3^4;
sbit lcdrs=P3^5;
sbit wela=P2^7;
sbit dula=P2^6;
//uchar code table[]="The cat is here";
//uchar code table1[]="Do not worry";
void write_com(uchar com);
void write_dat(uchar dat);
void delay(uint z);
void inti();
void keyscan();
//uchar num,i;
void main()
{
	 inti();
	 keyscan();
		  
/*		 for(i=0;table[i]!=0;i++)
		 {
		 	write_dat(table[i]);
			delay(20);
		 }
		 write_com(0x80+0x50);
		 for(i=0;table1[i]!=0;i++)
		 {
		 	write_dat(table1[i]);
			delay(20);	
		 }
		 for(num=0;num<16;num++)
		{
			write_com(0x18);
			delay(20);
		}
		while(1);  */
	
}
void inti()
{
	dula=0;
	wela=0;
	write_com(0x38);
	write_com(0x0e);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80+0x00);
}
void delay(uint z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void write_dat(uchar dat)
{
	lcden=0;
	lcdrs=1;
	delay(5);
	lcden=1;
	delay(5);
	P0=dat;

	lcden=0;
	lcdrs=0;
}
void write_com(uchar com)
{
	lcden=0;
	lcdrs=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void keyscan()
{
	uchar flag,temp,num;
	while(1)
	{
		P3=0xfe;
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			delay(5);
			temp=P3;
			temp=temp&0xf0;
			if(temp!=0xf0)
			{
				switch(temp)
				{
					case 0xe0:num='0';break;
					case 0xd0:num='1';break;
					case 0xb0:num='2';break;
					case 0x70:num='3';break;
				}
				while(temp!=0xf0)
				{
					temp=P3;
					temp=temp&0xf0;
					flag=1;
				}
			}
		}
		P3=0xfd;
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			delay(5);
			temp=P3;
			temp=temp&0xf0;
			if(temp!=0xf0)
			{
				switch(temp)
				{
					case 0xe0:num=0;break;
					case 0xd0:num=1;break;
					case 0xb0:num=2;break;
					case 0x70:num=3;break;
				}
				while(temp!=0xf0)
				{
					temp=P3;
					temp=temp&0xf0;
					flag=1;
				}
			}
		}
		P3=0xfb;
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			delay(5);
			temp=P3;
			temp=temp&0xf0;
			if(temp!=0xf0)
			{
				switch(temp)
				{
					case 0xe0:num=0;break;
					case 0xd0:num=1;break;
					case 0xb0:num=2;break;
					case 0x70:num=3;break;
				}
				while(temp!=0xf0)
				{
					temp=P3;
					temp=temp&0xf0;
					flag=1;
				}
			}
		}
		P3=0xf7;
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			delay(5);
			temp=P3;
			temp=temp&0xf0;
			if(temp!=0xf0)
			{
				switch(temp)
				{
					case 0xe0:num=0;break;
					case 0xd0:num=1;break;
					case 0xb0:num=2;break;
					case 0x70:num=3;break;
				}
				while(temp!=0xf0)
				{
					temp=P3;
					temp=temp&0xf0;
					flag=1;
				}
			}
		}
		if(flag==1)
		{
			flag=0;
			if(num>'0'&&num<'9')
			write_dat(num);
		 	else
		 	write_com(num);	
		}
	}
}
