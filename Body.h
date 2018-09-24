#pragma once
//不应该被实例化的，暂时没有加纯虚函数
class Body
{
private:
	unsigned int health;
public:

public:
	Body();
	virtual ~Body();
	//攻击
	void Battle_Hit(Body * enemy);
	//承受攻击
	void Battle_Suffer(unsigned int damege);
	//死了吗
	bool IsDead(void);
	//获取当前生命值
	unsigned int Health(void);
	//设置当前生命值 并返回 重载
	unsigned int Health(unsigned int health);
};

class Player : public Body
{

};

class Monster : public Body
{

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
	Player * player;
	//战场中的怪物
	Monster * monster;
	//实例对象指针
	static Battlefield * pBattlefield;
	///WaitKeyboard中可能会被疯狂访问的对象，升级成成员函数减少构造析构
	///std::string keyboardCache;
	///WaitKeyboard等中可能会被疯狂访问的对象，升级成成员函数减少内存申请
	///char keyboardPressed;
	///按任意键自带防作死
	///void WaitKeyboard(void);
	//以上都用一个全局函数替代了
private:
	//战场的数据情况是否可以开战
	bool IsAllReady(void);
	//是否玩家输了或者怪物死了
	bool IsFinshed(void);
	//打印战斗双方的状态
	bool ShowState(void);
	//互相伤害
	bool Fuck(void);
public:

public:
	//单例创建一个战场
	static Battlefield * CreateBattlefield(void);
	//什么对象参加了战斗，注意不要填错位置
	bool WhoseBattlefield(Player * player, Monster * monster);
	//开始战斗 返回true为玩家胜利
	bool Start(void);
};