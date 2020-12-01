/*******************************************************************/
/*                         AT24c02							   	   */
/*                         E2PROM						  		   */
/*                         I2C总线		                           */
/*******************************************************************/
#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
sbit scl=P2^1;
sbit sda=P2^0;

void delay1(uint z)						 //z毫秒延时
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void delay()
{
	;;
}

void start()							   //开始信号
{
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();
}

void stop()									//停止信号
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();
}

void ack()									//应答信号
{
	uchar i=255;
	scl=1;
	while(sda==1&&i>0)i--;
	sda=1;
	scl=0;
}

void write_byte(uchar dat)					//写一个字节
{
	uchar i,aa;
	scl=0;
	delay();
	aa=dat;
	for(i=0;i<8;i++)
	{
		dat=dat<<1;
		sda=CY;
		scl=1;
		delay();
		scl=0;
		delay();
		sda=1;
		delay();
	}
}

uchar read_byte()							 //读一个字节
{
	uchar i,x,y;
	scl=0;
	delay();
	for(i=0;i<8;i++)
	{
		scl=1;
    	delay();
		x=sda;
		y=y<<1|x;
		scl=0;
		delay();
		sda=1;
		delay();
	}
	return y;
}

void randon_write(uchar add,uchar dat)			  //指定地址写
{
	start();
	write_byte(0xa0);
	ack();
	write_byte(add);
	ack();
	write_byte(dat);
	ack();
	stop();
	delay1(100);
}

uchar randon_read(uchar add)					   //指定地址读
{
	uchar aa;
	start();
	write_byte(0xa0);
	ack();
	write_byte(add);
	ack();
	start();
	write_byte(0xa1);
	ack();
	aa=read_byte();
	stop();
	delay1(100);
	return aa;
}


void main()
{
	randon_write(5,0x01);
	P1=randon_read(5);
	while(1);
}











