#pragma once
//不应该被实例化的，暂时没有加纯虚函数
class Body
{
protected:
	std::string strName;
	unsigned int unCurrentHealth, unMaxHealth;
	unsigned int unLevel;
public:
	Body();
	virtual ~Body();
	//攻击 返回造成的伤害 由对象的Battle_Suffer()提供
	unsigned int BattleCommonHit(Body * enemy);
	//承受攻击 返回受到的伤害
	unsigned int BattleSuffer(unsigned int damege);
	//死了吗
	bool IsDead(void);
	//将当前生命值设置成生命值上限并返回
	virtual unsigned int ResetCurrentHealth(void) = 0;
	//获取当前生命
	unsigned int GetCurrentHealth(void);
	//我是谁?返回名字字符串
	std::string & WhoAmI(void);
	//我是谁?赋予名字
	void WhoAmI(const char * name);
	//计算攻击力 一次函数 随等级变化 k决定幅度
	virtual unsigned int GetAtk(double k) = 0;
	//获取等级
	unsigned int GetLevel(void);
	//设置等级
	void SetLevel(unsigned int level);
	//获取生命值上限
	unsigned int GetMaxHealth(void);
};

class Player : public Body
{
private:
	//装备的攻击力加成 例如 x1.001
	double dAtkModifier;
	//持有经验值
	unsigned long ulExp;
private:

public:
	//默认构造函数伤害加成1等级1经验0
	Player();
	//根据等级设置生命值上限
	void SetMaxHealth(void);
	//将当前生命值设置到生命值上限(初始化
	unsigned int ResetCurrentHealth(void);
	//获取攻击力
	unsigned int GetAtk(double k);
	//设置攻击力加成
	void SetAtkModifier(double atkModifier);
	//获取攻击力加成
	double GetAtkModifier(void);
	//升级 返回升级后的等级
	unsigned int LevelUp(void);
	//若经验足够则升级返回真，否则不升级返回假
	bool IsAbleToLevelUp(void);
	//返回升级所需经验值
	unsigned long ExpNeed(void);
	//返回当前经验值
	unsigned long ExpHave(void);
	//获得经验 返回当前经验
	unsigned long AwardExp(unsigned long quantity);
};

class Monster : public Body
{
private:
	//掉落的经验值
	unsigned long ulExpDrop;
public:
	//获取攻击力
	unsigned int GetAtk(double k);
	//模仿玩家 根据等级(设想)设置生命值上限并且返回
	void SetMaxHealth(void);
	//按照数值设置生命值上限
	void SetMaxHealth(unsigned int maxHealth);
	//将当前生命值设置到生命值上限(初始化
	unsigned int ResetCurrentHealth(void);
	//获取可以掉落的经验值
	unsigned long GetExpDrop(void);
	//设置可以掉落的经验值
	void SetExpDrop(unsigned long expDrop);
};
