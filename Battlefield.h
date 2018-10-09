#pragma once

//行动类型枚举
enum ActionType
{
	//没有任何动作，发呆
	AT_NONE = 0,
	//普通攻击
	AT_NORMAL = 1
};

//行动
struct Action
{
	//行动发出者
	Body * pbySender;
	//行动承受者
	Body * pbyVictim;
	//行动类型
	ActionType at;
	//行动附带参数1
	unsigned int unData1;
	//行动附带参数2
	unsigned int unData2;
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
	//战场中的玩家群，最多4位
	std::vector<Player *> vpPlayer;
	//战场中的怪物群，最多4只
	std::vector<Monster *> vpMonster;
	//战场中实际存在的怪物数量
	unsigned int unMonsterCount;
	//实例对象指针
	static Battlefield * pBattlefield;
	//很多地方要用到的字符串流
	std::stringstream ss;
	//"提示框"的文字列表
	std::vector<std::string> vMessage;
	//行动队列
	std::vector<Action> vActionQueue;
private:

	//打印用来分隔内容的行
	void PrintLine(void);
	//打印战斗双方的状态
	bool ShowState(void);
	//打印提示框的最后8条
	bool ShowMessage(void);
	//将提示放入提示列表，上限64条
	bool AddMessage(const char * str);
	//将ss的内容放进提示列表，快捷操作
	bool AddMessage(void);
	//清空提示列表
	bool FlushMessage(void);

	//是否玩家全灭
	bool IsAllPlayerDead(void);
	//是否怪物全灭
	bool IsAllMonsterDead(void);
	//互动 互动结束返回false
	bool Start_Interaction(void);
	//战场的数据情况是否可以开战
	bool Start_IsReady(void);
	//战场胜负判定
	bool Start_IsWin(void);
	//战场结果(最终屏)
	void Start_ShowResult(void);
	//战场怪物进场宣言
	void Start_ShowMonsterText(void);
	//战场胜利结算
	void Start_Award(void);

	//怪物选择“窗口”
	Monster * SelectMonster(void);

	//添加行动
	int AddAction(Body * pbySender, Body * pbyVictim, ActionType at,
				  unsigned int data1, unsigned int data2);
	//清空行动
	int FlushActionQueue(void);
	//执行队列
	int RunAcionQueue(void);

public:
	//单例创建一个战场
	static Battlefield * CreateBattlefield(void);
	//创建完之后要的，初始化战场一些变量或者处理
	bool Init(void);

	/*在战斗开始之前要做的*/
	//加入玩家，返回这个玩家的指针，超过上限不会加入并返回nullptr
	Player * JoinPlayer(Player * pPlayer);
	//加入怪物，返回这个怪物的指针，超过上限不会加入并返回nullptr
	Monster * JoinMonster(Monster * pMonster);

	//开始战斗，结算在内
	bool Start(void);
};