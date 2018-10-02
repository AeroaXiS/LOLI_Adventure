#include "pch.h"
#include "Body.h"

Battlefield * Battlefield::pBattlefield = nullptr;

Body::Body()
{
}


Body::~Body()
{
}

unsigned int Body::BattleCommonHit(Body * enemy)
{
	return enemy->BattleSuffer(RangeUniformRandom(this->GetAtk(1), 0.2));
}

unsigned int Body::BattleSuffer(unsigned int damege)
{
	if (damege >= this->currentHealth)
	{
		this->currentHealth = 0;
	}
	else
	{
		this->currentHealth -= damege;
	}
	return damege;
}

bool Body::IsDead(void)
{
	if (this->currentHealth <= 0) return true;
	return false;
}


unsigned int Body::GetCurrentHealth(void)
{
	return this->currentHealth;
}

std::string & Body::WhoAmI(void)
{
	return this->name;
}

void Body::WhoAmI(const char * name)
{
	this->name.assign(name);
}

unsigned int Body::GetLevel(void)
{
	return this->level;
}

void Body::SetLevel(unsigned int level)
{
	this->level = level;
}

unsigned int Body::GetMaxHealth(void)
{
	return this->maxHealth;
}

bool Battlefield::Start_IsReady(void)
{
	//正常
	if (this->plr != nullptr &&
		this->mst != nullptr)
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
	this->plr = plr;
	this->mst = mst;
	return true;
}

bool Battlefield::AttackRound(void)
{
	//用于转换的字符串流
	std::stringstream ss;
	//获得造成的伤害
	unsigned int plr_hit = this->plr->BattleCommonHit(this->mst);
	//转化
	ss << plr->WhoAmI() << "\t对\t" << mst->WhoAmI()
		<< "\t造成\t" << plr_hit << "\t伤害！";
	//注入
	this->AddMessage(ss.str().c_str());
	//清空
	ss.clear();
	ss.str("");
	//再来一遍
	unsigned int mst_hit = this->mst->BattleCommonHit(this->plr);
	ss << mst->WhoAmI() << "\t对\t" << plr->WhoAmI()
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
	cout << plr->WhoAmI() << "\tLV:" << plr->GetLevel()
		<<" Exp:"<<plr->ExpHave()<<" / "<<plr->ExpNeed()<< endl;
	cout << " HP:\t" << this->plr->GetCurrentHealth() << " / "
		<< this->plr->GetMaxHealth() << endl;
	this->PrintLine();
	cout << mst->WhoAmI() << "\tLV:" << mst->GetLevel() << endl;
	cout << " HP:\t" << this->mst->GetCurrentHealth() << " / "
		<< this->mst->GetMaxHealth() << endl;
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
	if (this->plr->IsDead() || this->mst->IsDead())
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
	ss << "遇到了" << this->mst->GetLevel() << "级的" << this->mst->WhoAmI();
	this->AddMessage(ss.str().c_str());

	//战斗循环
	while (this->Start_Interaction())
	{
		UniformRandomSrand();
	}

	//赢了吗
	bool isWin = false;
	if (this->plr->IsDead())
	{
		//玩家输了
		this->AddMessage("失败了！");
		isWin = false;
	}
	else if (this->mst->IsDead())
	{
		//玩家赢了
		this->AddMessage("胜利了！");
		//加经验
		plr->AwardExp(mst->GetExpDrop());
		ss.clear();
		ss.str("");
		ss << "获得了 " << mst->GetExpDrop() << " 点经验";
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
	while (plr->IsAbleToLevelUp())
	{
		ss.clear();
		ss.str("");
		ss << "等级上升到 " << plr->LevelUp() << " 级！";
		this->AddMessage(ss.str().c_str());
	}

	//让玩家知道结果
	system("cls");
	this->ShowState();
	this->ShowMessages();
	WaitAnyKey();
	return isWin;
}

Player::Player()
{
	this->SetAtkModifier(1.0);
	this->SetLevel(1);
	this->exp = 0;
}

void Player::SetMaxHealth(void)
{
	//生命值 = k * level + 128
	const double k = 1.0;
	this->maxHealth = static_cast<unsigned int>(k * this->level + 128);
}


unsigned int Player::ResetCurrentHealth(void)
{
	this->currentHealth = this->maxHealth;
	return this->currentHealth;
}

unsigned int Player::GetAtk(double k)
{
	//基础攻击力4
	return static_cast<unsigned int>(
		(k * this->level + 4)*(this->atkModifier)
		);
}

void Player::SetAtkModifier(double atkModifier)
{
	//不可以小于等于0
	if (atkModifier <= 0) return;
	this->atkModifier = atkModifier;
}

double Player::GetAtkModifier(void)
{
	return this->atkModifier;
}

unsigned int Player::LevelUp(void)
{
	this->level++;
	return this->level;
}

bool Player::IsAbleToLevelUp(void)
{
	if (exp >= this->ExpNeed())
	{
		return true;
	}
	return false;
}

unsigned long Player::ExpNeed(void)
{
	//到下一等级所需经验值计算公式 16x^2 + 128
	unsigned int x = this->level - 1;
	return (x * x * 256 + 128);
}

unsigned long Player::ExpHave(void)
{
	return this->exp;
}

unsigned long Player::AwardExp(unsigned long quantity)
{
	this->exp += quantity;
	return this->exp;
}


unsigned int Monster::GetAtk(double k)
{
	//默认4
	return 4;
}

void Monster::SetMaxHealth(void)
{
	//生命值 = k * level + 128
	const double k = 1.0;
	this->maxHealth = static_cast<unsigned int>(k * this->level + 128);
}

void Monster::SetMaxHealth(unsigned int maxHealth)
{
	this->maxHealth = maxHealth;
}

unsigned int Monster::ResetCurrentHealth(void)
{
	this->currentHealth = maxHealth;
	return this->currentHealth;
}

unsigned long Monster::GetExpDrop(void)
{
	return this->expDrop;
}

void Monster::SetExpDrop(unsigned long expDrop)
{
	this->expDrop = expDrop;
}
