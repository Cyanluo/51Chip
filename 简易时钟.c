#include<reg52.h>
#include<1602.h>
#define uchar unsigned char
#define uint unsigned int
sbit jian=P3^7;
sbit key1_jia=P3^0;
sbit key2_shan=P3^1;
sbit key3_jian=P3^2;

uchar code table[]=" 2019 08 31 SUT";
uchar code table1[]="    00:00:00";
uchar flag=0,count=0;
char miao=0,shi=0,fen=0;

void write_string(uchar *p,uchar address)
{
	uchar i;
	write_com(0x80+address);
	for(i=0;p[i]!=0;i++)
	{
		write_dat(p[i]);
	}
}

void inti_timer0()
{
	TMOD=0x01;
	TH0=0x4c;
	TL0=0x01;
	EA=1;
	ET0=1;
	TR0=1;
} 

void keyscan()
{
	if(key2_shan==0)
	{
		delay(5);
		if(key2_shan==0)
		{
			 if(flag==0)
			 {
				 TR0=0;
				 write_com(0x80+0x4a);
				 write_com(0x0d);
				 flag=1;
				 while(!key2_shan);
			 }
			 if(flag==1)
			  {
				 if(key2_shan==0)
					{
						delay(5);
						if(key2_shan==0)
						{
							 write_com(0x80+0x47);
							 write_com(0x0d);
							 flag=2;
							 while(!key2_shan);
						}
					}
			 }
			 if(flag==2)
			  {
				 if(key2_shan==0)
					{
						delay(5);
						if(key2_shan==0)
						{
							 write_com(0x80+0x44);
							 write_com(0x0d);
							 flag=3;
							 while(!key2_shan);
						}
					}
			 }
			 if(flag==3)
			  {
				 if(key2_shan==0)
					{
						delay(5);
						if(key2_shan==0)
						{
							 flag=0;
							 TR0=1;
							 write_com(0x0c);
							 while(!key2_shan);
						}
					}
			 }
		}
	}
	if(flag!=0)
	{
		if(key1_jia==0)
		{
			delay(5);
			if(key1_jia==0)
			{
				if(flag==1)
				{
					miao++;
					if(miao==60)
					miao=0;
					write_dat(0x30+miao/10);
					write_dat(0x30+miao%10);
					write_com(0x80+0x4a);
					while(!key1_jia);
				}
				if(flag==2)
				{
					fen++;
					if(fen==60)
					fen=0;
					write_dat(0x30+fen/10);
					write_dat(0x30+fen%10);
					write_com(0x80+0x47);
					while(!key1_jia);
				}
				if(flag==3)
				{
					shi++;
					if(shi==24)
					shi=0;
					write_dat(0x30+shi/10);
					write_dat(0x30+shi%10);
					write_com(0x80+0x44);
					while(!key1_jia);
				}
			}
		}
		if(key3_jian==0)
		{
			delay(5);
			if(key3_jian==0)
			{
				if(flag==1)
				{
					miao--;
					if(miao==-1)
					miao=59;
					write_dat(0x30+miao/10);
					write_dat(0x30+miao%10);
					write_com(0x80+0x4a);
					while(!key3_jian);
				}
				if(flag==2)
				{
					fen--;
					if(fen==-1)
					fen=59;
					write_dat(0x30+fen/10);
					write_dat(0x30+fen%10);
					write_com(0x80+0x47);
					while(!key3_jian);
				}
				if(flag==3)
				{
					shi--;
					if(shi==-1)
					shi=23;
					write_dat(0x30+shi/10);
					write_dat(0x30+shi%10);
					write_com(0x80+0x44);
					while(!key3_jian);
				}
			}
		}

	}
} 

void run()
{
	if(count==20)
	{
		count=0;
		miao++;
		if(miao==60)
		miao=0;
		write_com(0x80+0x4a);
		write_dat(0x30+miao/10);
		write_dat(0x30+miao%10);
		if(miao==0)
		{
			fen++;
			if(fen==60)
			fen=0;
			write_com(0x80+0x47);
			write_dat(0x30+fen/10);
			write_dat(0x30+fen%10);
			if(fen==0)
			{
				shi++;
				if(shi==24)
				shi=0;
				write_com(0x80+0x44);
				write_dat(0x30+shi/10);
				write_dat(0x30+shi%10);
			}
		}
	}
}

void main()
{
	jian=0;
	inti();
	inti_timer0();
	write_string(table,0x00);
	write_string(table1,0x40);
	while(1)
	{
		run();
		keyscan();
	}
}

void timer0() interrupt	 1
{
	 count++;
	 TH0=0x4c;
	 TL0=0x01;
}









