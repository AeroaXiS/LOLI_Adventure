#pragma once

//�������������������һ����
void WaitAnyKey(void);

//���̷������ȡ
//1��-2��-3��-4��0Ϊ���Ĳ��Ƿ����
int WaitDirectionKey(void);

//������[a,b]��ƽ���ֲ������ aСb�� ֻ����������
unsigned int UniformRandom(unsigned int a, unsigned int b);

//��UniformRandom()������
void UniformRandomSrand(void);

//����UniformRandom()�ķ�Χ���� (��6Ϊ�м�ֵ ���¸���50%Ϊ���[3,3])
unsigned int RangeUniformRandom(unsigned int mid, double percent);