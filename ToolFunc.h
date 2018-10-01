#pragma once

//单纯地用来做任意键下一步的
void WaitAnyKey(void);

//键盘方向键获取
//上为1顺时针到4，0为不是方向键
int WaitDirectionKey(void);

//在区间[a,b]内平均分布的随机 a小b大 只能是正整数
unsigned int UniformRandom(unsigned int a, unsigned int b);

//给uniform_random()新种子
void UniformRandomSrand(void);

//基于uniform_random()的范围浮动 如6为中间值 上下浮动50%为随机[3,3]
unsigned int RangeUniformRandom(unsigned int mid, double percent);