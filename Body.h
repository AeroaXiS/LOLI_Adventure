#pragma once
class Body
{
private:
	unsigned int health;
public:

public:
	Body();
	virtual ~Body();
	//����
	void Battle_Hit(Body * enemy);
	//���ܹ���
	void Battle_Suffer(unsigned int damege);
	//������
	bool IsDead(void);
	//��ȡ��ǰ����ֵ
	unsigned int Health(void);
	//���õ�ǰ����ֵ ������ ����
	unsigned int Health(unsigned int health);
};

class Player : public Body
{

};

class Monster : public Body
{

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
	///WaitKeyboard�п��ܻᱻ�����ʵĶ��������ɳ�Ա�������ٹ�������
	///std::string keyboardCache;
	//WaitKeyboard���п��ܻᱻ�����ʵĶ��������ɳ�Ա���������ڴ�����
	char keyboardPressed;
private:
	//ս������������Ƿ���Կ�ս
	bool IsAllReady(void);
	//�Ƿ�������˻��߹�������
	bool IsFinshed(void);
	//��ӡս��˫����״̬
	bool ShowState(void);
	//�����˺�
	bool Fuck(void);
	//��������Դ�������
	void WaitKeyboard(void);
public:

public:
	//��������һ��ս��
	static Battlefield * CreateBattlefield(void);
	//ʲô����μ���ս����ע�ⲻҪ���λ��
	bool WhoseBattlefield(Player * player, Monster * monster);
	//��ʼս�� ����trueΪ���ʤ��
	bool Start(void);
};