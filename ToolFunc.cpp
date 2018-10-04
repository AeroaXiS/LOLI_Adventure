#include "pch.h"
#include "ToolFunc.h"

//这个文件里的存放_getch的临时对象，同时避免频繁申请内存
static char keyboardPressed;

void WaitAnyKey(void)
{
	keyboardPressed = _getch();
	if (keyboardPressed == '\r')
	{
		//回车有\r\n两部分
		_getch();
		return;
	}
	else if (keyboardPressed == 0x00 || keyboardPressed == 0xE0)
	{
		//拓展字符要想办法抛弃掉后面的部分 //方向键其实也是这样
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
	//如果是方向键或者拓展键 -32和224都是网上get到的东西
	if (keyboardPressed == -32 || keyboardPressed == 224)
	{
		//方向键只可能是拓展键
		keyboardPressed = _getch();
		//可能是方向键或者箭头
		switch (keyboardPressed)
		{
			//方向键上
		case 72:
			return 1;
			break;
			//方向键右
		case 77:
			return 2;
			break;
			//方向键下
		case 80:
			return 3;
			break;
			//方向键左
		case 75:
			return 4;
			break;
			//拓展字母
		default:
			return 0;
			break;
		}
	}
	else if (keyboardPressed == '\r')
	{
		//玩家作死按回车
		_getch();
		return 0;
	}
	else
	{
		//因为字母方向都是拓展的了，那么单字节肯定...
		return 0;
	}
}

unsigned int UniformRandom(unsigned int a, unsigned int b)
{
	//权威的随机数公式
	return rand() % (b - a + 1) + a;
}

void UniformRandomSrand(void)
{
	//用程序开始运行到现在的tick即ms来做种子，1ms内循环进行无效
	srand(static_cast<unsigned int>(clock()));
}

unsigned int RangeUniformRandom(unsigned int mid, double percent)
{
	return UniformRandom(
		static_cast<unsigned int>(mid - mid * percent),
		static_cast<unsigned int>(mid + mid * percent));
}
