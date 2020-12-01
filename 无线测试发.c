 #include <reg51.h>
#include <2.4g.h>

#define uchar unsigned char
#define uint unsigned int

/***************************************************/
#define TX_ADR_WIDTH   5  // 5�ֽڿ�ȵķ���/���յ�ַ
#define TX_PLOAD_WIDTH 5  // ����ͨ����Ч���ݿ��
#define RX_ADR_WIDTH   5  // 5�ֽڿ�ȵķ���/���յ�ַ
#define RX_PLOAD_WIDTH 5  // ����ͨ����Ч���ݿ��
#define LED P1
uchar code TX_ADDRESS[TX_ADR_WIDTH]={0x01,0x03,0x05,0x07,0x09};
uchar code RX_ADDRESS[TX_ADR_WIDTH]={0x01,0x03,0x05,0x07,0x09};
uchar TX_BUF[10]="sdfsd";
uchar RX_BUF[10];
bdata unsigned char st1=0;
sbit st_11=st1^0;
sbit st_12=st1^1;
sbit st_13=st1^2;
sbit st_14=st1^3;
sbit st_15=st1^4;
sbit st_16=st1^5;
sbit st_17=st1^6;
sbit st_18=st1^7;

bdata unsigned char st=0;
sbit st_1=st^0;
sbit st_2=st^1;
sbit st_3=st^2;
sbit st_4=st^3;
sbit st_5=st^4;
sbit st_6=st^5;
sbit st_7=st^6;
sbit st_8=st^7;

uchar bdata sta;
sbit  RX_DR	 = sta^6;
sbit  TX_DS	 = sta^5;
sbit  MAX_RT = sta^4;
sbit CE   = P1^7;  // Chip Enable pin signal (output)
sbit CSN  = P1^6;  // Slave Select pin, (output to CSN, nRF24L01)
sbit IRQ  = P1^2;  // Interrupt signal, from nRF24L01 (input)
sbit MISO = P1^3;  // Master In, Slave Out pin (input)
sbit MOSI = P1^4;  // Serial Clock pin, (output)
sbit SCK  = P1^5;  // Master Out, Slave In pin (output)
sbit key  = P3^7;
sbit LEDc = P1^5;



void delayus(uchar t)
{
	while(--t);
}


void delay_ms(uchar x)
{
    uchar i, j;
    i = 0;
    for(i=0; i<x; i++)
    {
       j = 250;
       while(--j);
	   j = 250;
       while(--j);
    }
}

uchar SPI_RW(uchar byte)
{
	//uchar bit_ctr;

    st=byte;

    MOSI=st_8;
    SCK = 1;
    st_18=MISO;
    SCK = 0;

    MOSI=st_7;
    SCK = 1;
    st_17=MISO;
    SCK = 0;

    MOSI=st_6;
    SCK = 1;
    st_16=MISO;
    SCK = 0;

    MOSI=st_5;
    SCK = 1;
    st_15=MISO;
    SCK = 0;

    MOSI=st_4;
    SCK = 1;
    st_14=MISO;
    SCK = 0;

    MOSI=st_3;
    SCK = 1;
    st_13=MISO;
    SCK = 0;

    MOSI=st_2;
    SCK = 1;
    st_12=MISO;
    SCK = 0;

    MOSI=st_1;
    SCK = 1;
    st_11=MISO;
    SCK = 0;
    return(st1);           		  // return read byte
}	

/*uchar SPI_RW(uchar byte)
{
	uchar i;
   	for(i=0; i<8; i++)          // ѭ��8��
   	{
   		MOSI = (byte & 0x80);   // byte���λ�����MOSI
   		byte <<= 1;             // ��һλ��λ�����λ
   		SCK = 1;                // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
   		byte |= MISO;       	// ��MISO��byte���λ
   		SCK = 0;            	// SCK�õ�
   	}
    return(byte);           	// ���ض�����һ�ֽ�
} */

uchar SPI_RW_Reg(uchar reg, uchar value)
{
	uchar status;
  	CSN = 0;                   // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);      // ѡ��Ĵ�����ͬʱ����״̬��
  	SPI_RW(value);             // Ȼ��д���ݵ��üĴ���
  	CSN = 1;                   // CSN���ߣ��������ݴ���
  	return(status);            // ����״̬�Ĵ���
}

uchar SPI_Read(uchar reg)
{
	uchar reg_val;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	SPI_RW(reg);                // ѡ��Ĵ���
  	reg_val = SPI_RW(0);        // Ȼ��ӸüĴ���������
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(reg_val);            // ���ؼĴ�������
}

