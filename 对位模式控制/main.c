#include "stc15f2k60s2.h"
#include "tim.h"
#include "intrins.h"

int num=0;
int	h=0;
int x=0;

//��������
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

//��ʱ��0
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

//������
void main(void)
{	
	EX0 = 1;//���ش�����ʽ���½��أ�
  IT0 = 1;
  EX1 = 1;//���ش�����ʽ���½��أ�
  IT1 = 1;
  EA =1;//�������ж�
	
	Timer0Init();//��ʱ��0

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

//�ж�1
void intr1() interrupt 2
{
	num++;
	if(num>7)
	{
		num=0;
	}
}

//�ж�0
void intr0() interrupt 0 
{	
	h++;
	if(h>3)
	{
		h=0;
	}
}