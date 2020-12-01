#include<reg52.h>
#include<2.4g.h>
#define uchar unsigned char
#define uint unsigned int
#define TX_ADD_WIDTH 5
#define TX_PLOAD_WIDTH 4

uchar TX_ADDRESS[TX_ADD_WIDTH]={0x34,0x43,0x10,0x10,0x01};
uchar TX_BUF[TX_PLOAD_WIDTH];
uchar RX_BUF[TX_PLOAD_WIDTH];
uchar bdata sta=0;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x76,0x79,0x38,0x3f};

sbit Key    =P3^7;
sbit K_Tx   =P3^1;
sbit K_Rx   =P3^2;
sbit K_Td   =P3^4;
sbit MAX_RT =sta^4;
sbit TX_DR  =sta^5;
sbit RX_DR  =sta^6;
sbit LED_T  =P1^1;
sbit LED_R	=P1^2;
sbit wela   =P2^7;
sbit dula   =P2^6;
sbit CE   = P2^0;  // Chip Enable pin signal (output)
sbit CSN  = P2^5;  // Slave Select pin, (output to CSN, nRF24L01)
sbit IRQ  = P3^3;  // Interrupt signal, from nRF24L01 (input)
sbit MISO = P2^2;  // Master In, Slave Out pin (input)
sbit MOSI = P2^1;  // Serial Clock pin, (output)
sbit SCK  = P2^4;  // Master Out, Slave In pin (output)

void init();
void delay(uchar z);
uchar SPI_RW(uchar dat);
uchar SPI_RW_Reg(uchar reg,uchar dat);
uchar SPI_Read(uchar reg);
uchar SPI_Write_Buf(uchar reg,uchar *buf,uchar num);
uchar SPI_Read_Buf(uchar reg,uchar *buf,uchar num);
void  RX_Mode();
void TX_Mode(uchar *BUF);
uchar Check_Ack(bit clear);
void TX_Dat_1(uchar dat);
uchar RX_Dat();
void display(uchar bai,uchar shi,uchar ge,uchar cc,uchar dd);

void main()
{ 
	init();
	 while(1)
	 {				 
		 RX_Dat();	
		 display(RX_BUF[0],RX_BUF[1],RX_BUF[2],RX_BUF[3],0);		
	 }	 
}

void init()
{
	CE=0;
	CSN=1;
	SCK=0;
	IRQ=1;
	LED_T=1;
	LED_R=1;
} 

void delay(uchar z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

uchar SPI_RW(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		dat<<=1;
		MOSI=CY;
		SCK=1;
		dat|=MISO;
		SCK=0;
	}
	return dat;
}

uchar SPI_RW_Reg(uchar reg,uchar dat)
{
	uchar status;
	CSN=0;
	status=SPI_RW(reg);
	SPI_RW(dat);
	CSN=1;
	return status;
}

uchar SPI_Read(uchar reg)
{
	uchar reg_val;
	CSN=0;
	SPI_RW(reg);
	reg_val=SPI_RW(0);
	CSN=1;
	return reg_val;
}

uchar SPI_Write_Buf(uchar reg,uchar *buf,uchar num)
{
	 uchar i,status;
	 CSN=0;
	 status=SPI_RW(reg);
	 for(i=0;i<num;i++)
	 {
	 	SPI_RW(buf[i]);
	 }
	 CSN=1;
	 return status;
}

uchar SPI_Read_Buf(uchar reg,uchar *buf,uchar num)
{
	uchar i,status;
	CSN=0;
	status=SPI_RW(reg);
	for(i=0;i<num;i++)
	{
		buf[i]=SPI_RW(0);
	}
	CSN=1;
	return status;
}

void  RX_Mode()
{
	CE=0;
	SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,TX_ADDRESS,TX_ADD_WIDTH);
	SPI_RW_Reg(WRITE_REG+EN_AA,0x01);
	SPI_RW_Reg(WRITE_REG+EN_RXADDR,0x01);
	SPI_RW_Reg(WRITE_REG+RF_CH,0x40);
	SPI_RW_Reg(WRITE_REG+RX_PW_P0,TX_PLOAD_WIDTH);
	SPI_RW_Reg(WRITE_REG+RF_SETUP,0x07);
	SPI_RW_Reg(WRITE_REG+CONFIG,0x0f);
	CE=1;
}

void TX_Mode(uchar *BUF)
{
	CE=0;
	SPI_Write_Buf(WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADD_WIDTH);
	SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,TX_ADDRESS,TX_ADD_WIDTH);
	SPI_Write_Buf(WR_TX_PLOAD,BUF,TX_PLOAD_WIDTH);
	SPI_RW_Reg(WRITE_REG+EN_AA,0x01);
	SPI_RW_Reg(WRITE_REG+EN_RXADDR,0x01);
	SPI_RW_Reg(WRITE_REG+SETUP_RETR,0x0a);
	SPI_RW_Reg(WRITE_REG+RF_CH,0x40);
	SPI_RW_Reg(WRITE_REG+RF_SETUP,0x07);
	SPI_RW_Reg(WRITE_REG+CONFIG,0x0e);
	CE=1;
}

uchar Check_Ack(bit clear)
{
	uchar status;
	while(IRQ);
	CSN=0;
	sta=SPI_RW(NOP);
	CSN=1;
	if(MAX_RT)
	if(clear)
	SPI_RW(FLUSH_TX);
	status|=TX_DR;
	SPI_RW_Reg(WRITE_REG+STATUS,sta);
	return status;	
}

/*void keyscan()
{
 	Key=0;
	if(K_Tx==0)
	{
		delay(2);
		if(K_Tx==0)
		{
			TX_BUF=1
		}
	}
}
*/

void TX_Dat_1(uchar dat)
{
	TX_BUF[0]=dat;
	TX_Mode(TX_BUF);
	LED_T=0;
	Check_Ack(1);
	delay(500);
	LED_T=1;	
}

uchar RX_Dat()
{
	 uchar flag,i;
	 RX_Mode();
	 CSN=0;
	 sta=SPI_RW(NOP);
	 CSN=1;
	 if(RX_DR)
	 {
	 	CE=0;
		SPI_Read_Buf(RD_RX_PLOAD,RX_BUF,TX_PLOAD_WIDTH);
		flag=1;
		LED_R=0;
		for(i=0;i<50;i++)
		display(RX_BUF[0],RX_BUF[1],RX_BUF[2],RX_BUF[3],0);
		LED_R=1;
		for(i=0;i<50;i++)
		display(RX_BUF[0],RX_BUF[1],RX_BUF[2],RX_BUF[3],0);
	 }
	 SPI_RW_Reg(WRITE_REG+STATUS,sta);
	 delay(1);
	 return flag;
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
	delay(3);
	P0=0xff;
	
	wela=1;
	P0=0xfd;
	wela=0;
	P0=0xff;					
	dula=1;
	P0=table[shi];
	dula=0;
	delay(3);
	P0=0xff;
	
	wela=1;
	P0=0xfb;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[ge];
	dula=0;
	delay(3);
	P0=0xff;

	wela=1;
	P0=0xf7;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[cc];
	dula=0;
	delay(3);
	P0=0xff;

	wela=1;
	P0=0xef;
	wela=0;
	P0=0xff;
	dula=1;
	P0=table[dd];
	dula=0;
	delay(3);
	P0=0xff;
}