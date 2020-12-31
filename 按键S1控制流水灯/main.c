#include <stc15f2k60s2.h>
#include <intrins.h>

unsigned char keyval;

sbit k1=P3^2;//定义按键k1

void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}

//中断0
void intr0(void) interrupt 0 
{
	Delay10ms();//按键消抖
	
	if(k1 == 0)
	{
		unsigned char i;
		
		switch(i)//判断按键键值
		{
			case 0:keyval=1;break;
			case 1:keyval=2;break;
			case 2:keyval=3;break;
			case 3:keyval=4;break;
			case 4:keyval=5;break;
			case 5:keyval=6;break;
			case 6:keyval=7;break;
			case 7:keyval=0;break;
		}
		i++;
		if(i==8)i=0;
	}
}

//主函数
void main(void)
{
	EX0 = 1;//边沿触发方式（下降沿）
  IT0 = 1;
  EA =1;//开启总中断
	
	while(1)
	{
		P0=~(0x01<<keyval);//按一下流水灯移动一位，方向为LED1~LED8
	}
}