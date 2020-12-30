#include <stc15f2k60s2.h>

unsigned char count,i=0;

void Timer0Init(void)		//1����@11.0592MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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
		P0=~(0x01<<i);
		if(++i==8)i=0;
		count=0;
	}
}