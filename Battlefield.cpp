#include "pch.h"

Battlefield * Battlefield::pBattlefield = nullptr;

bool Battlefield::IsReadyToStart(void)
{
	//至少有一个玩家和敌人
	if (this->vpMonster.size() >= 1 && this->vpPlayer.size() >= 1)
	{
		return true;
	}
	std::cout << "[警告] 战场玩家或敌人少于1" << std::endl;
	WaitAnyKey();
	return false;
}

bool Battlefield::IsPlayerWining(void)
{
	if (this->IsAllPlayerDead())
	{
		//玩家输了
		return false;
	}
	else if (this->IsAllMonsterDead())
	{
		//玩家赢了
		return true;
	}
	else
	{
		//能够到达这里并且没有人死是不可能的
		std::cout << "[错误] 战场结算出现灵异事件" << std::endl;
		WaitAnyKey();
		return false;
	}
	return false;
}

void Battlefield::ShowResult(void)
{
	system("cls");
	this->ShowState();
	this->ShowMessage(16);
	WaitAnyKey();
}

void Battlefield::ShowMonsterIntro(void)
{
	for (auto &pMonster : this->vpMonster)
	{
		ss.clear();
		ss.str("");
		ss << "遇到了" << pMonster->GetLevel() << "级的" << pMonster->GetName();
		this->AddMessage();
	}
}

void Battlefield::AwardPlayer(void)
{
	//掉落总经验
	unsigned long ulExpSum = 0;
	for (auto &pMonster : this->vpMonster)
	{
		ulExpSum += pMonster->GetExpDrop();
	}
	//加经验，经验每人一份
	for (auto &pPlayer : this->vpPlayer)
	{
		//活人才有经验，死人跳过
		if (pPlayer->IsDead()) continue;
		pPlayer->AwardExp(ulExpSum);
		ss.clear();
		ss.str("");
		ss << "获得了 " << ulExpSum << " 点经验";
		this->AddMessage();
		//升级
		if (pPlayer->CheckLevelUp() != 0)
		{
			ss.clear();
			ss.str("");
			ss << "升级到 " << pPlayer->GetLevel() << " 级！";
			this->AddMessage();
		}
	}
}

void Battlefield::Balance(void)
{
	if (IsAllMonsterDead())
	{
		//胜利
		this->AddMessage("胜利了");
		this->AwardPlayer();
	}
	else
	{
		//失败
		this->AddMessage("失败了");
	}
}

