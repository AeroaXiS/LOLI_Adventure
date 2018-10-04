#include "pch.h"

Battlefield * Battlefield::pBattlefield = nullptr;


bool Battlefield::Start_IsReady(void)
{
	//正常
	if (this->pPlayer != nullptr &&
		this->pMonster != nullptr)
	{
		return true;
	}
	//警告
	std::cout << "[错误] 试图在数据不足时进行Battlefield::Start()"
		<< std::endl;
	WaitAnyKey();
	return false;
}

int Battlefield::AddAction(Body * pbySender, Body * pbyVictim, ActionType at, unsigned int data1, unsigned int data2)
{
	Action tmpA;
	tmpA.pbySender = pbySender;
	tmpA.pbyVictim = pbyVictim;
	tmpA.at = at;
	tmpA.unData1 = data1;
	tmpA.unData2 = data2;
	this->vActionQueue.push_back(tmpA);
	return 0;
}

int Battlefield::FlushActionQueue(void)
{
	std::vector<Action> emptyVec;
	this->vActionQueue.swap(emptyVec);
	return 0;
}

int Battlefield::RunAcionQueue(void)
{
	for (auto &a : this->vActionQueue)
	{
		//清空
		ss.clear();
		ss.str("");
		switch (a.at)
		{
		case AT_NORMAL:
			unsigned int damage;
			damage = a.pbySender->BattleCommonHit(a.pbyVictim);
			ss << a.pbySender->WhoAmI() << " 对 "
				<< a.pbyVictim->WhoAmI() << " 造成 "
				<< damage << " 伤害";
			this->AddMessage(ss.str().c_str());
			break;
		default:
			ss << a.pbySender->WhoAmI() << " 不知所措";
			this->AddMessage(ss.str().c_str());
			break;
		}
	}
	return 0;
}

Battlefield * Battlefield::CreateBattlefield(void)
{
	if (Battlefield::pBattlefield != nullptr)
	{
		return Battlefield::pBattlefield;
	}
	pBattlefield = new Battlefield;
	return pBattlefield;
}

bool Battlefield::WhoseBattlefield(Player * plr, Monster * mst)
{
	this->pPlayer = plr;
	this->pMonster = mst;
	return true;
}

bool Battlefield::Start_Interaction(void)
{
	system("cls");
	this->ShowState();
	this->ShowMessages();
	this->PrintLine();
	std::cout << "A-攻击" << std::endl;
	//已经采取行动了吗
	bool actionTaken = false;
	while (!actionTaken)
	{
		switch (_getch())
		{
		case'a':
		case'A':
			this->AddMessage("攻击！");
			this->AddAction(this->pPlayer, this->pMonster,
							AT_NORMAL, 0, 0);
			actionTaken = true;
			break;
		default:
			break;
		}
	}
	return true;
}

bool Battlefield::ShowState(void)
{
	using namespace std;
	this->PrintLine();
	cout << pPlayer->WhoAmI() << "\tLV:" << pPlayer->GetLevel()
		<< " Exp:" << pPlayer->ExpHave() << " / " << pPlayer->ExpNeed() << endl;
	cout << " HP:\t" << this->pPlayer->GetCurrentHealth() << " / "
		<< this->pPlayer->GetMaxHealth() << endl;
	this->PrintLine();
	cout << pMonster->WhoAmI() << "\tLV:" << pMonster->GetLevel() << endl;
	cout << " HP:\t" << this->pMonster->GetCurrentHealth() << " / "
		<< this->pMonster->GetMaxHealth() << endl;
	this->PrintLine();
	return true;
}

bool Battlefield::ShowMessages(void)
{
	int delta;
	//如果消息数量不足8条
	if (this->vMessage.size() <= 8)
	{
		delta = this->vMessage.size();
	}
	else
	{
		delta = 9;
	}
	for (auto iter = this->vMessage.end() - delta;
		 iter != vMessage.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}
	return true;
}

bool Battlefield::AddMessage(const char * str)
{
	if (this->vMessage.size() >= 64)
	{
		this->vMessage.erase(this->vMessage.begin());
	}
	this->vMessage.emplace_back(str);
	return true;
}

bool Battlefield::IsFinshed(void)
{
	if (this->pPlayer->IsDead() || this->pMonster->IsDead())
	{
		return true;
	}
	return false;
}

void Battlefield::PrintLine(void)
{
	using namespace std;
	cout <<
		"================================================================"
		<< endl;
}

bool Battlefield::Start(void)
{
	std::stringstream ss;

	//首先检测是不是可以开战
	if (!this->Start_IsReady())
	{
		//不可以就返回战斗失败
		return false;
	}

	//怪物进场宣言
	ss << "遇到了" << this->pMonster->GetLevel() << "级的" << this->pMonster->WhoAmI();
	this->AddMessage(ss.str().c_str());

	//战斗循环
	while (!this->IsFinshed())
	{
		UniformRandomSrand();
		this->Start_Interaction();
		//todo:	这里插入怪物AI
		//下面是临时的怪物ai
		AddAction(this->pMonster, this->pPlayer, AT_NORMAL, 0, 0);
		this->RunAcionQueue();
		this->FlushActionQueue();
	}

	//赢了吗
	bool isWin = false;
	if (this->pPlayer->IsDead())
	{
		//玩家输了
		this->AddMessage("失败了！");
		isWin = false;
	}
	else if (this->pMonster->IsDead())
	{
		//玩家赢了
		this->AddMessage("胜利了！");
		//加经验
		pPlayer->AwardExp(pMonster->GetExpDrop());
		ss.clear();
		ss.str("");
		ss << "获得了 " << pMonster->GetExpDrop() << " 点经验";
		this->AddMessage(ss.str().c_str());
		isWin = true;
	}
	else
	{
		//既然跳出了战斗循环但是没有人死，大概不可能的情况
		std::cout << "[错误] 战场结算出现灵异事件" << std::endl;
		WaitAnyKey();
		isWin = false;
	}

	//循环检测升级
	while (pPlayer->IsAbleToLevelUp())
	{
		ss.clear();
		ss.str("");
		ss << "等级上升到 " << pPlayer->LevelUp() << " 级！";
		this->AddMessage(ss.str().c_str());
	}

	//让玩家知道结果
	system("cls");
	this->ShowState();
	this->ShowMessages();
	WaitAnyKey();
	return isWin;
}
