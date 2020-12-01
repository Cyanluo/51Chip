#include<reg52.h>
#include<1602.h>
#define uchar unsigned char
#define uint unsigned int
sbit jian=P3^7;
sbit jian1=P3^6;
sbit key1_jia=P3^0;
sbit key2_shan=P3^1;
sbit key3_jian=P3^2;
sbit dscs=P1^4;
sbit dsas=P1^5;
sbit dsrw=P1^6;
sbit dsds=P1^7;
sbit beep=P2^3;
sbit leled=P2^5;


uchar code table1[]="      :  :  ";
uchar flag=0,count=0;
char miao=0,shi=0,fen=0,mounth,date,day,flag1,aa,ashi,afen,amiao;
uint year;
						   
void write_string(uchar *p,uchar address)
{
	uchar i;
	write_com(0x80+address);
	for(i=0;p[i]!=0;i++)
	{
		write_dat(p[i]);
	}
}

void ds_write(uchar address,uchar dat);
uchar ds_read(uchar adress);

void keyscan()
{
	if(flag1==1)
	{
		if(key2_shan==0||key3_jian==0||key1_jia==0)
		delay(5);
		if(key2_shan==0||key3_jian==0||key1_jia==0)
		flag1=0;
	}
	else
	{
		if(key2_shan==0)
		{
			delay(5);
			if(key2_shan==0)
			{
				 if(flag==0)
				 {
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
								 amiao=ds_read(1);
								 afen=ds_read(3);
								 ashi=ds_read(5);
								 ds_write(0,miao);
							     ds_write(2,fen);
								 ds_write(4,shi);
								 
								 write_com(0x80+0x4a);
								 write_dat(0x30+amiao/10);
								 write_dat(0x30+amiao%10);		  
							
								 write_com(0x80+0x47);
								 write_dat(0x30+afen/10);
								 write_dat(0x30+afen%10);
							
								 write_com(0x80+0x44);
								 write_dat(0x30+ashi/10);
								 write_dat(0x30+ashi%10);

								 write_com(0x80+0x4a);
								 write_com(0x0d);
								 flag=4;
								 while(!key2_shan);
							}
						}
				}
				 if(flag==4)
				  {
					 if(key2_shan==0)
						{
							delay(5);
							if(key2_shan==0)
							{
								 write_com(0x80+0x47);
								 write_com(0x0d);
								 flag=5;
								 while(!key2_shan);
							}
						}
				 }
				 if(flag==5)
				  {
					 if(key2_shan==0)
						{
							delay(5);
							if(key2_shan==0)
							{
								 write_com(0x80+0x44);
								 write_com(0x0d);
								 flag=6;
								 while(!key2_shan);
							}
						}
				 }
				 if(flag==6)
				  {
					 if(key2_shan==0)
						{
							delay(5);
							if(key2_shan==0)
							{
								 flag=0;
								 write_com(0x0c);
								 ds_write(1,amiao);
								 ds_write(3,afen);
								 ds_write(5,ashi);
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
					if(flag==4)
					{
						amiao++;
						if(amiao==60)
						amiao=0;
						write_dat(0x30+amiao/10);
						write_dat(0x30+amiao%10);
						write_com(0x80+0x4a);
						while(!key1_jia);
					}
					if(flag==5)
					{
						afen++;
						if(afen==60)
						afen=0;
						write_dat(0x30+afen/10);
						write_dat(0x30+afen%10);
						write_com(0x80+0x47);
						while(!key1_jia);
					}
					if(flag==6)
					{
						ashi++;
						if(ashi==24)
						ashi=0;
						write_dat(0x30+ashi/10);
						write_dat(0x30+ashi%10);
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
					if(flag==4)
					{
						amiao--;
						if(amiao==-1)
						amiao=59;
						write_dat(0x30+amiao/10);
						write_dat(0x30+amiao%10);
						write_com(0x80+0x4a);
						while(!key3_jian);
					}
					if(flag==5)
					{
						afen--;
						if(afen==-1)
						afen=59;
						write_dat(0x30+afen/10);
						write_dat(0x30+afen%10);
						write_com(0x80+0x47);
						while(!key3_jian);
					}
					if(flag==6)
					{
						ashi--;
						if(ashi==-1)
						ashi=23;
						write_dat(0x30+ashi/10);
						write_dat(0x30+ashi%10);
						write_com(0x80+0x44);
						while(!key3_jian);
					}
				}
			}
	
		}
	}
} 


void ds_write(uchar address,uchar dat)
{
	 dscs=0;
	 dsas=0;
	 dsds=1;
	 dsrw=1;
	 dsas=1;
	 P0=address;
	 dsas=0;
	 dsrw=0;
	 P0=dat;
	 dsrw=1;
	 dscs=1;
	 dsas=1;
}

uchar ds_read(uchar adress)
{
	uchar dat;
	dscs=0;
	dsds=1;
	dsrw=1;
	dsas=1;
	P0=adress;
	dsas=0;
	dsds=0;
	P0=0xff;
	dat=P0;
	dsds=1;
	dscs=1;
	dsas=1;
	return dat;
}

/*void inti_ds(uchar dsshi,uchar dsfen,uchar dsmiao,uchar dsyear,uchar dsmounth,uchar dsdate,uchar dsday)
{
	ds_write(0,dsmiao);
	ds_write(2,dsfen);
	ds_write(4,dsshi);
	ds_write(9,dsyear);
	ds_write(8,dsmounth);
	ds_write(7,dsdate);
	ds_write(6,dsday);

}	*/

void read()
{
	miao=ds_read(0);
	fen=ds_read(2);
	shi=ds_read(4);
	year=ds_read(9);
	mounth=ds_read(8);
	date=ds_read(7);
	day=ds_read(6);
}

void displaysfmnyr()
{
	write_com(0x80+0x4a);
	write_dat(0x30+miao/10);
	write_dat(0x30+miao%10);		  

	write_com(0x80+0x47);
	write_dat(0x30+fen/10);
	write_dat(0x30+fen%10);

	write_com(0x80+0x44);
	write_dat(0x30+shi/10);
	write_dat(0x30+shi%10);

	write_com(0x80+0x4a);
	write_dat(0x30+miao/10);
	write_dat(0x30+miao%10);

	write_com(0x80+0x03);
	write_dat(0x30+year/10);
	write_dat(0x30+year%10);

	write_com(0x80+0x06);
	write_dat(0x30+mounth/10);
	write_dat(0x30+mounth%10);

	write_com(0x80+0x09);
	write_dat(0x30+date/10);
	write_dat(0x30+date%10);

	write_com(0x80+0x0c);
	write_dat(0x30+day/10);
	write_dat(0x30+day%10);
}

/*void alarm_inti(uchar ashi,uchar afen,uchar amiao)
{
	ds_write(1,amiao);
	ds_write(3,afen);
	ds_write(5,ashi);
}	*/

void didi()
{
	beep=0;
	delay(200);
	beep=1;
	delay(200);
	beep=0;
	delay(200);
	beep=1;
	delay(400);
}

void main()
{
	jian=0;
	jian1=0;
	leled=0;
	EA=1;
	EX1=1;
	IT1=1;
	inti();
	ds_write(0x0b,0x26);
//	inti_ds(15,57,3,19,8,5,1);
	write_string(table1,0x40);
//	alarm_inti(17,55,50);
	aa=ds_read(0x0c);
	while(1)
	{
		keyscan();
		if(flag==0)
		{
			read();
			displaysfmnyr();
		}
		if(flag1==1)
		didi();

	}
}

void alarm() interrupt 2
{
	flag1=1;
	aa=ds_read(0x0c);
}






