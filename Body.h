#pragma once
//不应该被实例化的，暂时没有加纯虚函数
class Body
{
protected:
	std::string name;
	unsigned int currentHealth, maxHealth;
	unsigned int level;
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
	double atkModifier;
	//持有经验值
	unsigned long exp;
private:

public:
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
	unsigned long expDrop;
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

/*
单例模式的战场，游戏只能存在一个战场！
通过CreateBattlefield()来创建或者得到当前战场，战斗结束后要手动释放。
数据结算在这个类中进行
*/
class Battlefield
{
private:
	Battlefield()
	{
	}
	//战场中的玩家
	Player * plr;
	//战场中的怪物
	Monster * mst;
	//实例对象指针
	static Battlefield * pBattlefield;
	//"提示框"的文字列表
	std::vector<std::string> vMessage;
private:
	//是否玩家输了或者怪物死了
	bool IsFinshed(void);
	//打印用来分隔内容的行
	void PrintLine(void);
	//打印战斗双方的状态
	bool ShowState(void);
	//打印提示框的最后8条
	bool ShowMessages(void);
	//将提示放入提示列表，上限64条
	bool AddMessage(const char * str);
	//互相伤害
	bool AttackRound(void);
	//互动 互动结束返回false
	bool Start_Interaction(void);
	//战场的数据情况是否可以开战
	bool Start_IsReady(void);
public:

public:
	//单例创建一个战场
	static Battlefield * CreateBattlefield(void);
	//什么对象参加了战斗，注意不要填错位置
	bool WhoseBattlefield(Player * player, Monster * monster);
	//开始战斗 返回true为玩家胜利
	bool Start(void);
};