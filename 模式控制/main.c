#include "stc15f2k60s2.h"
#include "tim.h"
#include "intrins.h"

unsigned char keyval=0;

sbit buzzer=P4^3;
sbit k1=P3^2;//���尴��k1
bit flag1000ms;

//��ʱ20ms���ڰ�������
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
	static unsigned int i;
	
	if(++i >= 500)
	{
		flag1000ms = !flag1000ms;
		i = 0;
	}
}

//ģʽ3
void model3(void)
{
	if(flag1000ms==1)
	{
		P0 = 0xff;buzzer=1;
	}
	if(flag1000ms==0)
	{
		buzzer = 0;P0=0xfe;
 	}
}

//�ж�0
void intr0(void) interrupt 0 
{	
	Delay20ms();//��������
	
	if(k1 == 0)
	{
		static unsigned char i=0;
		
		switch(i)//�жϰ�����ֵ
		{
			case 0:keyval=1;break;//0 0
			case 1:keyval=2;break;//1 1
			case 2:keyval=3;break;//2 0
		}
		i++;
		if(i>2)i=0;
	}
}

//������
void main(void)
{	
	Timer0Init();//��ʱ��0
	
	EX0 = 1;//���ش�����ʽ���½��أ�
  IT0 = 1;
  EX1 = 1;//���ش�����ʽ���½��أ�
  IT1 = 1;
  EA =1;//�������ж�

	while(1)
	{
		if(keyval==1)
		{P0=~0x01;}
		if(keyval==2)
		{P0=0xff;}
		if(keyval==3)
		{model3();}
	}
}