#pragma once

//单纯地用来做任意键下一步的
void WaitAnyKey(void);

//键盘方向键获取
//上为1顺时针到4，0为不是方向键
int WaitDirectionKey(void);

//在区间[a,b]内平均分布的随机 a小b大 只能是正整数
//1ms内高速访问会爆炸
unsigned int uniform_random(unsigned int a, unsigned int b, bool newSeed = false);