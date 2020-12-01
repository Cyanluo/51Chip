#include<reg52.h>
#include<2.4g.h>
#define uchar unsigned char
#define uint unsigned int
#define TX_ADD_WIDTH 5
#define TX_PLOAD_WIDTH 4
uchar bdata sta;
uchar TX_ADDRESS[TX_ADD_WIDTH]={0x34,0x43,0x10,0x10,0x01};
uchar TX_BUF[TX_PLOAD_WIDTH];
uchar RX_BUF[TX_PLOAD_WIDTH];


sbit Key    =P3^7;
sbit K_Tx   =P3^1;
sbit K_Rx   =P3^2;
sbit K_Td   =P3^4;
sbit MAX_RT =sta^4;
sbit TX_DR  =sta^5;
sbit RX_DR  =sta^6;
sbit LED_T  =P1^1;
sbit LED_R	=P1^2;
sbit CE   = P0^6;  // Chip Enable pin signal (output)
sbit CSN  = P0^5;  // Slave Select pin, (output to CSN, nRF24L01)
sbit IRQ  = P3^3;  // Interrupt signal, from nRF24L01 (input)
sbit MISO = P0^2;  // Master In, Slave Out pin (input)
sbit MOSI = P0^1;  // Serial Clock pin, (output)
sbit SCK  = P0^4;  // Master Out, Slave In pin (output)

void init();
void delay(uchar z);
uchar SPI_RW(uchar dat);
uchar SPI_RW_Reg(uchar reg,uchar dat);
uchar SPI_Read(uchar reg);
uchar SPI_Write_Buf(uchar reg,uchar *buf,uchar num);
uchar SPI_Read_Buf(uchar reg,uchar *buf,uchar num);
void  RX_Mode();
void TX_Mode(uchar *BUF);
uchar Check_Ack();
void TX_Dat_1(uchar dat);
uchar RX_Dat();
void clear_all();
void clear_TR(uchar T_R);
void clearTXFIFO();
void delayus(uchar t);

void main()
{
	uchar i;
	init();
	TX_Dat_1(1);	 	 
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
	delay(1);
}

void delayus(uchar t)
{
	while(t--);
}

uchar Check_Ack()
{
	uchar count;
	while(IRQ)
	{
	   if(count>20000)
	   {
	   		count=0;
			clear_all();
			return;	
	   }
	   else
	   {
	   		count++;
			delayus(10);
	   }
	}
	if(SPI_Read(STATUS)&TX_DR)
	{
		SPI_RW_Reg(WRITE_REG+STATUS,0xff);
		clearTXFIFO();
		return;
	}	
	else
	{
		SPI_RW_Reg(WRITE_REG+STATUS,0xff);
		clearTXFIFO();
	}
	return;
}

void clearTXFIFO()
{
	CSN=0;
	SPI_RW(FLUSH_TX);
	delayus(10);
	CSN=1;
}

void clear_TR(uchar T_R)
{
	CSN=0;
	if(T_R)
	SPI_RW(FLUSH_RX);
	else
	SPI_RW(FLUSH_TX);
	CSN=1;
}

void clear_all()
{
	clear_TR(0);
	clear_TR(1);
	SPI_RW_Reg(WRITE_REG+STATUS,0xff);
	IRQ=1;
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
	Check_Ack();
	delay(500);
	LED_T=1;
	delay(1);	
}

uchar RX_Dat()
{
	 uchar flag;
	 RX_Mode();
	 sta=SPI_Read(STATUS);
	 if(RX_DR)
	 {
	 	SPI_Read_Buf(RD_RX_PLOAD,RX_BUF,TX_PLOAD_WIDTH);
		flag=1;
		LED_R=0;
		delay(500);
		LED_R=1;
	 }
	 SPI_RW_Reg(WRITE_REG+STATUS,sta);
	 return flag;
}























