#pragma once


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
	//"��ʾ��"�������б�
	std::vector<std::string> vMessage;
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
	//�����˺�
	bool AttackRound(void);
	//���� ������������false
	bool Start_Interaction(void);
	//ս������������Ƿ���Կ�ս
	bool Start_IsReady(void);
public:

public:
	//��������һ��ս��
	static Battlefield * CreateBattlefield(void);
	//ʲô����μ���ս����ע�ⲻҪ���λ��
	bool WhoseBattlefield(Player * player, Monster * monster);
	//��ʼս�� ����trueΪ���ʤ��
	bool Start(void);
};