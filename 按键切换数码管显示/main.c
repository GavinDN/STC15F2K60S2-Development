#include "stc15f2k60s2.h"

typedef unsigned int u16;
typedef unsigned char u8;

sbit SER=P1^6;//����HC595����
sbit SCK=P3^4;//����HC595����
sbit RCK=P1^5;//����HC595����
sbit EN=P1^7;//����HC595����
sbit DS4=P4^4;//����λѡ����
sbit DS3=P4^5;//����λѡ����
sbit DS2=P4^6;//����λѡ����
sbit DS1=P4^7;//����λѡ����

sbit K2=P3^3;//���尴��K2

#define led P0

u8 seg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07};

//��ʱ����
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

//�������ʾ����
void Seg_Disp(void)
{
	u8 i,num,c;
	
	EN = 0;//����
	for (i=0;i<1;i++)
	{
		switch(i)//λѡDS4
		{
			case 0:DS4=0;DS3=1;DS2=1;DS1=1;break;
		}
			num=seg[a];
		for(c=0;c<8;c++)//��ѡ
		{
			SCK=0;
			SER=num&0x80;
			num=num<<1;
			SCK=1;
		}
		RCK=0;RCK=1;
		for(c=0;c<8;c++)//ȫ������
		{
			SCK=0;
			SER=0x00;
			SCK=1;
		}
		RCK=0;RCK=1;
	} 
}

//������
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

//�ж�1����������
void INT_1() interrupt 2
{
	Delay10ms();//��������
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