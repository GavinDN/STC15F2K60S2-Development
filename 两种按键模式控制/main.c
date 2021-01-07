#include "stc15f2k60s2.h"
#include "tim.h"
#include "intrins.h"

int num=0;
int	h=0;
int x=0;

//按键消抖
void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//定时器0
void timer0() interrupt 1 
{
	x++;
	if(x == 50)
	{
		P0=~(0x01<<num);
		P43=0;
	}
	else if(x==100)
	{
		P43=1;
		P0=0xff;
		x=0;
	}
}

//主函数
void main(void)
{	
	EX0 = 1;//边沿触发方式（下降沿）
  IT0 = 1;
  EX1 = 1;//边沿触发方式（下降沿）
  IT1 = 1;
  EA =1;//开启总中断
	
	Timer0Init();//定时器0

	while(1)
	{
		switch(h)
		{
			case 0:P0=~(0x01<<num);TR0=0;P43=1;break;
			case 1:P0=0xff;break;
			case 2:TR0=1;break;
		}
	}
}

//中断1
void intr1() interrupt 2
{
	num++;
	if(num>7)
	{
		num=0;
	}
}

//中断0
void intr0() interrupt 0 
{	
	h++;
	if(h>3)
	{
		h=0;
	}
}