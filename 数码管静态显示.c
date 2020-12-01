#include<reg52.h>
sbit wle=P2^7; 
sbit dle=P2^6;
void main()
{
	wle=1;
	P0=0xc0;
	wle=0;
	dle=1;
	P0=0x3f;
	dle=0;
	while(1);
}