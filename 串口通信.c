#include<reg52.h>
#define uchar unsigned char
sbit wela=P2^7;
sbit dula=P2^6;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x79,0x38,0x3f};
void delay(uchar z);
void display(uchar bai,uchar shi,uchar ge,uchar cc,uchar dd);
void main()
{
	uchar aa=0,bai,shi,ge,biao[6],bb,cc,i;
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	SM0=0;
	SM1=1;
	REN=1;
//	EA=1;
//	ES=1;
	while(1)
	{
		if(RI==1)
		{
			RI=0;
			P1=SBUF;
			aa=SBUF;
			SBUF=aa;
		}
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
		display(bai,shi,ge,bb,cc);
	};
}
/*void es() interrupt 4
{
	RI=0;
	P1=SBUF;
} */
void delay(uchar z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void display(uchar bai,uchar shi,uchar ge,uchar cc,uchar dd)
{
	wela=1;
	P0=0xfe;
	wela=0;
	P0=0xff;								//ÏûÓ°
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