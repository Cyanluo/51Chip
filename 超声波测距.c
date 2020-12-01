#include<reg52.h>
#include<1602.h>
#define VELOCITY_30C	349.5       //30摄氏度时的声速，声速V= 331.5 + 0.6*温度； 
#define VELOCITY_23C	345.3       //23摄氏度时的声速，声速V= 331.5 + 0.6*温度；
uchar code table[]="     Ce Ju";
uchar code table1[]="distance:";
uint distance,count;
sbit input=P1^6;
sbit output=P1^7;
sbit beep=P2^3;
sbit jinbao=P3^2;

void timeinti()
{
	TMOD=0x01;
	TH0=0Xfc;
	TL0=0x6a;
	EA=1;
	EX0=1;
}

void write_string(uchar *p,uchar adress)
{
	uchar i;
	write_com(0x80+adress);
	for(i=0;p[i]!=0;i++)
	{
		write_dat(p[i]);
	}
}

void delayt(uint x)
{
    uchar j;
    while(x-- > 0)
    {
  	    for(j = 0;j < 125;j++)
        {
            ;
        }
    }
}

void sheng_bo()
{
	output=1;
	delayt(1);
	output=0;
}

void inti_MCU()
{
	input=0;
	output=0;
	distance=0;
	count=0;			 	
}

void write_shu()
{
	uchar a,b,c,d;
	a=distance/1000;
	b=distance%1000/100;
	c=distance%100/10;
	d=distance%10;
	write_string(table1,0x40);
	write_dat(0x30+a);
	write_dat(0x30+b);
	write_dat(0x30+c);
	write_dat('.');
	write_dat(0x30+d);
	write_dat('c');
	write_dat('m');
}

void measure()
{
	uchar x,y;
	float t;
	TR0=1;
	while(input){}
	TR0=0;
	x=TH0;
	y=TL0;
	t=count*1000+((x-0xfc)*256+(y-0x6a))*1.085;
	distance=VELOCITY_30C*t/2000;
	if(distance>4000)
	{
		distance=0;
	}
}

void main()
{
	inti();
	inti_MCU();
	timeinti();
	write_string(table,0x00);
	while(1)
	{
		sheng_bo();
		while(!input){}
		measure();
		write_shu();
		if(distance>1000)
		{
			jinbao=0;
		}
		TH0=0xfc;
		TL0=0x6a;
		inti_MCU();
		delayt(130);	
	}

}

void timer0() interrupt 1
{
	count++;
	TH0=0xfc;
	TL0=0x6a;
	if(count==18)
	{
		TR0=0;
		count=0;
	}
}

void baojin() interrupt 0
{
	beep=0;
	delayt(100);
	beep=1;
	jinbao=1;
}

																															