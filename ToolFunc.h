#pragma once

//�������������������һ����
void WaitAnyKey(void);

//���̷������ȡ
//��Ϊ1˳ʱ�뵽4��0Ϊ���Ƿ����
int WaitDirectionKey(void);

//������[a,b]��ƽ���ֲ������ aСb�� ֻ����������
unsigned int UniformRandom(unsigned int a, unsigned int b);

//��uniform_random()������
void UniformRandomSrand(void);

//����uniform_random()�ķ�Χ���� ��6Ϊ�м�ֵ ���¸���50%Ϊ���[3,3]
unsigned int RangeUniformRandom(unsigned int mid, double percent);