Monster * Battlefield::SelectMonster(void)
{
	//如果只有一个返回这个，判断的时候已经更新了
	if (UpdateAliveMonster() == 1) return this->vpAliveMonster[0];
	//如果一个活的都没有，返回null
	if (this->vpAliveMonster.size() == 0) return nullptr;

	//选择的序号
	unsigned int selected = 0;
	std::cout << "选择攻击对象:" << std::endl;
	std::cout << "[0]返回" << std::endl;
	auto iter = vpAliveMonster.begin();
	int i = 1;
	while (iter != this->vpAliveMonster.end())
	{
		std::cout << "[" << i << "] " << (**iter).GetName() << std::endl;
		i++;
		iter++;
	}
	//获取和过滤数字以外的按键，屏蔽超过实际怪物存在数量的按键，识别返回
	while (true)
	{
		selected = WaitNumKey();
		if (selected == 0) return nullptr;
		if (selected <= this->vpAliveMonster.size())
		{
			return this->vpAliveMonster[selected - 1];
		}
	}
	return nullptr;
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
	//std::vector<Action> emptyVec;
	//this->vActionQueue.swap(emptyVec);
	this->vActionQueue.clear();
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
			ss << a.pbySender->GetName() << " 对 "
				<< a.pbyVictim->GetName() << " 造成 "
				<< damage << " 伤害";
			this->AddMessage(ss.str().c_str());
			break;
		default:
			ss << a.pbySender->GetName() << " 不知所措";
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

bool Battlefield::Init(void)
{
	this->unMonsterCount = 0;
	return true;
}

Player * Battlefield::JoinPlayer(Player * pPlayer)
{
	//到达上限了
	if (this->vpPlayer.size() >= 4) return nullptr;
	//mdzz
	if (pPlayer == nullptr) return nullptr;
	//加入
	this->vpPlayer.push_back(pPlayer);
	//返回刚刚push_back的
	return *(this->vpPlayer.end() - 1);
}

Monster * Battlefield::JoinMonster(Monster * pMonster)
{
	if (this->vpMonster.size() >= 4) return nullptr;
	if (pMonster == nullptr) return nullptr;
	this->vpMonster.push_back(pMonster);
	return *(this->vpMonster.end() - 1);
}

bool Battlefield::IsAllPlayerDead(void)
{
	for (auto &pPlayer : this->vpPlayer)
	{
		if (!pPlayer->IsDead())
		{
			return false;
		}
	}
	return true;
}

bool Battlefield::IsAllMonsterDead(void)
{
	for (auto &pMonster : this->vpMonster)
	{
		if (!pMonster->IsDead())
		{
			return false;
		}
	}
	return true;
}

unsigned int Battlefield::UpdateAlivePlayer(void)
{
	this->vpAlivePlayer.clear();
	for (auto &pPlayer : this->vpPlayer)
	{
		if (!pPlayer->IsDead()) this->vpAlivePlayer.push_back(pPlayer);
	}
	return vpAlivePlayer.size();
}

unsigned int Battlefield::UpdateAliveMonster(void)
{
	this->vpAliveMonster.clear();
	for (auto &pPlayer : this->vpMonster)
	{
		if (!pPlayer->IsDead()) this->vpAliveMonster.push_back(pPlayer);
	}
	return vpAliveMonster.size();
}

bool Battlefield::Interact(void)
{
	//选中的怪物，可能用到
	Monster * pMonsterSelected;
	//每个活人都有一次下命令的机会
	for (auto &pPlayer : this->vpPlayer)
	{
		//死人跳过
		if (pPlayer->IsDead()) continue;
		//这个人已经要进入下一个回合了吗（真的行动了吗
		bool roundPassed = false;
		//菜单循环
		while (!roundPassed)
		{
			system("cls");
			this->ShowState();
			this->ShowMessage();
			this->PrintLine();
			std::cout << pPlayer->GetName() << "要做什么: ";
			std::cout << "A-攻击" << std::endl;
			switch (_getch())
			{
			case'a':
			case'A':
				pMonsterSelected = this->SelectMonster();
				if (pMonsterSelected == nullptr) break;
				this->AddMessage("攻击！");
				this->AddAction(pPlayer, pMonsterSelected,
								AT_NORMAL, 0, 0);
				roundPassed = true;
				break;
			default:
				break;
			}
		}
	}

	return true;
}

void Battlefield::PrintLine(void)
{
	using namespace std;
	cout <<
		"================================================================"
		<< endl;
}

bool Battlefield::ShowState(void)
{
	using namespace std;
	this->UpdateAlivePlayer();
	this->UpdateAliveMonster();
	//输出玩家的先
	for (auto &pPlayer : this->vpAlivePlayer)
	{
		std::cout << pPlayer->GetName() << " LV:" << pPlayer->GetLevel()
			<< " Exp:" << pPlayer->GetExpHave() << "/" << pPlayer->GetExpNeed()
			<< std::endl;
		std::cout << " HP:" << pPlayer->GetCurrentHealth() << "/"
			<< pPlayer->GetMaxHealth() << std::endl;
	}
	this->PrintLine();
	//怪物的
	for (auto &pMonster : this->vpAliveMonster)
	{
		std::cout << pMonster->GetName() << " LV:" << pMonster->GetLevel()
			<< std::endl;
		std::cout << " HP:" << pMonster->GetCurrentHealth() << "/"
			<< pMonster->GetMaxHealth() << std::endl;
	}
	this->PrintLine();
	return true;
}

bool Battlefield::ShowMessage(unsigned int many)
{
	int delta;
	//0条不输出
	if (many == 0) return false;
	//如果消息数量不足条
	if (this->vMessage.size() <= many)
	{
		delta = this->vMessage.size();
	}
	else
	{
		delta = many + 1;
	}
	for (auto iter = this->vMessage.end() - delta;
		 iter != vMessage.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}
	return true;
}

//将提示放入提示列表，上限64条
bool Battlefield::AddMessage(const char * str)
{
	if (this->vMessage.size() >= 64)
	{
		this->vMessage.erase(this->vMessage.begin());
	}
	this->vMessage.emplace_back(str);
	return true;
}

//将ss的内容放进提示列表，快捷操作
bool Battlefield::AddMessage(void)
{
	this->AddMessage(this->ss.str().c_str());
	return true;
}

bool Battlefield::FlushMessage(void)
{
	//std::vector<std::string> emptyVec;
	//this->vMessage.swap(emptyVec);
	this->vMessage.clear();
	return true;
}

bool Battlefield::Start(void)
{
	//首先检测是不是可以开战 不可以就返回战斗失败
	if (!this->IsReadyToStart()) return false;

	//怪物进场宣言
	this->ShowMonsterIntro();
	this->UpdateAliveMonster();
	this->UpdateAlivePlayer();

	//战斗循环
	while (!IsAllMonsterDead() && !IsAllPlayerDead())
	{
		UniformRandomSrand();
		this->Interact();
		//todo:	这里插入怪物智能
		//下面是临时的
		for (auto &pMonster : this->vpMonster)
		{
			this->AddAction(pMonster, this->vpAlivePlayer[0], AT_NORMAL, 0, 0);
		}
		this->RunAcionQueue();
		this->FlushActionQueue();
	}

	//胜利结算
	this->Balance();

	//打印最终屏
	this->ShowResult();

	return IsAllMonsterDead();
}