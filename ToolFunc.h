#pragma once

//单纯地用来做任意键下一步的
void WaitAnyKey(void);

//键盘方向键获取
//1上-2右-3下-4左，0为按的不是方向键
int WaitDirectionKey(void);

//键盘数字获取，一般用来选择
//如果不是0-9的按键，返回大于9
unsigned int WaitNumKey(void);

//在区间[a,b]内平均分布的随机 a小b大 只能是正整数
unsigned int UniformRandom(unsigned int a, unsigned int b);

//给UniformRandom()新种子
void RandomSrand(void);

//基于UniformRandom()的范围浮动 (如6为中间值 上下浮动50%为随机[3,3])
unsigned int FloatingRandom(unsigned int mid, double percent);

//概率抽奖，概率0.01-1，
//不在概率范围内也会被处理掉，详见定义
bool Roll(float percent);