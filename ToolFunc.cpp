#include "pch.h"
#include "ToolFunc.h"

//����ļ���Ĵ��_getch����ʱ����ͬʱ����Ƶ�������ڴ�
static char keyboardPressed;

void WaitAnyKey(void)
{
	keyboardPressed = _getch();
	if (keyboardPressed == '\r')
	{
		//�س���\r\n������
		_getch();
		return;
	}
	else if (keyboardPressed == 0x00 || keyboardPressed == 0xE0)
	{
		//��չ�ַ�Ҫ��취����������Ĳ��� //�������ʵҲ������
		_getch();
		return;
	}
	else
	{
		return;
	}
}

int WaitDirectionKey(void)
{
	keyboardPressed = _getch();
	//����Ƿ����������չ�� -32��224��������get���Ķ���
	if (keyboardPressed == -32 || keyboardPressed == 224)
	{
		//�����ֻ��������չ��
		keyboardPressed = _getch();
		//�����Ƿ�������߼�ͷ
		switch (keyboardPressed)
		{
			//�������
		case 72:
			return 1;
			break;
			//�������
		case 77:
			return 2;
			break;
			//�������
		case 80:
			return 3;
			break;
			//�������
		case 75:
			return 4;
			break;
			//��չ��ĸ
		default:
			return 0;
			break;
		}
	}
	else if (keyboardPressed == '\r')
	{
		//����������س�
		_getch();
		return 0;
	}
	else
	{
		//��Ϊ��ĸ��������չ���ˣ���ô���ֽڿ϶�...
		return 0;
	}
}

unsigned int UniformRandom(unsigned int a, unsigned int b)
{
	//Ȩ�����������ʽ
	return rand() % (b - a + 1) + a;
}

void UniformRandomSrand(void)
{
	//�ó���ʼ���е����ڵ�tick��ms�������ӣ�1ms��ѭ��������Ч
	srand(static_cast<unsigned int>(clock()));
}

unsigned int RangeUniformRandom(unsigned int mid, double percent)
{
	return UniformRandom(
		static_cast<unsigned int>(mid - mid * percent),
		static_cast<unsigned int>(mid + mid * percent));
}
