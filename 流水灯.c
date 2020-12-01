#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char	
#define  uint unsigned int
void delay(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
		for(j=110;j>0;j--);
}
int temp;
void main()
{
	temp=0xfe;
	P1=temp;
	delay(1000);
	while(1)
	{
		temp=_crol_(temp,1);
		P1=temp;
		delay(1000);
	}
}