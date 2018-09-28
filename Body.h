#pragma once
//��Ӧ�ñ�ʵ�����ģ���ʱû�мӴ��麯��
class Body
{
private:
	unsigned int health;
	std::string name;
public:

public:
	Body();
	virtual ~Body();
	//���� ������ɵ��˺� �ɶ����Battle_Suffer()�ṩ
	unsigned int Battle_Hit(Body * enemy);
	//���ܹ��� �����ܵ����˺�
	unsigned int Battle_Suffer(unsigned int damege);
	//������
	bool IsDead(void);
	//��ȡ��ǰ����ֵ
	unsigned int Health(void);
	//���õ�ǰ����ֵ ������ ����
	unsigned int Health(unsigned int health);
	//����˭?���������ַ���
	std::string & WhoAmI(void);
	//����˭?��������
	void WhoAmI(const char * name);
};

class Player : public Body
{
public:
};

class Monster : public Body
{
public:
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
	Player * player;
	//ս���еĹ���
	Monster * monster;
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
	//���� ��ӡ���Խ��еĲ���
	void Start_Interaction_ListCommand(void);
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