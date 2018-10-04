#pragma once

//�ж�����ö��
enum ActionType
{
	//û���κζ���������
	AT_NONE = 0,
	//��ͨ����
	AT_NORMAL = 1
};

//�ж�
struct Action
{
	//�ж�������
	Body * pbySender;
	//�ж�������
	Body * pbyVictim;
	//�ж�����
	ActionType at;
	//�ж���������1
	unsigned int unData1;
	//�ж���������2
	unsigned int unData2;
};


/*
����ģʽ��ս������Ϸֻ�ܴ���һ��ս����
ͨ��CreateBattlefield()���������ߵõ���ǰս����ս��������Ҫ�ֶ��ͷš�
���ݽ�����������н���
*/
class Battlefield
{
private:
	Battlefield()
	{
	}
	//ս���е����
	Player * pPlayer;
	//ս���еĹ���
	Monster * pMonster;
	//ʵ������ָ��
	static Battlefield * pBattlefield;
	//�ܶ�ط�Ҫ�õ����ַ�����
	std::stringstream ss;
	//"��ʾ��"�������б�
	std::vector<std::string> vMessage;
	//�ж�����
	std::vector<Action> vActionQueue;
private:
	//�Ƿ�������˻��߹�������
	bool IsFinshed(void);
	//��ӡ�����ָ����ݵ���
	void PrintLine(void);
	//��ӡս��˫����״̬
	bool ShowState(void);
	//��ӡ��ʾ������8��
	bool ShowMessages(void);
	//����ʾ������ʾ�б�����64��
	bool AddMessage(const char * str);
	//���� ������������false
	bool Start_Interaction(void);
	//ս������������Ƿ���Կ�ս
	bool Start_IsReady(void);

	//����ж�
	int AddAction(Body * pbySender, Body * pbyVictim, ActionType at,
				  unsigned int data1, unsigned int data2);
	//����ж�
	int FlushActionQueue(void);
	//ִ�ж���
	int RunAcionQueue(void);

public:
	//��������һ��ս��
	static Battlefield * CreateBattlefield(void);
	//ʲô����μ���ս����ע�ⲻҪ���λ��
	bool WhoseBattlefield(Player * player, Monster * monster);
	//��ʼս�� ����trueΪ���ʤ��
	bool Start(void);
};