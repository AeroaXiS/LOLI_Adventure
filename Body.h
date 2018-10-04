#pragma once
//��Ӧ�ñ�ʵ�����ģ���ʱû�мӴ��麯��
class Body
{
protected:
	std::string strName;
	unsigned int unCurrentHealth, unMaxHealth;
	unsigned int unLevel;
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
	double dAtkModifier;
	//���о���ֵ
	unsigned long ulExp;
private:

public:
	//Ĭ�Ϲ��캯���˺��ӳ�1�ȼ�1����0
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
	unsigned long ulExpDrop;
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
