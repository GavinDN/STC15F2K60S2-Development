#include <stc15f2k60s2.h>

unsigned char count,i=0;

void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA = 1;
}

void main()
{
	Timer0Init();
	while(1);
}

void tim0() interrupt 1
{
	if(++count==200)
	{
		P0=~(0x01<<i);//0x01:0000 0001 ~:表示二进制取反为1111 1110  <<:表示向左位移
		if(++i==8)i=0;//每200ms i的值加一，即每200ms LED灯由右到左位移一次
		count=0;
	}
}