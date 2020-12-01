/*******************************************************************/
/*红外、声音、继电器控制灯										   */
/*声音超过预定值延时开灯（电位器调节）						       */
/*红外控制常开、常灭灯		                                       */
/*******************************************************************/
#include<reg52.h>
#define uchar unsigned char 
#define uint unsigned int
sbit jdq=P3^0;							  //继电器控制口
sbit sk=P2^0;							  //声音传感器控制口
sbit ir=P3^3;							  //红外接收口
sbit hw=P1^7;							  //人体红外感应接口
uchar jiema[2]={0,0};					  
uchar shu[4],flag,a;

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)					  //延时大概z毫秒
		for(y=110;y>0;y--);
}

void delay1(uchar x)
{
	uchar i;
	while(x--)
	{
		for(i=0;i<13;i++){}
	}
}

void inti()								 //初始化外部中断1
{
	EA=1;
	EX1=1;
	IT1=1;
}
void bianma()  interrupt 2	 
{
	uchar x,y,num=0;
	EX1=0;
	delay1(15);								 //消抖
	if(ir==1)								
	{
		EX1=1;
		return ;		
	}
	while(!ir)
		{
			delay1(1);
		}
	for(x=0;x<4;x++)						 //获取32位4个数据
	{
		for(y=0;y<8;y++)
		{
			while(ir)
			{
				delay1(1);
			}
			while(!ir)
			{
				delay1(1);
			}
			while(ir)						  //计算高电平的时长
			{
				delay1(1);			
				num++;
				if(num>=30)					  //时间超出范围终止获取数据
				{
					EX1=1;
					return ;
				}
			}								
			shu[x]=shu[x]>>1;
			if(num>=8)						   //根据时长判断1、0
			{
				shu[x]=shu[x]|0x80;
			}
			num=0;
		}
	}
		if(shu[2]==~shu[3])					   //检测数据与其反码是否对应
		{
			flag=1;							   //按键按下后允许红外控制标志置位
		}
		EX1=1;
}

void main()
{
	jdq=0;
	inti();
	while(1)
	{
		if(sk==0)										//声音超过预定值
		{
			jdq=1;										//开灯
			delay(1000);
			delay(1000);
			jdq=0;										//延时后关灯
		}
		if(flag==1)
		{
			jiema[0]=shu[2]>>4;	  
			jiema[1]=shu[2]&0x0f;
			if(jiema[0]==1&&jiema[1]==6)				 //红外按键解码值92
			{
				jdq=1;									 //开灯
			}
			if(jiema[0]==1&&jiema[1]==9)				 //红外按键解码值93
			{
				jdq=0;									//关灯
			}
			
	
			flag=0;
		}
/*		if(hw==1)										//人体红外感应
		{
			jdq=1;										//开灯
			delay(1000);
			delay(1000);
			jdq=0;										//延时后关灯	 
		}	  */
	}
}