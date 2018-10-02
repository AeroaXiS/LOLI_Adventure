#pragma once
//��Ӧ�ñ�ʵ�����ģ���ʱû�мӴ��麯��
class Body
{
protected:
	std::string name;
	unsigned int currentHealth, maxHealth;
	unsigned int level;
public:
	Body();
	virtual ~Body();
	//���� ������ɵ��˺� �ɶ����Battle_Suffer()�ṩ
	unsigned int BattleCommonHit(Body * enemy);
	//���ܹ��� �����ܵ����˺�
	unsigned int BattleSuffer(unsigned int damege);
	//������
	bool IsDead(void);
	//����ǰ����ֵ���ó�����ֵ���޲�����
	virtual unsigned int ResetCurrentHealth(void) = 0;
	//��ȡ��ǰ����
	unsigned int GetCurrentHealth(void);
	//����˭?���������ַ���
	std::string & WhoAmI(void);
	//����˭?��������
	void WhoAmI(const char * name);
	//���㹥���� һ�κ��� ��ȼ��仯 k��������
	virtual unsigned int GetAtk(double k) = 0;
	//��ȡ�ȼ�
	unsigned int GetLevel(void);
	//���õȼ�
	void SetLevel(unsigned int level);
	//��ȡ����ֵ����
	unsigned int GetMaxHealth(void);
};

class Player : public Body
{
private:
	//װ���Ĺ������ӳ� ���� x1.001
	double atkModifier;
	//���о���ֵ
	unsigned long exp;
private:

public:
	Player();
	//���ݵȼ���������ֵ����
	void SetMaxHealth(void);
	//����ǰ����ֵ���õ�����ֵ����(��ʼ��
	unsigned int ResetCurrentHealth(void);
	//��ȡ������
	unsigned int GetAtk(double k);
	//���ù������ӳ�
	void SetAtkModifier(double atkModifier);
	//��ȡ�������ӳ�
	double GetAtkModifier(void);
	//���� ����������ĵȼ�
	unsigned int LevelUp(void);
	//�������㹻�����������棬�����������ؼ�
	bool IsAbleToLevelUp(void);
	//�����������辭��ֵ
	unsigned long ExpNeed(void);
	//���ص�ǰ����ֵ
	unsigned long ExpHave(void);
	//��þ��� ���ص�ǰ����
	unsigned long AwardExp(unsigned long quantity);
};

class Monster : public Body
{
private:
	//����ľ���ֵ
	unsigned long expDrop;
public:
	//��ȡ������
	unsigned int GetAtk(double k);
	//ģ����� ���ݵȼ�(����)��������ֵ���޲��ҷ���
	void SetMaxHealth(void);
	//������ֵ��������ֵ����
	void SetMaxHealth(unsigned int maxHealth);
	//����ǰ����ֵ���õ�����ֵ����(��ʼ��
	unsigned int ResetCurrentHealth(void);
	//��ȡ���Ե���ľ���ֵ
	unsigned long GetExpDrop(void);
	//���ÿ��Ե���ľ���ֵ
	void SetExpDrop(unsigned long expDrop);
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