#pragma once

//�������������������һ����
void WaitAnyKey(void);

//���̷������ȡ
//��Ϊ1˳ʱ�뵽4��0Ϊ���Ƿ����
int WaitDirectionKey(void);

//������[a,b]��ƽ���ֲ������ aСb�� ֻ����������
//1ms�ڸ��ٷ��ʻᱬը
unsigned int uniform_random(unsigned int a, unsigned int b, bool newSeed = false);