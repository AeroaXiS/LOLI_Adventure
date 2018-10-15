#pragma once
//不应该被实例化的，暂时没有加纯虚函数
class Body
{
protected:
	std::string strName;
	unsigned int unCurrentHealth, unMaxHealth;
	unsigned int unLevel;
	unsigned int unBasicAtk, unBasicDef;
	double dAtkBonus, dDefBonus;
public:
	Body();
	virtual ~Body();

	//死了吗
	bool IsDead(void);
	//将当前生命值设置成生命值上限并返回
	virtual unsigned int ResetCurrentHealth(void) = 0;
	//获取当前生命
	unsigned int GetCurrentHealth(void);
	//获取生命值上限
	unsigned int GetMaxHealth(void);
	//减少生命值，返回现在生命值
	unsigned int DecreaseHealth(unsigned int unDamage);
	//增加生命值，返回现在生命值
	unsigned int IncreaseHealth(unsigned int unHeal);

	//我是谁?返回名字字符串
	std::string & GetName(void);
	//我是谁?赋予名字
	void SetName(const char * name);

	//获取等级
	unsigned int GetLevel(void);
	//设置等级
	void SetLevel(unsigned int level);

	//获取总攻击力(加成后
	unsigned int GetAtk(void);
	//设置攻击力加成（对于基础攻击力
	void SetAtkBonus(double dAtkBonus);
	//刷新等级相关的基础攻击力
	virtual unsigned int UpdateBasicAtk(void) = 0;

	//获取总防御力(加成后
	unsigned int GetDef(void);
	//设置防御力加成（对于基础防御力
	void SetDefBonus(double dDefBonus);
	//刷新等级相关的基础防御力
	virtual unsigned int UpdateBasicDef(void) = 0;
};

class Player : public Body
{
private:
	//持有经验值
	unsigned long ulExp;
private:
	//升级 返回升级后的等级
	unsigned int LevelUp(void);
	//若经验足够则升级返回真，否则不升级返回假
	bool IsAbleToLevelUp(void);
public:
	//默认构造函数加成1等级1经验0
	Player();

	//根据等级设置生命值上限
	void SetMaxHealth(void);
	//将当前生命值设置到生命值上限(初始化
	unsigned int ResetCurrentHealth(void);

	//返回升级所需经验值
	unsigned long GetExpNeed(void);
	//返回当前经验值
	unsigned long GetExpOwn(void);

	//获得经验 返回当前经验
	unsigned long AwardExp(unsigned long quantity);
	//检测是否可以升级并且升级，返回0没有升级，正常返回升级后等级
	unsigned int CheckLevelUp(void);

	//刷新等级相关的基础攻击力
	unsigned int UpdateBasicAtk(void);
	//刷新等级相关的基础防御力
	unsigned int UpdateBasicDef(void);
};

class Monster : public Body
{
private:
	//掉落的经验值
	unsigned long ulExpDrop;
private:

public:
	//默认构造等级1生命64经验掉落1024
	Monster();
	//方便复制怪物吧
	Monster(Monster &right);

	//按照数值设置生命值上限
	void SetMaxHealth(unsigned int maxHealth);
	//将当前生命值设置到生命值上限(初始化
	unsigned int ResetCurrentHealth(void);

	//获取可以掉落的经验值
	unsigned long GetExpDrop(void);
	//设置可以掉落的经验值
	void SetExpDrop(unsigned long expDrop);

	//刷新等级相关的基础攻击力
	unsigned int UpdateBasicAtk(void);
	//刷新等级相关的基础防御力
	unsigned int UpdateBasicDef(void);
};
