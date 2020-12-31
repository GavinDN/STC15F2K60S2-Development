#include <stc15f2k60s2.h>
#include <intrins.h>

unsigned char keyval;

sbit k1=P3^2;//���尴��k1

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

//�ж�0
void intr0(void) interrupt 0 
{
	Delay10ms();//��������
	
	if(k1 == 0)
	{
		unsigned char i;
		
		switch(i)//�жϰ�����ֵ
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

//������
void main(void)
{
	EX0 = 1;//���ش�����ʽ���½��أ�
  IT0 = 1;
  EA =1;//�������ж�
	
	while(1)
	{
		P0=~(0x01<<keyval);//��һ����ˮ���ƶ�һλ������ΪLED1~LED8
	}
}