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
	unsigned int BattleCommonHit(Body * enemy);
	//���ܹ��� �����ܵ����˺�
	unsigned int BattleSuffer(unsigned int damege);
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
	//���㹥���� һ�κ��� ��ȼ��仯 k��������
	virtual unsigned int GetAtk(double k) = 0;
};

class Player : public Body
{
private:
	//װ���Ĺ������ӳ� ���� x1.001
	double atkModifier;
public:
	Player();
	unsigned int GetAtk(double k);
};

class Monster : public Body
{
public:
	unsigned int GetAtk(double k);
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
	Player * plr;
	//ս���еĹ���
	Monster * mst;
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