uchar SPI_Read_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
	uchar status, i;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
  	for(i=0; i<bytes; i++)
    	pBuf[i] = SPI_RW(0);    // ����ֽڴ�nRF24L01����
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(status);             // ����״̬�Ĵ���
}

uchar SPI_Write_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
	uchar status, i;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
  	for(i=0; i<bytes; i++)
    	SPI_RW(pBuf[i]);        // ����ֽ�д��nRF24L01
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(status);             // ����״̬�Ĵ���
}

void init_nrf(void)
{
	delayus(200);
	CE = 0;
	CSN=1;
	SCK=0;
  	SPI_Write_Buf(WRITE_REG +TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);  // �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);               // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);           // ʹ�ܽ���ͨ��0
  	SPI_RW_Reg(WRITE_REG + RF_CH, 40);                 // ѡ����Ƶͨ��0x40
  	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);  // ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x0f);            // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	IRQ=1;
}

void SetRX_Mode()
{
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);              // CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
	CE=1;
	delayus(130);
}

uchar rx_packet(uchar *rx_buf)
{
	uchar revale=0;
//	RX_DR=0;
	sta=SPI_Read(STATUS);
	SPI_RW_Reg(WRITE_REG+STATUS,0xff);
//	RX_DR=0;
	if(RX_DR)
	{
		CE=0;
		LEDc=0;
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf, TX_PLOAD_WIDTH);  // ��RX FIFO��������
		revale=1;
		LEDc=1;
	}
	SPI_RW_Reg(WRITE_REG+STATUS,sta);
	return revale;						   
}

void clear_txfifo()
{
	CSN=0;
	SPI_RW(FLUSH_TX);
	delayus(10);
	CSN=1;
}

void clear_tr(uchar R_T)
{
	CSN=0;
	if(R_T==1)
	SPI_RW(FLUSH_TX);
	else
	SPI_RW(FLUSH_RX);
	CSN=1;
}

void ifnref_clear_all()
{
	clear_tr(0);
	clear_tr(1);
	SPI_RW_Reg(WRITE_REG+STATUS,0xff);
	IRQ=1;
}

void tx_packet(uchar * BUF)
{
	uint count,sta;
	CE = 0;
  	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // д�뷢�͵�ַ
  	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ
  	SPI_Write_Buf(WR_TX_PLOAD, BUF, TX_PLOAD_WIDTH);                  // д���ݰ���TX FIFO
  	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);       // ʹ�ܽ���ͨ��0�Զ�Ӧ��
  	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);   // ʹ�ܽ���ͨ��0
  	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x0f);  // �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
  	SPI_RW_Reg(WRITE_REG + RF_CH, 40);         // ѡ����Ƶͨ��0x40
  	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x1a);    // ���ݴ�����1Mbps�����书��0dBm���������Ŵ�������
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);      // CRCʹ�ܣ�16λCRCУ�飬�ϵ�
	CE = 1;
	delayus(20);
	count=0;
	while(IRQ==1)
	{
		if(count>20000)
		{
			count=0;
			ifnref_clear_all();
			return;
		}
		else 
		{
			count++;
			delayus(10);
		}			 
	}
/*	if(SPI_Read(STATUS)&STA_MARX_TX)
	{
		SPI_RW_Reg(WRITE_REG+STATUS,0xff);
		clear_txfifo();
		return;
	}
	else
	{
		SPI_RW_Reg(WRITE_REG+STATUS,0xff);
		clear_txfifo();
	}
	return;*/
	sta=SPI_Read(STATUS);
	if(MAX_RT)
	{
		SPI_RW_Reg(WRITE_REG+STATUS,sta);
		clear_txfifo();
	}
}





void main(void)
{
	uchar a;
	init_nrf();
	EA=1;
	EX1=1;
	IT1=1;
	TX_BUF[0]=1;
	TX_BUF[0]=1;
	TX_BUF[0]=1;
	TX_BUF[0]=1;
	   while(1)
	   {
			SetRX_Mode();
			rx_packet(RX_BUF);
			if(key==0)
			{
				delay_ms(2);
				if(key==0)
				{
					tx_packet(TX_BUF);
					delay_ms(10);
//					TX_BUF[0]++;
					while(!key);
				}
			}
//			P1=RX_BUF[0];
			sta=SPI_Read(STATUS);
			P0=sta;
		}
		
		

	
	
}

/*void crc() interrupt 2
{
	LEDc=0;
} */