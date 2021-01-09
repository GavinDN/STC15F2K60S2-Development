#include "stc15f2k60s2.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit SER=P1^6;//定义HC595引脚
sbit SCK=P3^4;//定义HC595引脚
sbit RCK=P1^5;//定义HC595引脚
sbit EN=P1^7;//定义HC595引脚
sbit DS4=P4^4;//定义位选引脚
sbit DS3=P4^5;//定义位选引脚
sbit DS2=P4^6;//定义位选引脚
sbit DS1=P4^7;//定义位选引脚

sbit K2=P3^3;//定义按键K2

#define led P0

u8 seg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07};

//延时函数
void Delay10ms()//@11.0592MHz
{
	unsigned char i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}

u8 a=0;

//数码管显示功能
void Seg_Disp(void)
{
	u8 i,num,c;
	
	EN = 0;//消隐
	for (i=0;i<1;i++)
	{
		switch(i)//位选DS4
		{
			case 0:DS4=0;DS3=1;DS2=1;DS1=1;break;
		}
			num=seg[a];
		for(c=0;c<8;c++)//段选
		{
			SCK=0;
			SER=num&0x80;
			num=num<<1;
			SCK=1;
		}
		RCK=0;RCK=1;
		for(c=0;c<8;c++)//全灭清零
		{
			SCK=0;
			SER=0x00;
			SCK=1;
		}
		RCK=0;RCK=1;
	} 
}

//主函数
void main()
{
	led=0xfe;
	IT1 = 1;
	EX1 = 1;
  EA = 1;
	
	while(1)
	{
		Seg_Disp();
	}
}

u8 n=0;

//中断1，按键功能
void INT_1() interrupt 2
{
	Delay10ms();//按键消抖
	if(K2==0)
	{
		if(a<=8)
		{
		 	led=led<<1|0x01;
			a++;
			if(a==8)
      {
				led=0xfe;	
			  a=0;
			}
		}	 
	}
}