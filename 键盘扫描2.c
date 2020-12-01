#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar temp;
sbit d0=P1^0;
void delay(uchar z)
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
uchar keyscan()
{
	uchar num,flag=0;
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
					case 0xee:num=0;break;
					case 0xde:num=1;break;
					case 0xbe:num=2;break;
					case 0x7e:num=3;break;
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
					case 0xed:num=0;break;
					case 0xdd:num=1;break;
					case 0xbd:num=2;break;
					case 0x7d:num=3;break;
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
					case 0xeb:num=0;break;
					case 0xdb:num=1;break;
					case 0xbb:num=2;break;
					case 0x7b:num=3;break;
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
					case 0xe7:num=0;break;
					case 0xd7:num=1;break;
					case 0xb7:num=2;break;
					case 0x77:num=3;break;
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
			return num;
		}
	}
}
void main()
{
	while(1)
	{
		d0=keyscan();
	}
	
}