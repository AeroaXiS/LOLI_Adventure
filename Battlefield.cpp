#include "Battlefield.h"
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

bool Battlefield::AttackRound(void)
{
	//用于转换的字符串流
	std::stringstream ss;
	//获得造成的伤害
	unsigned int plr_hit = this->pPlayer->BattleCommonHit(this->pMonster);
	//转化
	ss << pPlayer->WhoAmI() << "\t对\t" << pMonster->WhoAmI()
		<< "\t造成\t" << plr_hit << "\t伤害！";
	//注入
	this->AddMessage(ss.str().c_str());
	//清空
	ss.clear();
	ss.str("");
	//再来一遍
	unsigned int mst_hit = this->pMonster->BattleCommonHit(this->pPlayer);
	ss << pMonster->WhoAmI() << "\t对\t" << pPlayer->WhoAmI()
		<< "\t造成\t" << mst_hit << "\t伤害！";
	this->AddMessage(ss.str().c_str());
	return true;
}

bool Battlefield::Start_Interaction(void)
{
	system("cls");
	this->ShowState();
	this->ShowMessages();
	this->PrintLine();
	std::cout << "A-攻击" << std::endl;
	switch (_getch())
	{
	case'a':
	case'A':
		this->AddMessage("攻击！");
		this->AttackRound();
		if (this->IsFinshed()) return false; //攻击之后战场结束跳出循环
		else return true;
		break;
	default:
		return true;
		break;
	}
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
	//如果消息数量不足4条
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
	while (this->Start_Interaction())
	{
		UniformRandomSrand();
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
