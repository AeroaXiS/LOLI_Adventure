#pragma once


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
	Player * pPlayer;
	//战场中的怪物
	Monster * pMonster;
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